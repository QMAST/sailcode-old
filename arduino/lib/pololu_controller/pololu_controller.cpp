#include "pololu_controller.h"

uint8_t pcon_buffer_to_dev[PCON_MAX_TO_DEV];
uint8_t pcon_buffer_from_dev[PCON_MAX_FROM_DEV];

uint8_t pconInitialise( polcore** dev, 
        HardwareSerial* serial_line, uint8_t dev_number ) {
    *dev = (polcore*) malloc( sizeof(polcore) );
    if( dev == NULL ) return 1; // Not enough memory

    (*dev)->serial_line = serial_line;
    (*dev)->device_number = dev_number;
    (*dev)->control = 0;

    return 0;
}

uint8_t pconSendCommand( polcore* dev, uint8_t* cmd ) {

    dev->serial_line->write( PCON_DEFAULT_COMMAND_BYTE );
    dev->serial_line->write( dev->device_number );

    // Starts at one since first byte is the number of bytes to be printed
    for( uint8_t i = 1; i <= cmd[0]; i++ ) {
        dev->serial_line->write( cmd[i] );
    }

    return 0;
}

uint8_t pconSendCommandBuffer( polcore* dev ) {
    return pconSendCommand( dev, pcon_buffer_to_dev );
}

uint8_t pconGenMotorGo( polcore* dev, uint8_t* buffer,
        uint8_t percent_power, enum PCON_DIRECTION direction ) {
    uint8_t direction_command;

    // If feedback isn't enabled for the device, send it the safe start signal
    // before any command to guarantee it will be accepted.
    if( ! pconCheckControl( dev, PCON_FEEDBACK_ENABLED ) ) {
        pconSendSafe( dev );
    }

    if( direction == PCON_FORWORD ) {
        direction_command = 0x05;
    } else if ( direction == PCON_BACKWORD ) {
        direction_command = 0x06;
    } else {
        // DEBUG Serial --> Invalid command
        return 1;
    }

    buffer[0] = 3; /* Number of bytes to be sent will always be 3 with this
                    * command
                    */
    buffer[1] = direction_command;
    buffer[2] = 0x00;
    buffer[3] = percent_power;

    if( percent_power > 0 ) {
        dev->control |= PCON_IS_RUNNING;
    } else if ( percent_power == 0 ) {
        dev->control &= ~percent_power;
    }

    return 0;
}

uint8_t pconGenMotorStop( polcore* dev, uint8_t* buffer ) {
    return pconGenMotorGo( dev, buffer, 0x0, PCON_FORWORD );
}

uint8_t pconGetResponse(polcore* dev, uint8_t* buffer ) {
    delay(PCON_RESPONCE_BREATH_TIME);

    if( dev->serial_line->available() <= 0 ) return 1;
    
    for( uint8_t i = 0; i < PCON_MAX_FROM_DEV 
            && dev->serial_line->available() > 0; i++ ) {
        buffer[i] = dev->serial_line->read();
    }

    return 0;
}

void pconSendSafe( polcore* dev ) {
    dev->serial_line->write( PCON_DEFAULT_COMMAND_BYTE );
    dev->serial_line->write( dev->device_number );
    dev->serial_line->write( 0x03 );
}

uint8_t pconCheckControl( polcore* dev, PCON_CONTROL bit ) {
    uint8_t check = 0;
    check = dev->control & bit;

    return check;
}

void pconSetControl( polcore* dev, PCON_CONTROL bit ) {
    dev->control |= bit;   
}

void pconClearControl( polcore* dev, PCON_CONTROL bit ) {
    dev->control &= ~bit;
}


#include "cmdline_functions.h"

#define SERVO_MAX_ANGLE 250 // The minimum angle is assumed to be 0

// The minimum output and maximum output are assumed to be the same magnitude,
// just opposite signs.
#define RC_MAX_MAGNITUDE 1000

int uabout( char* argv[] )
{
    // Cool little ascii art made with a program called figlet, gotta
    // escape the special characters though

    // Remember, printf has a 80 char limit at a time
    // This eats a tonne of sram, TODO switch this into a PROGMEM string
    static const unsigned char TEXT_LOGO_ARRAY[5][80] PROGMEM =
        {
"  ___|    \\    ____| |     ____| _ \\   _  \\  ___| ____| \\ \\  / |     \n",
" |       _ \\   __|   |     |    |   | |   | |     __|    \\  /  |     \n",
" |   |  ___ \\  |     |     __|  |   | __ <  |     |         \\  |     \n",
"\\____|_/    _\\_____|_____|_|   \\___/ _| \\_\\\\____|_____|  _/\\_\\_____| \n\n\n",
"AshCon Version 0.021 \n"
        };
    for( uint8_t i = 0; i < 5; i++ ) {
        Console->out->printf_P(TEXT_LOGO_ARRAY[i]);
    }

    P(COMPILED_TIME) = "Compiled on "__DATE__" "__TIME__ "\n";
    // Print the date and time of compilation
    // These macros cannot be within the quotes
    Console->out->printf_P( COMPILED_TIME );
    Console->ufunc_dump();

    return 0;
}

int umon( char* argv[] )
{
    Stream* internal_line = Console->out->getStream();
    Stream* ser_line;
    uint8_t value;
    sscanf( argv[1], "%d", &value );

    if( value == 1 )
        ser_line = &Serial1;
    else if( value == 2 )
        ser_line = &Serial2;
    else if( value == 3 )
        ser_line = &Serial3;

    char c = '1';

    while( c != 'q' ) {
        if( ser_line->available() > 0 ) {
            internal_line->print( ( char ) ser_line->read() );
        }

        if( internal_line->available() )
            c = internal_line->read();
    }
}


/** RC Poll all command line debug function
 *
 * Prints the current value of all the controllers channels to the main serial
 * line. Ends when a 'q' character is encountered on the command line
 */
int urcpollall( char* argv[] )
{
    P( MSG_FORMAT ) = "LS: (%d,%d) RS: (%d,%d) SW[%d] AUX[%d]\n";
    char c = '1';

    while( c != 'q' ) {
        updateControllerValues( radio );
        Console->out->printf_P( MSG_FORMAT,
                              getAxisOutput( radio->LSX ),
                              getAxisOutput( radio->LSY ),
                              getAxisOutput( radio->RSX ),
                              getAxisOutput( radio->RSY ),
                              getSwitchOutput( radio->gearSwitch ),
                              getAxisOutput( radio->AUX )
                            );

        if( Console->out->getStream()->available() ) {
            c = Console->out->getStream()->read();
        }
    }
}

int uselfcheck(char* argv[]) {
    P(DIAG_MSG_0) = "Available memory: %d\n";
    Console->out->printf_P( DIAG_MSG_0, freeMemory() );

    return 0;
}

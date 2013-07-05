#include "pololu_servo.h" 

PololuMSC::PololuMSC(Stream* serialIn, int reset_pin) {
    for( int i = 0; i < this->SERVO_SLOTS; i++ ) {
        this->available_servos[i].current_value = SERVO_DEFAULT;
        this->available_servos[i].is_attached = false;
    }

    this->DEBUG = false;

    this->serialCom = serialIn;
    this->reset_pin = reset_pin;
}

int PololuMSC::restart() {
    // reset the pololu
    digitalWrite(this->reset_pin, HIGH);
    delay(this->RESET_HIGH_WAIT);
    digitalWrite(this->reset_pin, LOW);
    delay(this->RESET_LOW_WAIT);

    // send initialization byte
    this->serialCom->write(0xFF);

    return 0;
}
int PololuMSC::setPosition(int motorID, int newValue) {
    if ( newValue > 254 || newValue < 0
            || motorID < 0 || motorID > this->SERVO_SLOTS - 1 ) {
        if ( this->DEBUG ) {
            this->serialDebug->println("Invalid setPosition Values");
        }
        return -1;
    }  
    this->available_servos[motorID].current_value = newValue;
    this->available_servos[motorID].is_attached = true;

    this->serialCom->write(0xFF);
    this->serialCom->write(motorID);
    this->serialCom->write(newValue);
    
    return 0;
}

int PololuMSC::debugSet(Stream* newSerial) {
    if ( newSerial == NULL ) {
        return -1;
    }
    this->serialDebug = newSerial;
    this->DEBUG = true;

    return 0;
}

int PololuMSC::debugOff() {
    this->DEBUG = false;
    this->serialDebug = NULL;
    return 0;
}

#include "ashcon.h"

ashcon::ashcon(Stream* new_line_in) {
    if( new_line_in != NULL ) {
        this->line_in = new_line_in;
    }

    this->internal_buffer = (char*)
                            malloc( sizeof(char) * (BUFFER_LENGTH + 1) );
    this->internal_buffer[BUFFER_LENGTH] = '\0';
    this->internal_buffer_len = BUFFER_LENGTH;
}

int ashcon::printf( char* fmt, ... ) {
    // Taken from http://playground.arduino.cc/Main/Printf
    char tmp[128]; // resulting string limited to 128 chars
    va_list args;
    va_start (args, fmt );
    vsnprintf(tmp, 128, fmt, args);
    va_end (args);
    this->line_in->print(tmp);

    return this->SUCCESS;
}

int ashcon::get_line() {
    int idx = 0; // how many characters we've pulled
    char char_in = '\0';

    while( i < this->internal_buffer_len && char_in != '\n' ) {
        if( this->line_in->available() > 0 ) {
            char_in = this->line_in->read();

            this->internal_buffer[i] = char_in;
        }
    
    }
}

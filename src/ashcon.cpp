#include "ashcon.h"

/** Initialize a console
 *
 * Pass a serial line to be used as the command console. Initialise the
 * internal buffer off the heap.
 */
ashcon::ashcon(Stream* new_line_in) {
    if( new_line_in != NULL ) {
        this->line_in = new_line_in;
    }

    this->internal_buffer = (char*)
                            malloc( sizeof(char) * (BUFFER_LENGTH + 1) );
    this->internal_buffer[BUFFER_LENGTH] = '\0';
    this->internal_buffer_len = BUFFER_LENGTH;
}

/** Emulated printf
 *
 * Taken from arduino forum, emulates printf without having to
 * include the true version which requires a FILE handle and a lot more
 * memory.
 */
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

/** get_line
 *
 * Sit and wait for the user to type a command line into the arduino.
 * Expects to wait until either the buffer has filled or the user has
 * enetered a newline character.
 *
 * Currently newline character is hardcoded.
 */
int ashcon::get_line() {
    int i = 0; // how many characters we've pulled
    char char_in = '\0';

    // Sit and wait until the line ends or the buffer fills,
    // Danger, it could wait forever without a timer.
    while( i < this->internal_buffer_len ) {
        if( this->line_in->available() > 0 ) {
            // A character is ready, grab it
            char_in = this->line_in->read();

            // Newline detection, varies on the monitor program...
            if( char_in == '\r' ) {
                //this->printf("Found an \\r \n\r");
                break;
            } else if ( char_in == '\n' ) {
                //this->printf("Found a \\n \n\r");
                break;
            }

            this->internal_buffer[i] = char_in;

            if( this->ECHO ) {
                this->line_in->print(char_in);
            }
            i++;
        }
    }

    this->internal_buffer[i] = '\0';

    if( this->ECHO ) {
        this->line_in->print("\n\r");
    }

    return this->SUCCESS;
}

char* ashcon::get_internal_buffer() {
    return this->internal_buffer;
}

#ifndef ashcon_h
#define ashcon_h

#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

class ashcon {
    private:
        static const int SUCCESS = 0;
        static const int BUFFER_LENGTH = 128;
        static const int ECHO = 1;
        Stream* line_in;

        char* internal_buffer;
        int internal_buffer_len;
    public:
        ashcon(Stream* new_line_in);

        int printf(char* fmt, ... );
        int get_line();

        char* get_internal_buffer();

        int prompt();
};

#endif

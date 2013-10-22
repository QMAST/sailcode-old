#ifndef ARDUINO_PRINTF_H
#define ARDUINO_PRINTF_H 
#include <Arduino.h>
#include <stdarg.h>

#ifdef __AVR__
#define P(name)   static const unsigned char name[] PROGMEM
#else
#define P(name)   static const unsigned char name[]
#endif

class aprintf {
    static const uint8_t PRINTF_BUFFER = 80;
    Stream* interface;

    public:
        aprintf( Stream* interface );
        void printf( char *fmt, ... );
        void printf_P( const prog_uint8_t* fmt, ... );
};
#endif

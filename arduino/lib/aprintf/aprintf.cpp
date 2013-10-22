#include "aprintf.h"

aprintf::aprintf( Stream* interface ) {
    this->interface = interface;
}

void aprintf::printf(char *fmt, ... ){
    char tmp[PRINTF_BUFFER];

    va_list args;
    va_start (args, fmt );
    vsnprintf(tmp, PRINTF_BUFFER, fmt, args);
    va_end (args);

    interface->print(tmp);
}

void aprintf::printf_P( const prog_uint8_t* fmt, ... ) {
    char tmp[PRINTF_BUFFER];

    va_list args;
    va_start (args, fmt );
    vsnprintf_P(tmp, PRINTF_BUFFER, (const prog_char*)fmt, args);
    va_end (args);

    interface->print(tmp);
}

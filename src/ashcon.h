#ifndef ashcon_h
#define ashcon_h

#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

class ashcon {
    private:
        static const int SUCCESS = 0;
        static const int ECHO = 1;
        Stream* line_in;

        // The internal command buffer, think get_line and where it puts
        // the results right away
        static const int COMMAND_BUFFER_LENGTH = 128;
        char* command_buffer;

        // Command arguments
        // NOTE: Specific documentation needed for this
        static const int COMMAND_ARG_NUM_MAX = 12;
        char* command_arg_list[COMMAND_ARG_NUM_MAX];
        int command_arg_num; // Acts as index to arg list

        int command_arg_append();
        int command_arg_clear();



    public:
        ashcon(Stream* new_line_in);

        int printf(char* fmt, ... );
        int get_line();

        // Debugging purposes
        char* get_command_buffer();

        int prompt();
};

#endif

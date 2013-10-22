#ifndef ashcon_h
#define ashcon_h

#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <aprintf.h>

class ashcon {
    public:
        static const int SUCCESS = 0;
        static const int FAILURE = 1;
        static const int ECHO = 0;
        ashcon(Stream* new_line_in);

        aprintf* out;

        int command_prompt();

        int get_line();
        int get_line_splitline();

        int user_function_register( char* id, int (*func)(char* args[]) );
        int user_function_call( char* id );

        // Debugging purposes
        //char* get_command_buffer();

    private:
        // Serial port used for communication
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

        // Functions to deal with the list of arguments
        void command_arg_init();
        int command_arg_append(char*);
#ifdef DEBUG
        void command_arg_dump_debug();
#endif
        int command_arg_clear();

        // Function list, register functions to be called with the
        // internal command list
        typedef struct {
            char* id;
            int (*func)(char* args[]);
        } user_function;
        
        static const int FUNCTION_LIST_MAX = 12;
        static const int FUNCTION_LIST_ID_MAX = 12;
        user_function ufunc_list[FUNCTION_LIST_MAX];
        int ufunc_list_idx;

        // Debug functions
        void ufunc_dump();


};

#endif

#include <ashcon.h>
#include <aprintf.h>
#include <pololu_controller.h>
#include <RadioControl.h>

#include "cmdline_functions.h"

ashcon* Console;
polcore* motor;

void setup() {
    Serial.begin(19200);
    Serial2.begin(9600);

    pconInitialise( &motor, &Serial2, 13 );

    Console = new ashcon( &Serial );
    Console->user_function_register( "about", &uabout );
    Console->user_function_register( "pol", &upol );
    Console->user_function_register( "hello", &ucommandprint );
}

void loop() {
    Console->command_prompt();
}

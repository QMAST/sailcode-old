#include <ashcon.h>
#include <aprintf.h>
#include <pololu_controller.h>
#include <RadioControl.h>

#include "cmdline_functions.h"

ashcon* Console;
polcore* motor;
RC* radio;

void setup() {
    /** Initialise the serial lines
     */
    Serial.begin(19200); // Connected to main comm line
    Serial1.begin(9600); // Connected to PololuMSC
    Serial2.begin(9600); // to Pololu dc controllers
    Serial3.begin(4800); // to AIRMAR receiver line

    radio = initRC();

    pconInitialise( &motor, &Serial2, 13 );

    Console = new ashcon( &Serial );
    Console->user_function_register( "about",   &uabout );
    Console->user_function_register( "rc",      &urcpollall );
	Console->user_function_register( "motorgo", &umotorGo );
	Console->user_function_register( "m", &umotorGo ); // For brevity
	Console->user_function_register( "startrc", &ustartRCControl );
}

/* Main polling loop
 *
 * All functions must be as non-blocking as possible
 */
void loop() {
    Console->command_prompt();
}

#include "cmdline_functions.h"

#define SERVO_MAX_ANGLE 250 // The minimum angle is assumed to be 0
#define RC_MAX_MAGNITUDE 1000 // The minumum output and maximum output are assumed to be the same magnitude, just opposite signs.

int uabout(char* argv[]) {
    // Cool little ascii art made with a program called figlet, gotta
    // escape the special characters though

    // Remember, printf has a 80 char limit at a time
    // This eats a tonne of sram, TODO switch this into a PROGMEM string
    Console->out->printf("  ___|    \\    ____| |     ____| _ \\   _  \\ "
            " ___| ____| \\ \\  / |     \n");
    Console->out->printf(" |       _ \\   __|   |     |    |   | |   | |"
            "     __|    \\  /  |     \n");
    Console->out->printf(" |   |  ___ \\  |     |     __|  |   | __ <  |"
            "     |         \\  |     \n");
    Console->out->printf("\\____|_/    _\\_____|_____|_|   \\___/ _| \\_"
            "\\\\____|_____|  _/\\_\\_____| \n\n\n");

    Console->out->printf("AshCon Version 0.021 \n");

	Console->out->printf("Compiled at __DATE__ __TIME__.\n");
    Console->ufunc_dump();

    return 0;
}

/** RC Poll all command line debug function
 *
 * Prints the current value of all the controllers channels to the main serial
 * line. Ends when a 'q' character is encountered on the command line
 */
int urcpollall(char* argv[]) {
    char c = '1';

    while( c != 'q' ) {
        updateControllerValues( radio );
        Console->out->printf("LS: (%d,%d) RS: (%d,%d) SW[%d] AUX[%d]\n",
                getAxisOutput( radio->LSX ),
                getAxisOutput( radio->LSY ),
                getAxisOutput( radio->RSX ),
                getAxisOutput( radio->RSY ),
                getSwitchOutput( radio->gearSwitch ),
                getAxisOutput( radio->AUX )
                    );

        if( Serial.available() ) c = Serial.read();
    }
}


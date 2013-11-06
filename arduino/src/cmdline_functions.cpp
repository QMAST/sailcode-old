#include "cmdline_functions.h"

int uabout(char* argv[]) {
    // Cool little ascii art made with a program called figlet, gotta
    // escape the special characters though

    // Remember, printf has a 80 char limit at a time
    // This eats a tonne of sram, TODO switch this into a PROGMEM string
    Console->out->printf("  ___|    \\    ____| |     ____| _ \\   _  \\ "
            " ___| ____| \\ \\  / |     \n\r");
    Console->out->printf(" |       _ \\   __|   |     |    |   | |   | |"
            "     __|    \\  /  |     \n\r");
    Console->out->printf(" |   |  ___ \\  |     |     __|  |   | __ <  |"
            "     |         \\  |     \n\r");
    Console->out->printf("\\____|_/    _\\_____|_____|_|   \\___/ _| \\_"
            "\\\\____|_____|  _/\\_\\_____| \n\r\n\r\n\r");

    Console->out->printf("AshCon Version 0.021 \n\r");

    return 0;
}

int uhelp(char* argv[]) {
}

int urcpollall(char* argv[]) {
    char c = '1';

    while( c != 'q' ) {
        updateControllerValues( radio );
        Console->out->printf("LS: (%d,%d) RS: (%d,%d) SW[%d] AUX[%d]\r\n",
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


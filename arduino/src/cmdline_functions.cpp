#include "cmdline_functions.h"

int uabout(char* argv[]) {
    // Cool little ascii art made with a program called figlet, gotta
    // escape the special characters though

    // Remember, printf has a 80 char limit at a time
    // This eats a tonne of sram, TODO switch this into a PROGMEM string
    Console->out->printf("  ___|    \\    ____| |     ____| _ \\   _ \\ "
            "___| ____| \\ \\  / |     \n\r");
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

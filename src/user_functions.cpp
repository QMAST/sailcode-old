#include "user_functions.h"

// Ugh, its using Serial directly
int utest_function(char* argv[]) {
    Serial.print("The test function has been activated,\n\r"
    "I have just been handed this: ");
    Serial.println(argv[1]);
    Serial.print("The ID of this function is: ");
    Serial.println(argv[0]);

}

int ucheck_mem(char* argv[]) {
    Console->printf("Memory Free: %d\n\r", freeMemory());

    return 0;
}

int uhelp(char* argv[]) {
    Console->printf("Command prompt: Type stuff in, yo \n\r\n\r"
            "- checkmem\n\r");
    Console->printf("- test \n\r"
            "- help \n\r"
            "- about\n\r");
    return 0;
}

int uabout(char* argv[]) {
    // Cool little ascii art made with a program called figlet, gotta
    // escape the special characters though

    // Remember, printf has a 128 char limit at a time
    Console->printf("  ___|    \\    ____| |     ____| _ \\   _ \\   ___| ____| \\ \\  / |     \n\r");
    Console->printf(" |       _ \\   __|   |     |    |   | |   | |     __|    \\  /  |     \n\r");
    Console->printf(" |   |  ___ \\  |     |     __|  |   | __ <  |     |         \\  |     \n\r");
    Console->printf("\\____|_/    _\\_____|_____|_|   \\___/ _| \\_\\\\____|_____|  _/\\_\\_____| \n\r\n\r\n\r");

    Console->printf("AshCon Version 0.01 \n\r");

    return 0;
}

#include "user_functions.h"

// Ugh, its using Serial directly
int test_function(char* argv[]) {
    Serial.print("The test function has been activated,\n\r"
    "I have just been handed this: ");
    Serial.println(argv[1]);
    Serial.print("The ID of this function is: ");
    Serial.println(argv[0]);

}

int check_mem(char* argv[]) {
    mycon->printf("Memory Free: %d\n\r", freeMemory());

    return 0;
}

int uhelp(char* argv[]) {
    mycon->printf("Command prompt: Type stuff in, yo \n\r\n\r"
            "- checkmem\n\r");
    mycon->printf("- test \n\r"
            "- help \n\r"
            "- about\n\r");
    return 0;
}

// Really hack serial terminal, mega only, yo
#ifdef BOARD_MEGA
int usmon(char* argv[]) {
    mycon->printf("SERIAL MONITOR ENGAGE\n\r");
    while( Serial.peek() != '-' ) {
        if( Serial.available() ) {
            Serial.print((char)Serial.peek());
            Serial1.print((char)Serial.read());
        }
        if( Serial1.available() ) {
            Serial.print((char)Serial1.read());
        }
    }
    mycon->printf("SERIAL MONITOR DISENGAGE\n\r");

    Serial.println();
}
#endif

int urep(char* argv[]) {
    mycon->repeat();
    return 0;
}

#ifdef BOARD_MEGA
int uservo(char* argv[]) {
    tservo->setPosition(7, 10);
    delay(500);
    tservo->setPosition(7, 240);
    delay(500);
}
#endif

int uabout(char* argv[]) {
    // Cool little ascii art made with a program called figlet, gotta
    // escape the special characters though

    // Remember, printf has a 128 char limit at a time
    mycon->printf("  ___|    \\    ____| |     ____| _ \\   _ \\   ___| ____| \\ \\  / |     \n\r");
    mycon->printf(" |       _ \\   __|   |     |    |   | |   | |     __|    \\  /  |     \n\r");
    mycon->printf(" |   |  ___ \\  |     |     __|  |   | __ <  |     |         \\  |     \n\r");
    mycon->printf("\\____|_/    _\\_____|_____|_|   \\___/ _| \\_\\\\____|_____|  _/\\_\\_____| \n\r\n\r\n\r");

    mycon->printf("AshCon Version 0.01 \n\r");

    return 0;
}

#include "user_functions.h"

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
    mycon->printf(
"  ___|    \\    ____| |     ____| _ \\   _ \\   ___| ____| \\ \\  / |     \n\r"
" |       _ \\   __|   |     |    |   | |   | |     __|    \\  /  |     \n\r"
" |   |  ___ \\  |     |     __|  |   | __ <  |     |         \\  |     \n\r"
"\\____|_/    _\\_____|_____|_|   \\___/ _| \\_\\\\____|_____|  _/\\_\\_____| \n\r"
    );

    return 0;
}

// Really hack serial terminal
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

int urep(char* argv[]) {
    mycon->repeat();
    return 0;
}

int uservo(char* argv[]) {
    tservo->setPosition(7, 10);
    delay(500);
    tservo->setPosition(7, 240);
    delay(500);
}


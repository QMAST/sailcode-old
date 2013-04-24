#include "sketch.h"

int test_function(char* argv[]);
int check_mem(char* argv[]);
int uhelp(char* argv[]);
int usmon(char* argv[]);
int uservo(char* argv[]);
int urep(char* argv[]);

void setup() {
    Serial.begin(115200);
    Serial1.begin(9600);
    Serial2.begin(9600);

    testk = new kstring( 100 );
    mycon = new ashcon(&Serial);
    mycon->user_function_register("test", &test_function);
    mycon->user_function_register("checkmem", &check_mem);
    mycon->user_function_register("help", &uhelp);
    mycon->user_function_register("smon", &usmon);
    mycon->user_function_register("servo", &uservo);
    mycon->user_function_register("r", &urep);

    pinMode(3, OUTPUT);
    tservo = new PololuMSC(&Serial2, 3);

    pinMode(LED_PIN, OUTPUT);

    Serial.println("Testing console");
}

void loop() {

    mycon->command_prompt();

    /*mycon->printf("> ");*/
    /*mycon->get_line();*/
    /*mycon->get_line_splitline();*/
    /*mycon->command_arg_append("This is a test");*/
    /*mycon->command_arg_append("Another string");*/

    /*mycon->ufunc_dump();*/
    /*mycon->printf("CALLING: %s\n\r", mycon->command_arg_list[0]);*/
    /*mycon->user_function_call(mycon->command_arg_list[0]);*/

    /*mycon->command_arg_dump_debug();*/
    /*mycon->command_arg_clear();*/

    /*mycon->printf("Loopend. \n\r");*/
    /*delete mycon;*/
    /*delete testk;*/
    /*while( true ) delay( 100 );*/
}

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

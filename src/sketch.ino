#include "sketch.h"

int test_function(char* argv[]);

void setup() {
    Serial.begin(115200);

    testk = new kstring( 100 );
    mycon = new ashcon(&Serial);
    mycon->user_function_register("test", &test_function);

    pinMode(LED_PIN, OUTPUT);

    Serial.println("Testing console");
}

void loop() {

    /*mycon->printf("> ");*/
    /*mycon->get_line();*/
    /*mycon->get_line_splitline();*/
    /*mycon->command_arg_append("This is a test");*/
    /*mycon->command_arg_append("Another string");*/

    mycon->ufunc_dump();

    /*mycon->command_arg_dump_debug();*/
    /*mycon->command_arg_clear();*/

    mycon->printf("Loopend. \n\r");
    delete mycon;
    delete testk;
    while( true ) delay( 100 );
}

int test_function(char* argv[]) {
    Serial.println("The test function has been activated");
}

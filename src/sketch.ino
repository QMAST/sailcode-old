#include "sketch.h"

int test_function(char* argv[]);
int check_mem(char* argv[]);

void setup() {
    Serial.begin(115200);

    testk = new kstring( 100 );
    mycon = new ashcon(&Serial);
    mycon->user_function_register("test", &test_function);
    mycon->user_function_register("checkmem", &check_mem);

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

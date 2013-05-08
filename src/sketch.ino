#include "sketch.h"

// The bare basics of an expected setup

void setup() {
    Serial.begin(115200);
    Console = new ashcon(&Serial);

    Console->user_function_register("about", &uabout);
    Console->user_function_register("help",  &uhelp);
    Console->user_function_register("mem",   &ucheck_mem);
    Console->user_function_register("test",  &utest_function);
}

void loop() {
    Console->command_prompt();

}


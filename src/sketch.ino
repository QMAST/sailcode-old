#include "sketch.h"


void setup() {
    Serial.begin(115200);
    #ifdef BOARD_MEGA
    Serial1.begin(9600);
    Serial2.begin(9600);
    #endif

    testk = new kstring( 100 );
    mycon = new ashcon(&Serial);

    mycon->user_function_register("test", &test_function);
    mycon->user_function_register("checkmem", &check_mem);
    mycon->user_function_register("help", &uhelp);
    mycon->user_function_register("r", &urep);
    mycon->user_function_register("about", &uabout);


#ifdef BOARD_MEGA
    mycon->user_function_register("smon", &usmon);
    mycon->user_function_register("servo", &uservo);
#endif

    pinMode(3, OUTPUT);
#ifdef BOARD_MEGA
    tservo = new PololuMSC(&Serial2, 3);
#endif

    pinMode(LED_PIN, OUTPUT);

    Serial.println("Testing console");
}

void loop() {

    mycon->command_prompt();

}


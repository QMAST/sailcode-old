#include "sketch.h"

void setup() {
    Serial.begin(9600);

    testk = new kstring( 100 );
    mycon = new ashcon(&Serial);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    Serial.println("Testing console");

    mycon->printf("This is a %s\n\r", (char*) "test");


    mycon->printf("Shutdown. \n\r");
    delete mycon;
    delete testk;
    while( true ) delay( 100 );
}

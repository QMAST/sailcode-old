#include <Arduino.h>

#include "ashcon.h"

ashcon* Console;

int mode =0;
void piInterrupt();
int dispatchRequest(int argc, char* argv[]);
void setup() {
	//Initialize console
	Serial.begin(115200);
    Console = new ashcon(&Serial);
    Console->user_function_register("req", &dispatchRequest);

	//Setup interrupts
    attachInterrupt(0, piInterrupt, FALLING);

}

void loop() {
	switch(mode) {
		case 0:
			delay(200);
		break;
		case 1:
			Console->command_prompt();
			mode =0;
		break;
	}
}


void piInterrupt() {
	mode =1;
}

int dispatchRequest(int argc, char* argv[]) {
	//For this test, just return engough to make it work properly.
	Serial.println("1.0, 3.1415");
	return 0;
}
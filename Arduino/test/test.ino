#include <Arduino.h>
#include <ashcon.h>

ashcon* Console;
int mode = 0;
int counter = 0;
void setup() {
	Console = new ashcon(&Serial);
	Console->user_function_register("req", &returnGarbage);

	attachInterrupt(0, piInterrupt, RISING);
}

void loop() {
	switch(mode) {
		case 0:
		//Figure out something to do here
		break;
		case 1:
			Console->command_prompt();
			mode=0;
		break;

	}
}

void piInterrupt() {
	mode =1;
}

int returnGarbage(int argc, char* argv[]) {
	Serial.print("Interrupt number ");
	Serial.print(counter);
	Serial.print(": ");
	counter++;
	for(int i=0; i<argc; i++){
		Serial.print(argv[i]);
		Serial.print(",");
		Serial.flush();
	}
	Serial.print("\n\r");
	return 0;
}
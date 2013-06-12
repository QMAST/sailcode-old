#include <Arduino.h>
#include <ashcon.h>

ashcon* Console;
volatile int mode = 0;
int counter = 0;
void setup() {
        Serial.begin(115200);
	Console = new ashcon(&Serial);
	Console->user_function_register("req", &returnGarbage);
        pinMode(13, OUTPUT);
        attachInterrupt(0, piInterrupt, LOW);
}

void loop() {
	switch(mode) {
		case 0:
		//Figure out something to do here
                    delay(200);
		break;
		case 1:
			Console->command_prompt();
			mode=0;
                        digitalWrite(13, LOW);
		break;

	}
}

void piInterrupt() {
	mode =1;
        digitalWrite(13, HIGH);
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

#include <Arduino.h>
int mode=0;

void setup() {
	Serial.begin(115200);
    attachInterrupt(0, piInterrupt, RISING);
}

void loop() {
	if(mode==0){
		delay(250);
	} else{
		Serial.println("Interrupt Received!!");
		mode=0;
	}
}

void piInterrupt() {
    digitalWrite(13, HIGH);
	mode = 1;
}

#include <Arduino.h>

int counter=0;
void setup(){
	Serial.begin(115200);
	delay(500);
}

void loop(){
	Serial.print("Printing line ");
	Serial.println(counter);
	Serial.flush();
        counter++;
	delay(250);
}

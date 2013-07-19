#include <Arduino.h>
#include <compass.h>
#include <airmar.h>
//Need to test that the multiplexor is working, and switching between the two sensors works as excpected.
#define MULTIPLEX_PIN1 30
#define MULTIPLEX_PIN2 31
#define ENABLE 50

Compass* c;
Airmar* a;

int stat;

void setup() {
	Serial.begin(115200);//USB Serial
	Serial2.begin(9600);

	c = new Compass("compass", &Serial2);
	a = new Airmar("airmar", &Serial2);

        pinMode(30, OUTPUT);
        pinMode(31, OUTPUT);
        pinMode(ENABLE, OUTPUT);
        digitalWrite(ENABLE, HIGH);

	delay(1000);
	Serial.println("Initializing...");
}

void loop () {
	//Update the airmar, then update the compass.
	//Print the values for both.
	clearBuffer();
	digitalWrite(MULTIPLEX_PIN1, HIGH);
	digitalWrite(MULTIPLEX_PIN2, LOW);
	Serial2.begin(4800);
	delay(100);
	stat = a->update();
	if(stat==0){
		Serial.print("Airmar updated: ");
		Serial.print("lat-");
		Serial.print(a->lat);
		Serial.print(" lon-");
		Serial.print(a->lon);
		Serial.print(" windSpeed-");
		Serial.print(a->windSpeed);
		Serial.print(" windDirection-");
		Serial.println(a->windDirection);
	} else {
		Serial.println("Airmar Failed to update");
	}

	//Get compass values
	clearBuffer();
	digitalWrite(MULTIPLEX_PIN1, LOW);
	digitalWrite(MULTIPLEX_PIN2, LOW);
	Serial2.begin(9600);
	delay(100);

	stat = c->update();
	if(stat==0) {
		Serial.print("Compass updated: ");
		Serial.print(" heading-");
		Serial.print(c->compassHeading);
		Serial.print(" pitch-");
		Serial.print(c->pitch);
		Serial.print(" roll-");
		Serial.print(c->roll);
		Serial.print(" dip-");
		Serial.println(c->dip);
	} else {
		Serial.println("Compass failed to update");
	}
}

void clearBuffer(){
	//Switch to an unconnected pin
	digitalWrite(MULTIPLEX_PIN1, LOW);
	digitalWrite(MULTIPLEX_PIN2, HIGH);

	while(Serial2.available()>0){
		Serial2.read();
	}
}

#include "angleSensor.h"

AngleSensor::AngleSensor(int pin, const char* id) {
	this->pin = pin;
	int idLen = strlen(id);
	this->id = (char*) malloc(sizeof(char)*idLen);
	strcpy(this->id, id);
	
	this->tempRate = 1;
	
	this->varList = NULL;
	addVar(INT, "angle", &angle);
	
	this->angle = 0;
	this->update();
}

int AngleSensor::update() {
	int val = analogRead();
	//1023=5V, 0=0V. Need to map 0.5V to -180, and 4.5V to 180
	//204.6 points per Volt
	//90 degrees per Volt.
	//So we have 204.6/90 points per degree.
	//or 90/204.6 degrees per point.
	//This means that at 2.5 volts, we are getting 225 degrees. 
	//We want that to be 0
	val = int((double(val)*0.4399) - 225);
	this->temp = 0;
	return val;
}

int AngleSensor::getTemp(unsigned long time) {
	unsigned long timeDif = time-this->prevTime;
	this->temp += (int)(timeDif*this->tempRate);
	return this->temp;
}

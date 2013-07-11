#ifndef _COMPASS_H_
#define _COMPASS_H_
#define MULTIPLEX_PIN1 28
#define MULTIPLEX_PIN2 29

#include <Arduino.h>
#include <stdlib.h>
#include "nmea.h"
#include <sensor.h>

class Compass : public Sensor {
public:
	Compass(const char* id, Stream* lineIn);
	~Compass();
	int update();
	int getTemp(unsigned long time);
	
	double compassHeading;
	char compassStatus;
	
private:
	int tempRate;//Relative rate at which the temperature should increase.
	unsigned long prevTime;
	int temp;
};

#endif

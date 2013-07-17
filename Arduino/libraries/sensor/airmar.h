
#ifndef _AIRMAR_H_
#define _AIRMAR_H_
#define MULTIPLEX_PIN1 28
#define MULTIPLEX_PIN2 29

#include <Arduino.h>
#include <stdlib.h>
#include "nmea.h"
#include <sensor.h>

class Airmar : public Sensor {
public:
	Airmar(const char* id, Stream* lineIn);
	~Airmar();
	int update();
	int getTemp(unsigned long time);
	
	double heading, windDirection;
	
	int tempRate;//Relative rate at which the temperature should increase.
	double lat, lon;//Latitude and Longitude
	double var, dev; //Heading, variation, deviation
	double windSpeed;//Wind speed, in knots
	double courseOverGround, speedOverGround;//Speed in knots
	unsigned long prevTime;
	int temp;
};

#endif


#ifndef _AIRMAR_H_
#define _AIRMAR_H_

#include <Arduino.h>
#include <stdlib.h>
#include "nmea.h"
#include <sensor.h>

class Airmar : public Sensor {
public:
	Airmar(const char* id, Stream* lineIn);
	~Airmar();
	int update();
	int getTemp(unsigned long temp);
private:
	int tempRate;//Relative rate at which the temperature should increase.
	double lat, lon;//Latitude and Longitude
	double heading, var, dev; //Heading, variation, deviation
	double windSpeed, windHeading;//Wind speed, in knots
	double courseOverGround, speedOverGround;//Speed in knots
	unsigned long prevTime;
	int temp;
};

#endif

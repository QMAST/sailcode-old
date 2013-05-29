
#ifndef _AIRMAR_H_
#define _AIRMAR_H_

#include <Arduino.h>
#include <stdlib.h>
#include "nmea.h"
#include "sensor.h"

class Airmar : public Sensor {
public:
	Airmar(char* id, Stream* lineIn);
	~Airmar();
	virtual int update();
	virtual int getTemp(int temp);
private:
	const int tempRate = 4;//Relative rate at which the temperature should increase.
	double lat, lon;//Latitude and Longitude
	double heading, var, dev; //Heading, variation, deviation
	double windSpeed, windHeading;//Wind speed, in knots
	double courseOverGround, speedOverGround;//Speed in knots
	unsigned long prevTime = 0;
	int temp = 0;
};

#endif

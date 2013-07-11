#ifndef _ANGLE_SENSOR_H
#define _ANGLE_SENSOR_H

#include <Arduino.h>
#include <sensor.h>

class AngleSensor : public Sensor {
public:
	AngleSensor(int pin, const char* id);
	~AngleSensor();
	int update();
	int getTemp(unisgned long time);
	
	int angle;

private:
	int tempRate;
	int pin;
	unsigned long prevTime;
	int temp;
};

#endif
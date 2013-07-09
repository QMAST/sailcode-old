#ifndef _ANGLE_SENSOR_H
#define _ANGLE_SENSOR_H

#include <Arduino.h>

class AngleSensor {
public:
	AngleSensor(int pin);
	int getAngle();

private:
	int pin;
};

#endif
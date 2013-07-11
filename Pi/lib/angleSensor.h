#ifndef _ANGLE_SENSOR_H
#define _ANGLE_SENSOR_H

#define BUFFER_SIZE 20
#include <time.h>
#include <float.h>
#include "buffer.h"
#include "logging.h"
#include "arduinoCom.h"

#include <string>

class AngleSensor{
public:
	AngleSensor(ArduinoCom* lineIn);

	float getAngles(int* motor1, int* motor2, int* mast);

private:
	ArduinoCom* ard;
	
	Buffer<int> *motor1;
	Buffer<int> *motor2;
	Buffer<int> *mast;
	Buffer<time_t> *atime;
};


#endif
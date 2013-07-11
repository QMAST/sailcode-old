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
	ArduinoCom* ard(BUFFER_SIZE);
	Buffer<int> motor1(BUFFER_SIZE);
	Buffer<int> motor2(BUFFER_SIZE);
	Buffer<int> mast(BUFFER_SIZE);
	Buffer<time_t> time(BUFFER_SIZE);
};


#endif
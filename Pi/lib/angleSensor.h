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

	float getValues(int* motor1, int* motor2, int* mast);

private:
	ArduinoCom* ard;
	Buffer<int> motor1 = Buffer<int>(BUFFER_SIZE);
	Buffer<int> motor2 = Buffer<int>(BUFFER_SIZE);
	Buffer<int> mast = Buffer<int>(BUFFER_SIZE);
	Buffer<time_t> time = Buffer<time_t>(BUFFER_SIZE);
};


#endif
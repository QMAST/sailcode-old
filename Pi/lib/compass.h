#ifndef _COMPASS_H
#define _COMPASS_H

#define BUFFER_SIZE 20
#include <time.h>
#include <float.h>
#include "buffer.h"
#include "logging.h"
#include "arduinoCom.h"
#include <string>

class Compass{
public:
	Compass(ArduinoCom* lineIn);

	float getValues(float* heading, float* pitch, float* roll, float* dip);
private:
	//Arduino Connection.
	ArduinoCom* ard;

	//Buffers to hold all the data, over a period of time.
	Buffer<float> heading = Buffer<float>(BUFFER_SIZE);
	Buffer<float> pitch = Buffer<float>(BUFFER_SIZE);
	Buffer<float> roll = Buffer<float>(BUFFER_SIZE);
	Buffer<float> dip = Buffer<float>(BUFFER_SIZE);
	Buffer<time_t> time = Buffer<time_t>(BUFFER_SIZE);
};

#endif
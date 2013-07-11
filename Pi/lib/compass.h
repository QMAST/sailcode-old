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
	Buffer<float> *heading;
	Buffer<float> *pitch;
	Buffer<float> *roll;
	Buffer<float> *dip;
	Buffer<time_t> *time;
};

#endif
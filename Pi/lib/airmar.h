#ifndef _AIRMAR_H
#define _AIRMAR_H

#define BUFFER_SIZE 20
#include <time.h>
#include <float.h>
#include "buffer.h"
#include "float.h"
#include "arduinoCom.h"
#include <string>

class Airmar {
public:
	Airmar(ArduinoCom* lineIn);
	float getGPS(float* lat, float* lon);
	float getWind(float* speed, float* heading);
	float getCompass(float* heading, float* variation, float* deviation);
private:
	//Arduino connection
	ArduinoCom* ard;
	
	//GPS information buffers
	Buffer<float> gLat(BUFFER_SIZE);
	Buffer<float> gLon(BUFFER_SIZE);
	Buffer<time_t> gTime(BUFFER_SIZE);

	//Wind information buffers
	Buffer<float> wSpeed(BUFFER_SIZE);
	Buffer<float> wHeading(BUFFER_SIZE);
	Buffer<time_t> wTime(BUFFER_SIZE);

	//Compass information buffers
	Buffer<float> cHeading(BUFFER_SIZE);
	Buffer<float> cVar(BUFFER_SIZE);
	Buffer<float> cDev(BUFFER_SIZE);
	Buffer<time_t> cTime(BUFFER_SIZE);
};

#endif
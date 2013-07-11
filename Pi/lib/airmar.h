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
	Buffer<float> gLat = Buffer<float>(BUFFER_SIZE);
	Buffer<float> gLon = Buffer<float>(BUFFER_SIZE);
	Buffer<time_t> gTime = Buffer<time_t>(BUFFER_SIZE);

	//Wind information buffers
	Buffer<float> wSpeed = Buffer<float>(BUFFER_SIZE);
	Buffer<float> wHeading = Buffer<float>(BUFFER_SIZE);
	Buffer<time_t> wTime = Buffer<time_t>(BUFFER_SIZE);

	//Compass information buffers
	Buffer<float> cHeading = Buffer<float>(BUFFER_SIZE);
	Buffer<float> cVar = Buffer<float>(BUFFER_SIZE);
	Buffer<float> cDev = Buffer<float>(BUFFER_SIZE);
	Buffer<time_t> cTime= Buffer<time_t>(BUFFER_SIZE);
};

#endif
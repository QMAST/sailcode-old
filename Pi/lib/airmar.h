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
	Buffer<float> gLat;
	Buffer<float> gLon;
	Buffer<time_t> gTime;

	//Wind information buffers
	Buffer<float> wSpeed;
	Buffer<float> wHeading;
	Buffer<time_t> wTime;

	//Compass information buffers
	Buffer<float> cHeading;
	Buffer<float> cVar;
	Buffer<float> cDev;
	Buffer<time_t> cTime;
};

#endif
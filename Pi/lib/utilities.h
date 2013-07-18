#ifndef _UTILITIES_H
#define _UTILITIES_H
#include <math.h>

#define RT2PI 2.5066282746310005 //Square root of 2Pi
#define DELTA 5
#define PI 3.14159265

#typedef struct GPSPoint
{
	float lat;
	float lon;
} GPSPoint;  

class Utilities {
public:
	static int getBearing(float start, float end);
};

#endif
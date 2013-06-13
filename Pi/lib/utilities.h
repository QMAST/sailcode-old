#ifndef _UTILITIES_H
#define _UTILITIES_H
#include <cmath>

#define RT2PI 2.5066282746310005 //Square root of 2Pi
#define DELTA 5


class Utilities {
public:
	static double reconcileAngle(double* data, double* confidence, int num);
};

#endif
#ifndef _UTILITIES_H
#define _UTILITIES_H
#include <math.h>

#define RT2PI 2.5066282746310005 //Square root of 2Pi
#define DELTA 5
#define PI 3.14159265
#define NAV_DEGREES 5 //degree increments used for nav_score
#define NAV_ELEMENTS 360/NAV_DEGREES

#define WAYPOINT_RADIUS 1 //acceptable radius around waypoint

typedef struct
{
	float lat;
	float lon;
} GPSPoint;  

typedef struct Score
{
	int direction;
	int score;
} Score;

class Utilities {
public:
	static int getBearing(GPSPoint* start, GPSPoint* end); // returns direction to get to end from start
	static bool withinRange(GPSPoint* current, GPSPoint* waypoint); //returns whether you are within range of waypoint
	void navScore(Score navScore[NAV_ELEMENTS], Airmar* windSensor); //updates array containing nacScore

};

#endif

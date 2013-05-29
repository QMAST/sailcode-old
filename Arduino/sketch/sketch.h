#ifndef _sketch_h
#define _sketch_h

#include <sensor.h>
#include <ashcon.h>
#include <airmar.h>

typedef struct SensorLink {
	struct SensorLink* next;
	Sensor* s;
} SensorLink;

int mode = 0;
Airmar* airmar;
ashcon* Console;
SensorLink* sensorList;

void addToList(Sensor* item);
int dispatchRequest(int argc, char* argv[]);
Sensor* getHottestSensor();
void piInterrupt();
#endif
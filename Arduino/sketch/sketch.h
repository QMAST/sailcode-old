#ifndef _sketch_h
#define _sketch_h

#include <Arduino.h>
#include <ashcon.h>
#include <airmar.h>
#include <sensor.h>

#define RCPIN 8
#define KILLPIN 10
typedef struct SensorLink {
	struct SensorLink* next;
	Sensor* s;
} SensorLink;

int mode = 0;
int spd;
Airmar* airmar;
ashcon* Console;
SensorLink* sensorList;

void addToList(Sensor* item);
int dispatchRequest(int argc, char* argv[]);
Sensor* getHottestSensor();
void piInterrupt();
#endif

//Abstract interface for sensors interfacing with the arduino.
//Will allow the arduino to loop through all the sensors to update them more efficiently

#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <Arduino.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
I was worried about this conflicting with the 
same enum in logging.h, but then realized this is running 
on the Arduino, and the other one is on the raspberry Pi.
*/
typedef enum {
	INT,
	DOUBLE,
	CHAR,
	FLOAT,
	STRING
} DataType;

class Sensor {
public: 
	char** getVariables(int argc, char* argv[]);
	virtual int update() = 0;
	virtual int getTemp(unsigned long temp) = 0;
	char* id;
protected:
	typedef struct DataSource{
		DataType type;
		char* id;
		void* data;
		DataSource* next;
	} DataSource;

	DataSource* varList;
	int addVar(DataType type, const char* id, void* data);
	Stream* lineIn;
};

#endif

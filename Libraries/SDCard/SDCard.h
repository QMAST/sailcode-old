/* SDCard.h

	For interacting with the SD Card shield, used for datalogging. Eventually will
	include GPS functionality as well, but as it is a back-up gps, it will be
	programmed later, and merely use modified code from the main GPS


	For the datalogging, the SD card needs to get information from the sensors, and
	send it as a formatted string to the SD card. The information is organized as
	### LABEL1: DATA1, LABEL2: DATA2, .... LABELN: DATAN ###  The organization of
	this depends on how flexible we want the data logging to be.  If we want to
	simply hardcode in all the data sources, then it is easy, if cumbersome, to
	write the logging function. If we want to make it more flexible, then we can
	implement a linked list of structs containing the data label, and a pointer to
	the data source variable. The data source variable could then be updated by other 
	functions which poll the hardware sources. 
	This would obviously be more intensive - both in implementation and in memory usage,
	however, it would be a lot more flexible if more sources were added, or we wanted to 
	change anything regarding how they were formatted.

	The issue with creating a list of values is that different sources have different data types - certain sources are doubles, others are longs, or ints. Would need to look carefully at this.

	In the meantime, I will implement the basic read/write and initialization functions.
*/
#ifndef SDCard_h
#define SDCard_h

#include "Arduino.h"
#include <SD.h>
#define DEBUG 0

//The different datatypes that are possible to be written to the file
 enum DataType{
	INT,
	DOUBLE,
	CHAR,
	FLOAT
};

/*
This structure is used to hold pieces of information which will be written to the SD card.
Each piece of information has a string label, a pointer to the data, and a DataType telling what type of data it is.
As well, there is a pointer to another DataSource. This allows the DataSources to be used as a linked list.
When a line is logged, the list will be looped through, and each source will be written to a line in the log.
*/
typedef struct {
	DataType type;
	char* label;
	void* data;
	DataSource* head;
} DataSource;

class SDCard
{
public:
	SDCard(int pin);
	char* getFilename();
	void addDataSource(char* label, void* data, DataType type);
	int writeLine();
private:
	int _pin;
	char* _logfile;
	DataSource* _list;
}


#endif
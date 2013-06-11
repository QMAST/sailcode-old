/*
	Class to simplify data and error logging on the Raspberry Pi, making it easy as possible to deal with data logging.
	Data logging and error logging will be saved in two separate files, to simplify parsing the data later on.
*/
#ifndef _LOGGING_H
#define _LOGGING_H

#include <string>
#include <fstream>
#include <list>
#include <sys/stat.h>
#include <time.h>

typedef enum {
	INT,
	DOUBLE,
	CHAR,
	FLOAT,
	STRING
} DataType;

class Logging
{

public:
static std::string errPath;//Path for the error log

Logging();
~Logging();
static void error(const char* src, const std::string &msg);//Log error to file pointed by errPath
int addDataSource(DataType type, const std::string &label, void* data);
int log();//write line to file.

private:

typedef struct {
	DataType type;
	std::string label;
	void* data;
} DataSource;

std::string dataPath;//Path for the data log
std::list<DataSource> sources;//List of data sources to print to file.
static std::string getTimeStamp();
int addDataSource(DataSource* src);



};

#endif

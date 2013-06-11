#include <string.h>
#include <stdlib.h>

#include "logging.h"
#include "arduinoCom.h"
//#include "gaelforce.h"
//#include "environment.h"


int main(int argc, char* argv[]) {
	//Simple data logging test.
	double lat, lon;
	double heading, var, dev;
	double windSpeed, windHeading;
	double courseOverGround, speedOverGround;
	std::string resp;
	int stat=0;
	int pin= 0;
	char* buf;
	Logging* log = new Logging();
	ArduinoCom ard("/dev/ttyACM0",pin);
	log->addDataSource(DOUBLE, "lat", &lat);
	log->addDataSource(DOUBLE, "lon", &lon);
	log->addDataSource(DOUBLE, "heading", &heading);
	log->addDataSource(DOUBLE, "var", &var);
	log->addDataSource(DOUBLE, "dev", &dev);
	log->addDataSource(DOUBLE, "windSpeed", &windSpeed);
	log->addDataSource(DOUBLE, "windHeading", &windHeading);
	log->addDataSource(DOUBLE, "courseOG", &courseOverGround);
	log->addDataSource(DOUBLE, "speedOG", &speedOverGround);
	
	while(true) {
		stat = ard.requestVariables("airmar","lat lon", resp);
		if(stat==0){ 
			//need to parse the variables string into the appropriate slots.
			buf = new char[resp.length()];
			strcpy(buf, resp.c_str());
			lat = atof(strtok(buf, ","));
			lon = atof(strtok(NULL, ","));

			delete[] buf;
		}
		stat = ard.requestVariables("airmar", "heading var dev", resp);
		if(stat==0) {
			buf = new char[resp.length()];
			strcpy(buf, resp.c_str());

			heading = atof(strtok(buf, ","));
			var = atof(strtok(NULL, ","));
			dev = atof(strtok(NULL, ","));

			delete[] buf;
		}
		stat = ard.requestVariables("airmar", "windSpeed windHeading courseOverGround speedOverGround", resp);
		if(stat==0) {
			buf = new char[resp.length()];
			strcpy(buf, resp.c_str());
			windSpeed = atof(strtok(buf, ","));
			windHeading = atof(strtok(NULL, ","));
			courseOverGround = atof(strtok(NULL, ","));
			speedOverGround = atof(strtok(NULL, ","));

			delete[] buf;
		}
		log->log();
	}
}



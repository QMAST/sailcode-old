#include <string.h>
#include <stdlib.h>
#include "airmar.h"
#include "logging.h"
#include "arduinoCom.h"
#include "compass.h"

//#include "gaelforce.h"
//#include "environment.h"


int main(int argc, char* argv[]) {
	Logging::init();
	ArduinoCom ard("/dev/ttyACM0",pin);
	
	Airmar airmar(&ard);
	Compass compass(&ard);
	
	//Simple data logging test.
	float *lat, *lon;
	float *airmarHeading, *airmarVar, *airmarDev;
	float *windSpeed, *windDirection;
	float *compassHeading, *compassPitch, *compassRoll, *compassDip;
	std::string resp;
	int stat=0;
	int pin= 2;
	char* buf;
	
	
	Logging::addDataSource(DOUBLE, "lat", lat);
	Logging::addDataSource(DOUBLE, "lon", lon);
	Logging::addDataSource(DOUBLE, "airmarHeading", airmarHeading);
	Logging::addDataSource(DOUBLE, "airmarVar", airmarVar);
	Logging::addDataSource(DOUBLE, "airmarDev", airmarDev);
	Logging::addDataSource(DOUBLE, "windSpeed", windSpeed);
	Logging::addDataSource(DOUBLE, "windDirection", windDirection);
	Logging::addDataSource(DOUBLE, "compassHeading", compassHeading);
	Logging::addDataSource(DOUBLE, "compassVar", compassVar);
	Logging::addDataSource(DOUBLE, "compassDev", compassDev);
	while(true) {
		
		airmar.getGPS(lat, lon);
		airmar.getWind(windSpeed, windDirection);
		airmar.getCompass(airmarHeading, airmarVar, airmarDev);

		compass.getValues(compassHeading, compassPitch, compassRoll, compassDip);

		Logging::log();

		usleep(1000*5000);
	}
}



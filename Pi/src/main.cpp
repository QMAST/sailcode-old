#include <string.h>
#include <stdlib.h>
#include <string>
#include "airmar.h"
#include "logging.h"
#include "arduinoCom.h"
#include "compass.h"
#include "angleSensor.h"
#include <iostream>
#include "utilities.h"

//#include "gaelforce.h"
//#include "environment.h"

using namespace std;

int main(int argc, char* argv[]) {
	Logging::init();
	int pin =2;
	ArduinoCom* ard = new ArduinoCom("/dev/ttyACM0", pin);
	
	Airmar airmar(ard);
	Compass compass(ard);
	AngleSensor angles(ard);
	
	//Simple data logging test.
	float *lat = new float;
	float *lon = new float;

	float *airmarHeading  = new float;
	float *airmarVar = new float;
	float *airmarDev = new float;

	float *windSpeed = new float;
	float *windDirection = new float;
	float *compassHeading = new float;
	float *compassPitch = new float;
	float *compassRoll = new float;
	float *compassDip = new float;
	int stat=0;
	string resp="";
	
	
	Logging::addDataSource(FLOAT, "lat", lat);
	Logging::addDataSource(FLOAT, "lon", lon);
	Logging::addDataSource(FLOAT, "airmarHeading", airmarHeading);
	Logging::addDataSource(FLOAT, "airmarVar", airmarVar);
	Logging::addDataSource(FLOAT, "airmarDev", airmarDev);
	Logging::addDataSource(FLOAT, "windSpeed", windSpeed);
	Logging::addDataSource(FLOAT, "windDirection", windDirection);
	Logging::addDataSource(FLOAT, "compassHeading", compassHeading);
	Logging::addDataSource(FLOAT, "compassPitch", compassPitch);
	Logging::addDataSource(FLOAT, "compassRoll", compassRoll);
	Logging::addDataSource(FLOAT, "compassDip", compassDip);

	std::cout << "Entering main loop...\n";

	//ard->setHeading(90); //East
	while(true) {
		
		airmar.getGPS(lat, lon);
		std::cout<<"lat="<<*lat<<", lon="<<*lon<<"\n";

		//for Parkinglot testing
		/*GPSPoint here = (airmar->gLat, airmar->gLon);
		GPSPoint there = (4413.4225, 7629.2946);
		int dir = getBearing(here, there);
		ard.setHeading(dir);*/

		airmar.getWind(windSpeed, windDirection);
		std::cout<<"windSpeed="<<*windSpeed<<", windDirection="<<*windDirection<<"\n";
		
		airmar.getCompass(airmarHeading, airmarVar, airmarDev);
		std::cout<<"airmarHeading="<<*airmarHeading<<", airmarVar="<<*airmarVar<<", airmarDev="<<*airmarDev<<"\n";

		compass.getValues(compassHeading, compassPitch, compassRoll, compassDip);
		std::cout<<"compass Heading="<<*compassHeading<<", pitch="<<*compassPitch<<", roll="<<*compassRoll<<", compassDip="<<*compassDip<<"\n";

		stat = ard->requestVariables("compass","compassHeading pitch", resp);
		if(stat==0) {
			cout<<resp<<endl;
		}
		else {
			cout<<"Request failed."<<endl;
		}

		Logging::log();

		usleep(1000*5000);
	}


}



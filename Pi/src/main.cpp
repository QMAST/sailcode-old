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

#define waypointTest1 0;
#define waypointTest2 0;

bool nextWaypoint(GPSPoint* waypoint); //sail to next waypoint

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

	ard.setHeading(90); //East

	if(waypointTest2){
	//Parkinglot testing BOTH WAYS
	GPSPoint first = (4413.4334, 7629.3137);
	GPSPoint second = (4413.4225, 7629.2946);
	bool success = false;
	bool first = true;
	}

	while(true) {
		
		airmar.getGPS(lat, lon);
		std::cout<<"lat="<<*lat<<", lon="<<*lon<<"\n";


		GPSPoint here = (airmar->gLat, airmar->gLon);

		if(waypointTest1){
		//for Parkinglot testing ONE WAY
		GPSPoint there = (4413.4225, 7629.2946);
		int dir = getBearing(here, there);
		ard.setHeading(dir);
		}


		//Parkinglot testing BOTH WAYS - back and forth between 2 waypoint
		if(waypointTest2){
			success = false;
			if(first == true){
				int dir = getBearing(here, first);
				ard.setHeading(dir);
				success = withinRange(here, first);
				if(success){ first= false; }
			}
			else{
				int dir = getBearing(here, second);
				ard.setHeading(dir);
				success = withinRamge(here, second);
				if(success) {first = true;}

			}
		}

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

//can now be rewrittent to take nextPoint from waypoint class 
bool nextWaypoint(GPSPoint* waypoint){

	GPSPoint current = (airmar->gLat, airmar->gLon);
	int dir = getBearing(here, waypoint);
	ard.setHeading(dir);
	return(withinRange(current, waypoint));


}



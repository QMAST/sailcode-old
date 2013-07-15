#include <string.h>
#include <stdlib.h>
#include <string>
#include "airmar.h"
#include "logging.h"
#include "arduinoCom.h"
#include "compass.h"
#include "angleSensor.h"

//#include "gaelforce.h"
//#include "environment.h"

using namespace std;

int main(int argc, char* argv[]) {
	Logging::init();
	int pin =2;
	ArduinoCom ard("/dev/ttyACM0",pin);
	
	Airmar airmar(&ard);
	Compass compass(&ard);
	AngleSensor angles(&ard);
	
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
	int *motor1Angle = new int;
	int *motor2Angle = new int;
	int *mastAngle = new int;
	string resp;
	
	
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
	Logging::addDataSource(INT, "motor1Angle", motor1Angle);
	Logging::addDataSource(INT, "motor2Angle", motor2Angle);
	Logging::addDataSource(INT, "mastAngle", mastAngle);


	while(true) {
		
		airmar.getGPS(lat, lon);
		airmar.getWind(windSpeed, windDirection);
		airmar.getCompass(airmarHeading, airmarVar, airmarDev);

		compass.getValues(compassHeading, compassPitch, compassRoll, compassDip);

		angles.getAngles(motor1Angle, motor2Angle, mastAngle);

		Logging::log();

		usleep(1000*5000);
	}
}



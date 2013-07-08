#include "airmar.h"

Airmar::Airmar(ArduinoCom* lineIn) {
	this->ard = lineIn;

}

float getGPS(float* lat, float* lon) {
	//float* lats = this->gLat.get();
	//float* lons = this->gLon.get();
	//time_t* times = this->gTime.get();

	//First, get the variables from the arduino.
	std::string vars = "";
	int stat = this->lineIn->requestVariables("airmar", "lat lon", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
	}
	else {
		char* buf = strtok(vars.c_str(), ",");
		this->gLat.add((float) atof(buf));
		buf =strtok(NULL, ",");
		this->gLon.add((float) atof(buf));
		this->gTime.add(time(NULL));
	}

	//To-do - implement a method for computing self-confidence.
	//Right now, just return a 1 for self confidence, and return the most recent values.
	*lat = this->gLat.peak();
	*lon = this->gLon.peak();
	
	//delete[] lats;
	//delete[] lons;
	//delete[] times;

	return 1.0f;//Right now, self confidence is not implemented
}

float getWind(float* speed, float* heading) {
	std::string vars = "";
	int stat = this->lineIn->requestVariables("airmar", "windSpeed windDirection", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
	}
	else {
		char* buf = strtok(vars.c_str(), ",");
		this->wSpeed.add((float) atof(buf));
		buf =strtok(NULL, ",");
		this->wHeading.add((float) atof(buf));
		this->wTime.add(time(NULL));
	}

	*speed = this->wSpeed.peak();
	*heading = this->wHeading.peak();

	return 1.0f;
}

float getCompass(float* heading, float* variation, float* deviation) {

	std::string vars = "";
	int stat = this->lineIn->requestVariables("airmar", "heading var dev", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
	}
	else {
		char* buf = strtok(vars.c_str(), ",");
		this->cHeading.add((float) atof(buf));
		buf =strtok(NULL, ",");
		this->cVar.add((float) atof(buf));
		buf =strtok(NULL, ",");
		this->cDev.add((float) atof(buf));

		this->cTime.add(time(NULL));
	}

	*heading = this->cHeading.peak();
	*variation = this->cVar.peak();
	*deviation = this->cDev.peak();

	return 1.0f;
}
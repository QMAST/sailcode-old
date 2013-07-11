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
		int len = vars.length();
		char* str = new char[len+1];
		vars.copy(str, len);
		str[len] ='\0';

		char* buf = strtok(str, ",");
		this->gLat.add((float) atof(buf));
		buf =strtok(NULL, ",");
		this->gLon.add((float) atof(buf));
		this->gTime.add(time(NULL));

		delete[] str;
	}

	//To-do - implement a method for computing self-confidence.
	//Right now, just return a 1 for self confidence, and return the most recent values.
	*lat = this->gLat.peek();
	*lon = this->gLon.peek();
	
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
		int len = vars.length();
		char* str = new char[len+1];
		vars.copy(str, len);
		str[len] ='\0';

		char* buf = strtok(str, ",");
		this->wSpeed.add((float) atof(buf));
		buf =strtok(NULL, ",");
		this->wHeading.add((float) atof(buf));
		this->wTime.add(time(NULL));

		delete[] str;
	}

	*speed = this->wSpeed.peek();
	*heading = this->wHeading.peek();

	return 1.0f;
}

float getCompass(float* heading, float* variation, float* deviation) {

	std::string vars = "";
	int stat = this->lineIn->requestVariables("airmar", "heading var dev", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
	}
	else {
		int len = vars.length();
		char* str = new char[len+1];
		vars.copy(str, len);
		str[len] ='\0';

		char* buf = strtok(str, ",");
		this->cHeading.add((float) atof(buf));
		buf =strtok(NULL, ",");
		this->cVar.add((float) atof(buf));
		buf =strtok(NULL, ",");
		this->cDev.add((float) atof(buf));

		this->cTime.add(time(NULL));

		delete[] str;
	}

	*heading = this->cHeading.peek();
	*variation = this->cVar.peek();
	*deviation = this->cDev.peek();

	return 1.0f;
}
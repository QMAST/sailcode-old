#include "gaelforce.h"

Gaelforce::Gaelforce(ArduinoCom* lineIn) {
	this->lineIn = lineIn;
	this->updateGPS();
	this->updateCompass();
	this->updateOG();
}

int Gaelforce::updateGPS() {
	std::string vars = "";
	int stat = this->lineIn->requestVariables("airmar", "lat lon", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
		return -1;
	}

	char* buf = strtok(vars.c_str(), ",");
	this->lat = atof(buf);
	buf =strtok(NULL, ",");
	this->lat = atof(buf);
}

int Gaelforce::updateCompass() {
	std::string vars = "";
	int stat = this->lineIn->requestVariables("airmar", "heading dev var", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
		return -1;
	}
	char* buf = strtok(vars.c_str(), ",");
	this->heading = atof(buf);
	buf = strtok(NULL, ",");
	this->dev = atof(buf);
	buf = strtok(NULL, ",");
	this->var = atof(buf);
}

int Gaelforce::updateOG() {
	std::string vars = "";
	int stat = this->lineIn->requestVariables("airmar", "courseOG speedOG", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
		return -1;
	}
	char* buf = strtok(vars.c_str(), ",");
	this->courseOG = atof(buf);
	buf = strtok(NULL, ",");
	this->speedOG = atof(buf);
}


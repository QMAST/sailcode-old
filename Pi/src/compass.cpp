#include "compass.h"

Compass::Compass(ArduinoCom* lineIn) {
	this->ard = lineIn;

	heading = new Buffer<float>(BUFFER_SIZE);
	pitch = new Buffer<float>(BUFFER_SIZE);
	roll = new Buffer<float>(BUFFER_SIZE);
	dip = new Buffer<float>(BUFFER_SIZE);
	this->ctime = new Buffer<time_t>(BUFFER_SIZE);
}

float Compass::getValues(float* heading, float* pitch, float* roll, float* dip) {
	std::string vars = "";
	int stat = this->ard->requestVariables("compass", "compassHeading pitch roll dip", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
	}
	else {
		int len = vars.length();
		char* str = new char[len+1];
		vars.copy(str, len);
		str[len] ='\0';

		char* buf = strtok(str, ",");
		this->heading->add((float) atof(buf));
		buf = strtok(NULL, ",");
		this->pitch->add((float) atof(buf));
		buf = strtok(NULL, ",");
		this->roll->add((float) atof(buf));
		buf = strtok(NULL, ",");
		this->dip->add((float) atof(buf));

		this->ctime->add(time(NULL));

		delete[] str;
	}

	*heading = this->heading->peek();
	*pitch = this->pitch->peek();
	*roll = this->roll->peek();
	*dip = this->dip->peek();

	return 1.0f;
}
#include "compass.h"

Compass::Compass(Arduinocom* lineIn) {
	this->ard = lineIn;

	// heading = Buffer<float>(BUFFER_SIZE);
	// pitch = Buffer<float>(BUFFER_SIZE);
	// roll = Buffer<float>(BUFFER_SIZE);
	// dip = Buffer<float>(BUFFER_SIZE);
	// this->time = Buffer<time_t>;
}

float Compass::getValues(float* heading, float* pitch, float* roll, float* dip) {
	std::string vars = "";
	int stat = this->lineIn->requestVariables("compass", "heading pitch roll dip", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
	}
	else {
		int len = vars.length();
		char* str = new char[len+1];
		vars.copy(str, len);
		str[len] ='\0';

		char* buf = strtok(str, ",");
		this->heading.add((float) atof(buf));
		buf = strtok(NULL, ",");
		this->pitch.add((float) atof(buf));
		buf = strtok(NULL, ",");
		this->roll.add((float) atof(buf));
		buf = strtok(NULL, ",");
		this->dip.add((float) atof(buf));

		this->time.add(time(NULL));

		delete[] str;
	}

	*heading = this->heading.peek();
	*pitch = this->pitch.peek();
	*roll = this->roll.peek();
	*dip = this->roll.dip();

	return 1.0f;
}
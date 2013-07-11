#include "angleSensor.h"

AngleSensor::AngleSensor(ArduinoCom* lineIn) {
	this->ard = lineIn;
	motor1 =  new Buffer<int>(BUFFER_SIZE);
	motor2 =  new Buffer<int>(BUFFER_SIZE);
	mast = new  Buffer<int>(BUFFER_SIZE);
	this->time =  new Buffer<time_t>(BUFFER_SIZE);
}

float AngleSensor::getAngles(int* motor1, int* motor2, int* mast) {
	std::string vars = "";
	int stat = this->ard->requestVariables("motor1Angle", "angle", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
	}
	else {
		int len = vars.length();
		char* str = new char[len+1];
		vars.copy(str, len);
		str[len] ='\0';

		char* buf = strtok(str, ",");
		this->motor1->add(atoi(buf));

		delete[] str;
	}

	vars = "";
	stat = this->ard->requestVariables("motor2Angle", "angle", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
	}
	else {
		int len = vars.length();
		char* str = new char[len+1];
		vars.copy(str, len);
		str[len] ='\0';

		char* buf = strtok(str, ",");
		this->motor2->add(atoi(buf));

		delete[] str;
	}

	vars = "";
	stat = this->ard->requestVariables("mastAngle", "angle", vars);
	if(stat!=0) {
		Logging::error(__func__, "Error while getting variables");
	}
	else {
		int len = vars.length();
		char* str = new char[len+1];
		vars.copy(str, len);
		str[len] ='\0';

		char* buf = strtok(str, ",");
		this->mast->add(atoi(buf));

		delete[] str;
	}
	this->time.add(time(NULL));


	*motor1 = this->motor1->peek();
	*motor2 = this->motor2->peek();
	*mast = this->mast->peek();
	return 1.0f;
}
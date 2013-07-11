#include "motor.h"

Motor::Motor(Stream* serialLine, int pin, char controllerID) {
	this->serialCom = serialLine;
	this->anglePin = pin;
	this->controllerID = controllerID;

	//Exit safe-start mode.
	this->serialCom->write(0xAA);
	this->serialCom->write(this->controllerID);
	this->serialCom->write(0x03);
	this->currentSpeed = 0;
}

void Motor::setMotorParams(int min, int max) { 
	this->zeroAngle = min;
	this->maxAngle = max;
}

double Motor::getAngle() {
	int val = analogRead(this->anglePin);
	//Convert the raw number into an angle between 0 and 360.
	//In this case, an angle of 0 corresponds to a reading of -180 by the sensor.
	//This makes it clearer to show the relationship between the amount of rope out and the angle.
	if(val<100) {
		//Value is in LOW
		return -1.0;
	}
	else {
		return ((val-102)/2.275);//Converts from value to angle.
	}
}

void Motor::reset(){
	this->serialCom->write(0xAA);
	this->serialCom->write(this->controllerID);
	this->serialCom->write(0x03);
	this->currentSpeed = 0;
}

int Motor::setLength(int position) {
	/* Adjust the motor to have the specified rope length out.
	For example, setLength(0) would bring the rope in all the way,
	setLength(100) would take it all the way out.
	Need to determine max and min angles, but we should be able to make this work.
	There is a linear relationship between the angle and the position of the knot on the line.
	Also need to include a timeout in case the motor isn't responsive.
	*/
	int speed, sign;
	//First calculate desired angle from position.
	double dif = this->maxAngle - this->zeroAngle;
	double endAngle = this->zeroAngle + (position/100.0 * dif);

	double currAngle = this->getAngle();
	dif=abs(endAngle - currAngle);
	while(dif > this->ANGLE_ERROR) {

		//Need to translate the difference into an appropriate motor speed.
		sign = (endAngle > currAngle) ? 1:-1;
		if(dif > 90) {
			speed = sign*3600; //Full speed
		} else if(dif > 40) {
			speed = sign*1800;//Half speed
		} else if(dif >15) {
			speed = sign*900;//Quarter speed
		} else {
			speed = sign*500;
		}
		this->setMotorSpeed(speed);
		currAngle = this->getAngle();
		dif = abs(endAngle - currAngle);
	}

	this->setMotorSpeed(0);

	//Returns the actual position of the motor
	currAngle = this->getAngle();
	position = int(100*(currAngle-this->zeroAngle)/(this->maxAngle - this->zeroAngle));
	return position;
}

int Motor::setMotorSpeed(int speed) {
	// Adjust the motor speed, to the specified value between -3600 and 3600
	if(speed!=this->currentSpeed) {
		this->serialCom->write(0xAA);
		this->serialCom->write(this->controllerID);

		if (speed < 0)
	  	{
	    	this->serialCom->write(0x86);  // motor reverse command
	    	speed = -speed;  // make speed positive
	  	}
	  	else
	  	{
	    	this->serialCom->write(0x85);  // motor forward command
	  	}
		this->serialCom->write(speed & 0x1F);
		this->serialCom->write(speed >> 5);
		this->currentSpeed=speed;
	}
	return 0;
}


/* Pololu Simple Motor controller class
The motor controller needs simple serial commands sent to it,
which can control the speed and direction of the DC motor.
An angle sensor is used to determine the current position of the winch.
The winch position determines how much rope is let out, and how much slack
the sail has.

*/

#ifndef _MOTOR_H
#define _MOTOR_H

#include <Arduino.h>

class Motor {
public:
	Motor(Stream* serialLine, int pin, char controllerID);

	double getAngle();
	void setMotorParams(int min, int max);
	void reset();
	int setLength(int position);
	int setMotorSpeed(int speed);
private:
	int anglePin;
	char controllerID;

	int currentSpeed;

	static const int WINCH_RADIUS = 5;//5 Cm from middle to where rope lies (approx.)
	static const double ANGLE_ERROR = 3.0;
	//The following are different for each winch. Will have to set manually.
	int zeroAngle; //Angle reported when the knot is pulled completely tight
	int maxAngle; //Angle reported when the knot is all the way out.

	Stream* serialCom;
};

#endif	

#include <Arduino.h>
#include <motor.h>
#include <rc.h>

#define ANGLE_PIN_1 0
#define ANGLE_PIN_2 1
//Two motors
Motor* motor1;
Motor* motor2;
RC* Control;

int num;
void setup() {
	Serial.begin(115200);
	Serial2.begin(38400);
	motor1 = new Motor(&Serial2, ANGLE_PIN_1, '\x0D');
	motor2 = new Motor(&Serial2, ANGLE_PIN_2, '\x0E');

	Control = new RC();

}

void loop() {
	if(Control->gearSwitchUp()) {
		num=Control->getValueRV();
                Serial.print("RV Value: ");
                Serial.print(num);
                num = map(num, -100, 100, -3600, 3600);
		motor1->setMotorSpeed(num);
		Serial.print(", Motor 1: ");
		Serial.print(motor1->getAngle());
		num=Control->getValueLV();
                Serial.print("LV Value: ");
                Serial.print(num);
		num = map(num, -100, 100, -3600,3600);
		motor2->setMotorSpeed(num);
		Serial.print(", Motor 2: ");
		Serial.println(motor2->getAngle());

	}
	else {
		//Sailcode goes here.
		motor1->setMotorSpeed(0);
		motor2->setMotorSpeed(0);
	}
	delay(200);
}

void getMotorParams() {
	/*
		Subroutine to get the motor parameters using RC control.
		Keeps track of the max and minimum positions of the two motors,
		until the auxiliary switch is set back to a normal position.
		Sets the motors with this position.
	*/
	int max1, max2, min1, min2;
	int temp;

	while(Control->getValueAux() > 50) {
		//While the aux knob is over halfway, get the max and min
		temp = motor1->getAngle();
		if(temp > max1) {
			max1 = temp;
		}
		else if(temp < min1) {
			min1 = temp;
		}

		temp = motor2->getAngle();
		if(temp > max2) {
			max2 = temp;
		} else if(temp<min2) {
			min2 = temp;
		}

		//Get RC values for motor movement.
		temp=Control->getValueRV();
        temp = map(temp, -100, 100, -3600, 3600);
		motor1->setMotorSpeed(temp);
		temp=Control->getValueLV();
		temp = map(temp, -100, 100, -3600, 3600);
		motor2->setMotorSpeed(temp);

	}

	motor1->setMotorParams(min1, max1);
	motor2->setMotorParams(min2, max2);
	return;
}
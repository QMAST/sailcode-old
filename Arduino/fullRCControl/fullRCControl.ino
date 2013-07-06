#include <Arduino.h>
#include <motor.h>
#include <rc.h>
#include <pololu_servo.h>

#define ANGLE_PIN_1 0
#define ANGLE_PIN_2 1

#define POLOLU_RESET 20

//Two motors
Motor* motor1;
Motor* motor2;
RC* Control;
PololuMSC* servo;

int num;
void setup() {
	Serial.begin(115200);
	Serial2.begin(38400);
        Serial3.begin(9600);
	motor1 = new Motor(&Serial2, ANGLE_PIN_2, '\x0E');

	Control = new RC();
        servo = new PololuMSC(&Serial3, POLOLU_RESET);
}

void loop() {
	if(Control->gearSwitchUp()) {
		num=Control->getValueRV();
                num = map(num, -100, 100, -3600, 3600);
		motor1->setMotorSpeed(num);

                num=Control->getValueLV();
                num = map(num, -100,100, 0, 254);
                servo->setPosition(0,num);
                servo->setPosition(1,num);
	}
	else {
		motor1->setMotorSpeed(0);
		motor2->setMotorSpeed(0);
	}
	delay(200);
}

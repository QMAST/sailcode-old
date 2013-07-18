/* 
	Test for angle pin on winch motors

*/

#include <Arduino.h>
#include <motor.h>
#include <rc.h>
#include <pololu_servo.h>

#define MOTOR_PIN A0

Motor* motor;
RC* control;
PololuMSC* servo;

void HandleRC();

void setup() {
	Serial.begin(115200);
	
	Serial1.begin(38400);
	motor= new Motor(&Serial1, MOTOR_PIN, '\x0E');

	int temp = motor->getAngle();
	Serial.print("Winch is at: ");
	Serial.println(temp);
	motor->setMotorParams(temp-10, temp+10);
}

void loop() {

	
	HandleRC();
        int temp = motor->getAngle();
        Serial.println(temp);

}

void HandleRC() {
    //Go into normal RC mode.
    int temp;
    temp = control->getValueRV();
    temp = map(temp, -100,100, -3600,3600);
    if(abs(temp)<3600) {
      motor->setMotorSpeed(temp);
    }
    
    temp = control->getValueRH();
    Serial.println(temp);
    /*temp = map(temp, 100,-100, 1,254);
    if(abs(temp)<254) {
      Serial.print("Servo Setting: ");
      Serial.println(temp);
      servo->restart();
      servo->setPosition(0, temp);
      servo->setPosition(1, temp);
    }*/
    if (temp < -500 || temp > 500) {
       servo->setPosition(0,127);
       servo->setPosition(1,127);
       //Serial.println("NEUTRAL");
    }
    else if (temp < -20){
       servo->restart();
       servo->setPosition(0, 1);
       servo->setPosition(1, 1);
       //Serial.println("RIGHT");
    }
    else if (temp > 20) {
       servo->restart();
       servo->setPosition(0,254);
       servo->setPosition(1,254);
       //Serial.println("LEFT");
    }
    else{
       servo->setPosition(0,127);
       servo->setPosition(1,127);
       //Serial.println("NEUTRAL");
    }

}


/* 
	Testing motor issues individually

*/

#include <Arduino.h>
#include <motor.hh>

#define MOTOR_PIN A0

Motor* motor;

void HandleRC();

void setup() {
	Serial.begin(115200);
	
	Serial1.begin(38400);
	motor= new Motor(&Serial1, MOTOR_PIN, '\x0D');

	int temp = motor->getAngle();
	Serial.print("Winch is at: ");
	Serial.println(temp);
	motor->setMotorParams(temp-10, temp+10);
}

void loop() {

	
	HandleRC();

}

void HandleRC() {
  //Handles all the RC control possibilities. 
  if(control->getValueLV() > 0) {//If the left stick is set more than halfway up...
    //Enter motor configuration mode, to set the motor parameters.
    //This will take complete control of the program until the mode is disabled, regardless of gearswitch position
    Serial.println("Calibrating...");
    getMotorParams();
  }
  else {//If the left stick is less than halfway up...
    //Go into normal RC mode.
    //Serial.println("In RC");
    int temp;
    temp = control->getValueRV();
    temp = map(temp, -100,100, -3600,3600);
    if(abs(temp)<3600) {
      motor1->setMotorSpeed(temp);
      motor2->setMotorSpeed(temp);
    }
    temp = control->getValueRH();
    //Serial.println(temp);
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

}
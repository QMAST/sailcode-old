/* Testing pololu servo function for setting rudder */

#include <Arduino.h>

#include <pololu_servo.h>

#define RESET_PIN 40

PololuMSC* rudderServo;

void setup() {
   
  Serial.begin(115200);
  
  rudderServo = new PololuMSC(&Serial3, RESET_PIN);
  
  Serial3.begin(9600);
  pinMode(RESET_PIN, INPUT);
  delay(5);

}

void loop() {
  
  rudderServo->restart();

  rudderServo->setPosition(0, 127);
  rudderServo->setPosition(1, 127);
  
  
  delay(4000);
  
  
  rudderServo->setPosition(0, 254);
  rudderServo->setPosition(1, 254);
  
  delay(4000);
  
   rudderServo->setPosition(0, 127);
  rudderServo->setPosition(1, 127);
  
  
  delay(4000);
  
  
  rudderServo->setPosition(0, 1);
  rudderServo->setPosition(1, 1);
  
  delay(4000);
  
   
  
  
  
}


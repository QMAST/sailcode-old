/* Testing pololu servo function for setting rudder */

#include <Arduino.h>

#include <pololu_servo.h>

#define RESET_PIN 50

PololuMSC* rudderServo;

void setup() {
   
  Serial.begin(115200);
  
  rudderServo = new PololuMSC(&Serial2, RESET_PIN);
  
  Serial2.begin(2400);
  pinMode(RESET_PIN, INPUT);
  delay(5);

}

void loop() {
  
  //rudderServo->restart();

  rudderServo->setPosition(0, 127);
  rudderServo->setPosition(1, 127);
  
  
  delay(2000);
  
  
  //rudderServo->setPosition(0, 200);
  //rudderServo->setPosition(1, 200);
  
  delay(2000);
  
   
  
  
  
}


/* Testing pololu servo function for setting rudder */

#include <Arduino.h>

#include <pololu_servo.h>

#define RESET_PIN 50

PololuMSC* rudderServo;

void setup() {
   
  Serial.begin(115200);
  
  rudderServo = new PololuMSC(&Serial2, RESET_PIN);
  
  Serial2.begin(9600);
  pinMode(RESET_PIN, INPUT);
  delay(5);
  Serial2.write(0xAA);
  Serial2.write(0x83);
}

void loop() {
  

  rudderServo->setPosition(0, 45);
  rudderServo->setPosition(1, 45);
  
  delay(1000);
  
   
  
  
  
}


/* Testing pololu servo function for setting rudder */

#include <Arduino.h>

#include <pololu_servo.h>

#define RESET_PIN 50

ServoMSC* rudderServo;

void setup() {
   
  Serial.begin(115200);
  
  rudderServo = new ServoMSC(&Serial2, RESET_PIN);
  
  Serial2.begin(38400);
  pinMode(RESET_PIN, INPUT);
  delay(5);
  Serial2.write(0xAA);
  Serial2.write(0x83);
}

void loop() {
  
  delay(500);
  rudderServo->setPosition(0, 100);
  rudderServo->setPosition(1, 100);
  
  delay(1000);
  
  
  
  
}


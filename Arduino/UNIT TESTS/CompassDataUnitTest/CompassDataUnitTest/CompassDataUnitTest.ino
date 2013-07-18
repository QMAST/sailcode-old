/* Testing compass data */

#include <Arduino.h>
#include <compass.h>
#include <sensor.h>

#define MULTIPLEX_PIN1 30
#define MULTIPLEX_PIN2 31

Compass* compass;

void setup(){
  
 Serial.begin(115200);
  
 Serial2.begin(9600);
 
 pinMode(MULTIPLEX_PIN1, OUTPUT);
 pinMode(MULTIPLEX_PIN2, OUTPUT);
 pinMode(50, OUTPUT);
 digitalWrite(50, HIGH);
 
 compass = new Compass("compass", &Serial2);
  
}

void loop(){
 
 //digitalWrite(50, HIGH);
 //digitalWrite(MULTIPLEX_PIN1, LOW);
 //digitalWrite(MULTIPLEX_PIN2, LOW);
 
  int temp = compass->update();
  Serial.print("Update: ");
  Serial.println(temp);
  
  Serial.print("Heading: ");
  Serial.println(compass->compassHeading);
  Serial.print("Status: ");
  Serial.println(compass->compassStatus);
  
  
}

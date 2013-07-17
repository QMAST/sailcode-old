/* Testing compass data */

#include <Arduino.h>
#include <compass.h>
#include <sensor.h>

Compass* compass;

void setup(){
  
  Serial.begin(115200);
  
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);
  
 Serial2.begin(9600);
 compass = new Compass( "compass", &Serial2);
  
}

void loop(){
  compass->update();
  
  Serial.println(compass->compassHeading);
  
  
}

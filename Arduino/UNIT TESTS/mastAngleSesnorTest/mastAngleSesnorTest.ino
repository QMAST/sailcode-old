/* testing angle sensor at base of mast */

#include <Arduino.h>

#define ANGLE_PIN A2

void setup() {
  Serial.begin(115200);
  

  
}


void loop() {
  
    int val = analogRead(ANGLE_PIN);
  val = int((double(val)*0.4399) - 225);
  
  Serial.println(val);
  
  delay(300);
  
}

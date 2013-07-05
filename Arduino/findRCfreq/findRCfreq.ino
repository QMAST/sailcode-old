#include <Arduino.h>

int getPWM_Value(int pinIn);
int pwd;
void setup(){
    Serial.begin(115200);
    pinMode(2, INPUT);
}

void loop(){
    pwd = pulseIn(2, HIGH, 20000);
    Serial.println(pwd);
    delay(500);
}

int getPWM_Value(int pinIn)
{

  int RCVal = pulseIn(pinIn, HIGH, 20000);
  if(RCVal == 0)
  {
    RCVal = -1;
  }

  RCVal = map(RCVal, 1000, 2000, -3200, 3200);
  return RCVal;

}


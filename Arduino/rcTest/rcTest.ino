#include <Arduino.h>

#define RCPIN 8
int spd;
void setup() {
    Serial.begin(115200);
    Serial2.begin(38400);
    pinMode(RCPIN, INPUT);

    //Set up pololu
    delay(5);
    Serial2.write(0xAA);
    Serial2.write(0x83);

}

void loop() {
    spd = getPWM_Value(RCPIN);
    Serial.println(spd);
    setMotorSpeed(spd);
    delay(200);
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

void setMotorSpeed(int speed)
{
  if (speed < 0)
  {
    Serial2.write(0x86);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    Serial2.write(0x85);  // motor forward command
  }
  Serial2.write(speed & 0x1F);
  Serial2.write(speed >> 5);
}

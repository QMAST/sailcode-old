#include <Arduino.h>
#include <pololu_controller.h>
#include <pololu_servo.h>

void setMotorSpeed(polcore* motor, int speed);
void setServoAngle(PololuMSC* pololu, uint8_t pololuId, uint8_t angle);

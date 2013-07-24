#include <Servo.h>
#include <rc.h>

#define POLOLU_RESET 20

Servo servo;
RC* control;

void setup() {
    control = new RC();
    Serial.begin(115200);
    Serial1.begin(9600);
    servo.attach(9);
}

void loop() {
    //Check PWM input
    //Map to range 0-254,
    //Set motor position.
    int val = control->getValueRV();
    //Serial.println(val);
    val = map(val, -100, 100, 0, 180);
    //Serial.println(val);
     servo.write(val);
     delay(100);   
}

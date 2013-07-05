To use the Pololu Micro Servo Controller library.

    ```c
    #include <pololu_servo.h>

    static const int pololu_reset_pin = 3;
    static const int MOTOR_ONE = 7;
    
    PololuMSC* pololu;

    void setup() {
        Serial1.begin(9600);
        pinMode(pololu_reset_pin, OUTPUT);
        pololu = new PololuMSC(&Serial1, pololu_reset_pin);
        pololu->restart();
    }

    void loop() {
        pololu->setPosition(MOTOR_ONE, 250);
        delay(500);
        pololu->setPosition(MOTOR_ONE, 0);
        delay(500);
    }
    ```

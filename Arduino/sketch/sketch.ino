/*
  This is the main sketch which contains our most up-to-date sailcode and
  accurate steps
*/

#include <Arduino.h>
#include <ashcon.h>
#include <airmar.h>
#include <compass.h>
#include <sensor.h>
#include <rc.h>
#include <pololu_servo.h>
#include <motor.h>

#define MULTIPLEX_PIN1 30
#define MULTIPLEX_PIN2 31
#define ENABLE_PIN 50
#define SERVO_RESET_PIN 40
#define MOTOR_1_ANGLEPIN A0
#define MOTOR_2_ANGLEPIN A1

typedef struct SensorLink {
	struct SensorLink* next;
	Sensor* s;
} SensorLink;

int mode = 0;
int spd;
int dir = 90;

//All the objects necessary on the boat
Airmar* airmar;
Compass* compass;
ashcon* Console;
SensorLink* sensorList;
RC* control;
PololuMSC* servo;
Motor* motor1;
Motor* motor2;


//Function prototypes
void addToList(Sensor* item);
int dispatchRequest(int argc, char* argv[]);
Sensor* getHottestSensor();
void piInterrupt();
int updateDirection(int argc, char* argv[]);
void SailAutonomous();
void HandleRC();
void clearBuffer();


void setup() {
	//Initialize console
    Serial.begin(115200);
    Console = new ashcon(&Serial);
    Console->user_function_register("req", &dispatchRequest);
    Console->user_function_register("dir", &updateDirection);
    
    //Initialize multiplexor
    pinMode(MULTIPLEX_PIN1, OUTPUT);
    pinMode(MULTIPLEX_PIN2, OUTPUT);
	pinMode(ENABLE_PIN, OUTPUT);
	digitalWrite(ENABLE_PIN, HIGH);
    
	
    //Initialize Servos
    Serial3.begin(9600);
    servo = new PololuMSC(&Serial3, SERVO_RESET_PIN);

    //Initialize RC
    control = new RC();

    //Initialize motors
    Serial1.begin(38400);
    motor1 = new Motor(&Serial1, MOTOR_1_ANGLEPIN, '\x0D', -180, 180);
    motor2 = new Motor(&Serial1, MOTOR_2_ANGLEPIN, '\x0E', -180, 180);

    //Initialize sensors
    Serial2.begin(9600);
    airmar = new Airmar("airmar",&Serial2);
    compass = new Compass("compass",&Serial2);
    addToList(airmar);
    addToList(compass);

    //Setup interrupts
    attachInterrupt(0, piInterrupt, FALLING);
}

void loop() {
    switch(mode) {
        case 0: //Default mode, polling sensors, handling RC.
        {
            if(control->gearSwitchUp()) //We're in RC mode.
            {
                //Serial.println("Entering RC");
                HandleRC();
                //Serial.println("RC");
            } 
            else { //We're in autonomous mode
                int pos = control->getValueAux();
                if(pos<25) {
                  dir=0;
                } else if(pos<50) {
                  dir=90;
                } else if(pos<75) {
                  dir=180;
                } else {
                  dir=270;
                }
            
              
		SailAutonomous();
            }

            //Update Sensors, regardless of mode.

            Sensor* sens = getHottestSensor();
            //Need to include multiplexor and code for changing Baud rate when necessary.
            
            clearBuffer();
            if(strcmp(sens->id, "compass")){
              Serial2.begin(9600);
            }
            else 
            {
              Serial2.begin(4800);
            }
            sens->update();
        }
        break;
        case 1: //Responding to request for variables.
        {
            Console->command_prompt();
            mode=0;
        }
        break;
    }
}

void addToList(Sensor* item) {
    if(item == NULL){
        return;
    }
    SensorLink* link = (SensorLink*) malloc(sizeof(SensorLink));
    link->next = sensorList;
    link->s = item;
    sensorList = link;
}

int dispatchRequest(int argc, char* argv[]) {
        //digitalWrite(13, HIGH);
	//Need to search through a list of sensors, 
	//and find one that matches argv[1] - 
	//this should be the sensor name. 
	//All following args are variables that are requested.
	SensorLink* link = sensorList;
        //Serial.print("Loooking for sensor ");
        //Serial.println(argv[1]);
	while(link!=NULL) {
		if(strcmp(link->s->id, argv[1])==0){
                        //Serial.println("Found Sensor!");
			break;
		}
		link = link->next;
	}
        
        if(link==NULL){
             //Didn't find a match
              return -1;   
        }

        
	char** variables = link->s->getVariables(argc-2, &(argv[2]));
	for(int i=0; i<(argc-2); i++) {//Print out all the variables.
		if(variables[i]!=NULL) {
			Serial.print(variables[i]);
                        
		} else {
			Serial.print("*");
		}
		Serial.print(",");
		Serial.flush();
                
	}
	Serial.print("\n\r");

        //Serial.println("Exiting request");
        for(int i=0; i<(argc-2); i++){
             free(variables[i]);   
        }
        free(variables);
        //digitalWrite(13, LOW);
	return 0;
}

int updateDirection(int argc, char* argv[]) {
	//argv[1] is the new sail direction

	dir = atoi(argv[1]);
  Serial.println("OK");
	return 0;


}

void clearBuffer(){
	//Switch to an unconnected pin
	digitalWrite(MULTIPLEX_PIN1, LOW);
	digitalWrite(MULTIPLEX_PIN2, HIGH);

	while(Serial1.available()>0){
		Serial1.read();
	}
}

Sensor* getHottestSensor() {
	if(sensorList==NULL || sensorList->s==NULL) {
		return NULL;
	}
    SensorLink* link = sensorList;
    Sensor* hottest;
    int maxTemp=0;
    unsigned long t = millis();
    unsigned long temp;
    while(link!=NULL) {
    	temp = link->s->getTemp(t);
    	if(temp > maxTemp) {
    		hottest = link->s;
    		maxTemp = temp;
    	}
    	link = link->next;
    }
    return hottest;
}

void piInterrupt() {
	mode =1;
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

void SailAutonomous(){
        Serial.println("Sailing Autonomously");
	int diff = abs(airmar->heading - dir);
	//Set rudder 
	if (diff < 10){
		servo->setPosition(0, 127);
		servo->setPosition(1, 127);
	}
	else if(airmar->heading > dir){
		if ( (airmar->heading - dir) < 180 ){
			servo->setPosition(0, 254);
			servo->setPosition(1, 254);
        }
		else {
			servo->setPosition(0, 1);
			servo->setPosition(1, 1);
        }
	}
	else {
		if( (dir - airmar->heading) < 180){
			servo->setPosition(0, 1);
			servo->setPosition(1, 1);
        }
		else{
			servo->setPosition(0, 254);
			servo->setPosition(1, 254);
		}
	}
	
	//Set sails
	int windDirWRTHeading = airmar->windDirection - compass->compassHeading;
	if (windDirWRTHeading < 0)
		windDirWRTHeading+=360;
	
	if(windDirWRTHeading >=180 && windDirWRTHeading < 360) {
		windDirWRTHeading = 360-windDirWRTHeading;
	}

	motor1->setLength((windDirWRTHeading/180)*100);
	motor2->setLength((windDirWRTHeading/180)*100);

}


void HandleRC() {
  //Handles all the RC control possibilities. 
  if(control->getValueLV() > 0) {//If the left stick is set more than halfway up...
    //Enter motor configuration mode, to set the motor parameters.
    //This will take complete control of the program until the mode is disabled, regardless of gearswitch position
    Serial.println("Calibrating...");
    getMotorParams();
  }
  else {//If the left stick is less than halfway up...
    //Go into normal RC mode.
    Serial.println("In RC");
    int temp;
    temp = control->getValueRV();
    temp = map(temp, -100,100, -3600,3600);
    if(abs(temp)<3600) {
      motor1->setMotorSpeed(temp);
      motor2->setMotorSpeed(temp);
    }
    temp = control->getValueRH();
    Serial.println(temp);
    /*temp = map(temp, 100,-100, 1,254);
    if(abs(temp)<254) {
      Serial.print("Servo Setting: ");
      Serial.println(temp);
      servo->restart();
      servo->setPosition(0, temp);
      servo->setPosition(1, temp);
    }*/
    if (temp < -500 || temp > 500) {
       servo->setPosition(0,127);
       servo->setPosition(1,127);
       //Serial.println("NEUTRAL");
    }
    else if (temp < -20){
       servo->restart();
       servo->setPosition(0, 1);
       servo->setPosition(1, 1);
       //Serial.println("RIGHT");
    }
    else if (temp > 20) {
       servo->restart();
       servo->setPosition(0,254);
       servo->setPosition(1,254);
       //Serial.println("LEFT");
    }
    else{
       servo->setPosition(0,127);
       servo->setPosition(1,127);
       //Serial.println("NEUTRAL");
    }
  }

}

void getMotorParams() {
  /*
    Subroutine to get the motor parameters using RC control.
    Keeps track of the max and minimum positions of the two motors,
    until the auxiliary switch is set back to a normal position.
    Sets the motors with this position.
  */
  int max1, max2, min1, min2;
  max1=-180;
  max2=-180;
  min1=180;
  min2=180;
  int temp;

  while(control->getValueLV() > 0) {
    //While the aux knob is over halfway, get the max and min
   
    temp = motor1->getAngle();
    if(temp>-180 && temp <180) {
        if(temp > max1) {
          max1 = temp;
        }
        else if(temp < min1) {
          min1 = temp;
        }
    }
    temp = motor2->getAngle();
    if(temp>-180 && temp <180){
        if(temp > max2) {
          max2 = temp;
        } else if(temp<min2) {
          min2 = temp;
        }
    }
    //Get RC values for motor movement.
    temp = control->getValueRV();
    temp = map(temp, -100,100, -3600,3600);
    if(abs(temp)<3600) {
      motor1->setMotorSpeed(temp);
      motor2->setMotorSpeed(temp);
    }
  }

  motor1->setMotorParams(min1, max1);
  motor2->setMotorParams(min2, max2);
  Serial.print("Max winch 1: ");
  Serial.print(max1);
  Serial.print("Min winch 1: ");
  Serial.print(min1);
  
  Serial.print("   Max winch 2: ");
  Serial.print(max2);
  Serial.print("Min winch 2: ");
  Serial.print(min2); 
  
  return;
}

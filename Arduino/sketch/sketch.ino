#include <Arduino.h>
#include <ashcon.h>
#include <airmar.h>
#include <compass.h>
#include <sensor.h>

#define RCPIN 8
#define KILLPIN 10

#define MULTIPLEX_PIN1 30
#define MULTIPLEX_PIN2 31


typedef struct SensorLink {
	struct SensorLink* next;
	Sensor* s;
} SensorLink;

int mode = 0;
int spd;
int dir = 90;
Airmar* airmar;
Compass* compass;
ashcon* Console;
SensorLink* sensorList;

void addToList(Sensor* item);
int dispatchRequest(int argc, char* argv[]);
Sensor* getHottestSensor();
void piInterrupt();
boolean isKillswitchEngaged();
int updateDirection(int argc, char* argv[]);
void SailAutonomous();

void setup() {
	//Initialize console
    Serial.begin(115200);
    Console = new ashcon(&Serial);
    Console->user_function_register("req", &dispatchRequest);
    Console->user_function_register("dir", &updateDirection);
    
    //Initialize multiplexor
    pinMode(MULTIPLEX_PIN1, OUTPUT);
    pinMode(MULTIPLEX_PIN2, OUTPUT);
    
    //Initialize Pololu
    Serial2.begin(38400);
    pinMode(RCPIN, INPUT);
    delay(5);
    Serial2.write(0xAA);
    Serial2.write(0x83);

    //Initialize sensors
    airmar = new Airmar("airmar",&Serial1);
    compass = new Compass("compass",&Serial1);
    addToList(airmar);
    addToList(compass);

    //Setup interrupts
    attachInterrupt(0, piInterrupt, FALLING);
}

void loop() {
    switch(mode) {
        case 0: //Default mode, polling sensors, handling RC.
        {
            if(isKillswitchEngaged() ==false)
            {
                spd = getPWM_Value(RCPIN);
                if(spd > -3200 && spd <3200){
                    setMotorSpeed(spd);
                }
                else
                {
                    setMotorSpeed(0);
                }
            } else {
                // setMotorSpeed(0);
				SailAutonomous();
            }
            Sensor* sens = getHottestSensor();
            //Serial.print("Hottest sensor is ");
            //Serial.println(sens->id);
            sens->update();
            //Serial.write(0); //Just to see if the light blinks.
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
	//Need to search through a list of sensors, 
	//and find one that matches argv[1] - 
	//this should be the sensor name. 
	//All following args are variables that are requested.
	SensorLink* link = sensorList;
	while(link!=NULL) {
		if(strcmp(link->s->id, argv[1])==0){
			break;
		}
		link = link->next;
	}

	char** variables = link->s->getVariables(argc-2, &(argv[2]));
	for(int i=0; i<argc-2; i++) {//Print out all the variables.
		if(variables[i]!=NULL) {
			Serial.print(variables[i]);
		} else {
			Serial.print(" ");
		}
		Serial.print(",");
		Serial.flush();
	}
	Serial.print("\n\r");
	return 0;
}

int updateDirection(int argc, char*argv[]) {
	//argv[1] is the new sail direction

	dir = atoi(argv[1]);
	return 0;


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

int getPWM_Value(int pinIn)
{
    
  int RCVal = pulseIn(pinIn, HIGH, 20000);
  if(RCVal == 0)
  {
    RCVal = -10000;
  }

  RCVal = map(RCVal, 1000, 2000, -3200, 3200);
  //Serial.print(pinIn);
  //Serial.print("-");
  //Serial.println(RCVal);
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

boolean isKillswitchEngaged()
{
     int num = getPWM_Value(KILLPIN);
     if(num>0) return false;
      return true;   
    
}

void SailAutonomous(){

	
	//Set rudder 
	if (airmar->heading == dir){
		//set rudder to neutral
	}
	else if(airmar->heading > dir){
		if ( (airmar->heading - dir) < 180 ){
			//turn left
                }
		else {
			//turn right
                }
	}
	else {
		if( (dir - airmar->heading) < 180){
			//turn right
                }
		else{
  
                }
			//turn left
	}
	
	//Set sails
	//Funky trig to get optimum sail position for current heading and wind direction
	airmar->windDirection;
	
	

}

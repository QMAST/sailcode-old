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

#define MULTIPLEX_PIN1 28
#define MULTIPLEX_PIN2 29
#define SERVO_RESET_PIN 40

typedef struct SensorLink {
	struct SensorLink* next;
	Sensor* s;
} SensorLink;

volatile int mode = 0;

//All the objects necessary on the boat
Airmar* airmar;
Compass* compass;
ashcon* Console;

SensorLink* sensorList;


//Function prototypes
void addToList(Sensor* item);
int dispatchRequest(int argc, char* argv[]);
Sensor* getHottestSensor();
void piInterrupt();

void setup() {
	//Initialize console
    pinMode(13, OUTPUT);

    Serial.begin(115200);
    Console = new ashcon(&Serial);
    Console->user_function_register("req", &dispatchRequest);
    
    sensorList = NULL;
    
    //Initialize multiplexor
    pinMode(MULTIPLEX_PIN1, OUTPUT);
    pinMode(MULTIPLEX_PIN2, OUTPUT);

    //Initialize sensors
    Serial2.begin(9600);
    //airmar = new Airmar("airmar",&Serial2);
    compass = new Compass("compass",&Serial2);
    //addToList(airmar);
    addToList(compass);

    //Setup interrupts
    attachInterrupt(0, piInterrupt, RISING);
}

void loop() {
    switch(mode) {
        case 0: //Default mode, polling sensors, handling RC.
        {
            //Update Sensors, regardless of mode.
            digitalWrite(13, HIGH);
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
            digitalWrite(13,LOW);
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
        digitalWrite(13, HIGH);
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

        digitalWrite(13, LOW);
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

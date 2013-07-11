#include <Arduino.h>
#include <airmar.h>
#include <compass.h>
#include <sensor.h>

#define MULTIPLEX_PIN1 28
#define MULTIPLEX_PIN2 29

int mode=0;//Interrupt mode switch

typedef struct SensorLink {
	struct SensorLink* next;
	Sensor* s;
} SensorLink;

//Method prototypes
Sensor* getHottestSensor();
void clearBuffer();
void addToList(Sensor* item);
//Global Variables
Airmar* airmar;
Compass* compass;
SensorLink* sensorList;


char* comp[]={"compassHeading", "compassStatus"};
char* wind[]={"windSpeed", "windDirection"};
char** vars;

void setup() {
	Serial.begin(115200);//Initialize serial over usb
	Serial2.begin(4800);//Initialize serial for sensors

	//Initialize Multiplexor
	pinMode(MULTIPLEX_PIN1, OUTPUT);
	pinMode(MULTIPLEX_PIN2, OUTPUT);

	//Initialize Sensors
	sensorList=NULL;
	airmar = new Airmar("airmar", &Serial2);
	compass = new Compass("compass", &Serial2);
	addToList(airmar);
	addToList(compass);

}

void loop() {
	//Update sensors
	Sensor* sens = getHottestSensor();
	//Clear buffer, switch multiplexor off
	clearBuffer();
        if(strcmp(sens->id, "compass")) {
             Serial2.begin(9600);
             Serial2.println("$PTNT,HTM*63");   
        } else {
             Serial2.begin(4800);   
        }

	sens->update();
        
	Serial.print(sens->id);
	Serial.print(" updated: ");
	if(strcmp(sens->id, "compass")) {
		vars = sens->getVariables(2, comp);
		Serial.print("Heading - ");
		Serial.print(vars[0]);
		Serial.print(", Status - ");
		Serial.println(vars[1]);
		
	} else if(strcmp(sens->id, "airmar")) {
		vars = sens->getVariables(2, wind);
		Serial.print("Speed - ");
		Serial.print(vars[0]);
		Serial.print(", Heading - ");
		Serial.println(vars[1]);
	}
	for(int i=0; i<2; i++) {
        free(vars[i]);
    }
    free(vars);
	
}

void clearBuffer(){
	//Switch to an unconnected pin
	digitalWrite(MULTIPLEX_PIN1, LOW);
	digitalWrite(MULTIPLEX_PIN2, HIGH);

	while(Serial1.available()>0){
		Serial.read();
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

void addToList(Sensor* item) {
    if(item == NULL){
        return;
    }
    SensorLink* link = (SensorLink*) malloc(sizeof(SensorLink));
    link->next = sensorList;
    link->s = item;
    sensorList = link;
}

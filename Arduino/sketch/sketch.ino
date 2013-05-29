#include "sketch.h"

void setup() {
	//Initialize console
    Console = new ashcon(&Serial);
    Console->user_function_register("req", &dispatchRequest);
    
    //Initialize sensors
    airmar = new Airmar("airmar",&Serial1);
    addToList(airmar);

    //Setup interrupts
    attachInterrupt(0, piInterrupt, RISING);
}

void loop() {
    switch(mode) {
        case 0: //Default mode, polling sensors.
            Sensor* sens = getHottestSensor();
            sens->update();
        break;
        case 1: //Responding to request for variables.
            Console->command_prompt();
            mode=0;
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
		if(strcmp(link->sens->id, argv[1])==0){
			break;
		}
		link = link->next;
	}

	char** variables = link->sens->getVariables(argc-2, &(argv[2]));
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

Sensor* getHottestSensor() {
	if(sensorLink==NULL || sensorLink->s==NULL) {
		return NULL;
	}
    SensorLink* link = sensorLink;
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
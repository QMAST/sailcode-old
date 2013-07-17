#include "compass.h"
#define DEBUG 0

Compass::Compass(const char* id, Stream* lineIn) {
	int idLen = strlen(id);
	this->id = (char*) malloc(sizeof(char)*(idLen+1));
	strcpy(this->id, id);
	
	this->tempRate =1;

	this->lineIn = lineIn;
	this->varList = NULL;
	addVar(DOUBLE, "compassHeading", &compassHeading);
	addVar(CHAR, "compassStatus", &compassStatus);
	addVar(DOUBLE, "pitch", &pitchAngle);
	addVar(DOUBLE, "roll", &rollAngle);
	addVar(DOUBLE, "dip", &dipAngle);

	this->compassHeading = 0;
	this->compassStatus = 0;
	this->pitchAngle = 0;
	this->rollAngle = 0;
	this->dipAngle = 0;

	this->update();
}

int Compass::update() {
	//Get the data from the sensor, parse it properly, do anything else necessary.
	this->lineIn->println("$PTNT,HTM*63");
	
	//digitalWrite(MULTIPLEX_PIN1, LOW);
	//digitalWrite(MULTIPLEX_PIN2, LOW);
	//delay(20);
		
		
	//Read line, place into a buffer.
	char* buf = (char*) malloc(256*sizeof(char));
	char charIn ='\0';
	int i=0;

	//Need a timeout here, to prevent a hang.
	unsigned long st = millis();
	//Wait to get a $ to start the line
	while(true){
		if(this->lineIn->peek() == '$'){
			break;
		}
		if(this->lineIn->available() >0){
			this->lineIn->read();
		}
		if(abs(millis()-st) > 500) {
			if(DEBUG) {
			 	Serial.println("Timeout waiting for $");
			}
			free(buf);
			return -1;//Timeout

		}
	}

	st = millis();
	while(i<255) {
		if(this->lineIn->available() >0) {
			charIn = this->lineIn->read();//Read a single character;

			if(charIn == '\r' || charIn == '\n') {//Newline read
				break;
			}

			buf[i] = charIn;
			i++;//Should never reach a 255 character line, especially from the airmar.
		}
		if(abs(millis()-st) > 500) {

			if(DEBUG) {
			 	Serial.println("Timeout waiting for full line");
			}
			free(buf);
			return -1;//Timeout
		}
	}

	buf[i] = '\0';
	if(DEBUG) {
		Serial.print("Line Read: ");
		Serial.println(buf);
		Serial.println("End of the line");
	}
	//call NMEA::parseString();
	NMEAData* nmea = (NMEAData*) malloc(sizeof(NMEAData)); 
	i = NMEA::parseString(buf, nmea);
	if(i!=0) {
		if(DEBUG) {
			Serial.println("Error Parsing: ");
		}

		free(nmea);
		free(buf);
		return -1;
	}
	//Depending on the header, copy the data appropriately
	switch(nmea->header) {
		case PTNTHTM:
			this->compassHeading = atof(nmea->data[0]);
			this->compassStatus = atof(nmea->data[1]);
			this->pitchAngle = atof(nmea->data[2]);
			this->rollAngle = atof(nmea->data[4]);
			this->dipAngle = atof(nmea->data[6]);
		break;
		default:
			if(DEBUG) {
				Serial.print("Invalid NMEA Header:");
				Serial.print(nmea->header);
			}
			for(i=0; i<nmea->count; i++){
				free(nmea->data[i]);
			}
			free(nmea);
			free(buf);
			return -1;
	}

	//Free all of the nmea stuff.
	for(i=0; i<nmea->count; i++){
		free(nmea->data[i]);
	}
	free(nmea);
	free(buf);
	this->temp = 0;//Reset the temperature.
	return 0;
}

int Compass::getTemp(unsigned long time) {
	unsigned long timeDif = time-this->prevTime;
	this->temp += (int)(timeDif*this->tempRate);
	return this->temp;
}

#include "airmar.h"
#define DEBUG 0

Airmar::Airmar(const char* id, Stream* lineIn) {
	int idLen = strlen(id);
	this->id = (char*) malloc(sizeof(char)*idLen);
	strcpy(this->id, id);
	
	this->lineIn = lineIn;
	this->varList = NULL;
	addVar(DOUBLE, "lat", &lat);
	addVar(DOUBLE, "lon", &lon);
	addVar(DOUBLE, "heading", &heading);
	addVar(DOUBLE, "windSpeed", &windSpeed);
	addVar(DOUBLE, "windHeading", &windHeading);
	addVar(DOUBLE, "var", &var);
	addVar(DOUBLE, "dev", &dev);
	addVar(DOUBLE, "courseOG", &courseOverGround);
	addVar(DOUBLE, "speedOG", &speedOverGround);
	//Now we can easily implement new AIRMAR features.

	this->lat = 0;
	this->lon = 0;
	this->heading = 0;
	this->var = 0;
	this->dev = 0;
	this->windSpeed = 0;
	this->windHeading = 0;
	this->courseOverGround = 0;
	this->speedOverGround = 0;
	this->update();
}

int Airmar::update() {
	//Get the data from the sensor, parse it properly, do anything else necessary.
	//Airmar will be read much more frequently, so probably only read one line per call of this.

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
			 	Serial.println("Timeout.");
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
			 	Serial.println("Timeout.");
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
		case HCHDG:
			this->heading = atof(nmea->data[0]);
			this->dev = atof(nmea->data[1]);
			if(strcmp(nmea->data[2],"W")==0) {
				this->dev *=-1;
			}
			this->var = atof(nmea->data[3]);
			if(strcmp(nmea->data[4],"W")==0) {
				this->var *=-1;
			}
		break;
		case WIMWV:
		if(strcmp(nmea->data[4], "A")==0) {
			if(nmea->data[0]!=NULL && nmea->data[0][0]!='\0')
			{
				this->windHeading = atof(nmea->data[0]);
			}
			if(nmea->data[0]!=NULL && nmea->data[2][0]!='\0')
			{
				this->windSpeed = atof(nmea->data[2]);
			}
		}
		break;
		case GPVTG:
		if(strcmp(nmea->data[4], "N")!=0) {
			this->courseOverGround = atof(nmea->data[0]);
			this->speedOverGround = atof(nmea->data[4]);
		}
		break;
		case GPGLL:
		if(strcmp(nmea->data[6],"N")!=0){//If the data is valid
			this->lat = atof(nmea->data[0]);
			if(strcmp(nmea->data[1], "S")==0) {
				this->lat *=-1;
			}
			this->lon = atof(nmea->data[2]);
			if(strcmp(nmea->data[3], "W")==0) {
				this->lon *=-1;
			}
		}
		break;
		case GPRMC:
			this->lat = atof(nmea->data[2]);
			if(strcmp(nmea->data[3], "S")==0) {
				this->lat *=-1;
			}
			this->lon = atof(nmea->data[4]);
			if(strcmp(nmea->data[5], "W")==0) {
				this->lon *=-1;
			}
			
		break;
		case GPGGA:
			this->lat = atof(nmea->data[1]);
			if(strcmp(nmea->data[2], "S")==0) {
				this->lat *=-1;
			}
			this->lon = atof(nmea->data[3]);
			if(strcmp(nmea->data[4], "S")==0) {
				this->lon *=-1;
			}
		break;
		case GPZDA:
			//Just date and time, ignore for now.
		break;
		case WIMDA:
			if(nmea->data[0]!=NULL && nmea->data[12][0]!='\0')
			{
				this->windHeading = atof(nmea->data[12]);
			}
			if(nmea->data[0]!=NULL && nmea->data[16][0]!='\0')
			{
				this->windSpeed = atof(nmea->data[16]);
			}
		break;
		case WIMWD:
			if(nmea->data[0]!=NULL && nmea->data[0][0]!='\0')
			{
				this->windHeading = atof(nmea->data[0]);
			}
			if(nmea->data[0]!=NULL && nmea->data[4][0]!='\0')
			{
				this->windSpeed = atof(nmea->data[4]);
			}
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

int Airmar::getTemp(unsigned long time) {
	unsigned long timeDif = time-this->prevTime;
	this->temp += (int)(timeDif*this->tempRate);
	return this->temp;
}

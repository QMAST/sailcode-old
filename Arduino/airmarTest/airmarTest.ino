
#include <Arduino.h>
#include <airmar.h>


Airmar* am;
char* gps[]={"lat","lon"};
char* wind[]={"windSpeed", "windHeading"};
char* comp[]={"heading","var","dev"};
char* overGround[] = {"courseOG", "speedOG"};
char** vars;
int stat;
void setup() {
        Serial.begin(115200);
	Serial2.begin(4800);
	am = new Airmar("airmar", &Serial2);

}

void loop() {
	Serial.println("Polling AIRMAR...");
	stat = am->update();
	if(stat!=0){ 
		Serial.println("Polling failed.");
	} else {
                Serial.println("Polling Success");
                /*
		vars = am->getVariables(2,gps);
                if(vars!=NULL) {
        		Serial.print("Lat: ");
        		Serial.print(vars[0]);
        		Serial.print(", Lon: ");
        		Serial.print(vars[1]);
                }
		vars = am->getVariables(2,wind);
		if(vars!=NULL) {
                        Serial.print(", wSpeed: ");
        		Serial.print(vars[0]);
        		Serial.print(", wHead: ");
        		Serial.print(vars[1]);
                }        
		vars = am->getVariables(3, comp);
                if(vars!=NULL) {
        		Serial.print(", cHeading: ");
        		Serial.print(vars[0]);
        		Serial.print(", wVar: ");
        		Serial.print(vars[1]);
        		Serial.print(", wDev: ");
        		Serial.print(vars[2]);
                }
		vars = am->getVariables(2, overGround);
		if(vars!=NULL) {
                        Serial.print(", cOG: ");
        		Serial.print(vars[0]);
        		Serial.print(", sOG: ");
        		Serial.println(vars[1]);
                }
                */
                
                /*
                Serial.print("Lat: ");
                Serial.print(am->lat);
        	Serial.print(", Lon: ");
        	Serial.print(am->lon);
                Serial.print(", wSpeed: ");
        	Serial.print(am->windSpeed);
        	Serial.print(", wHead: ");
        	Serial.print(am->windHeading);
                Serial.print(", cHeading: ");
        	Serial.print(am->heading);
        	Serial.print(", cVar: ");
        	Serial.print(am->var);
       		Serial.print(", cDev: ");
       		Serial.println(am->dev);
               */
	}


//delay(1000);
	
	
}

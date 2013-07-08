
#include <Arduino.h>
#include <airmar.h>


Airmar* am;
char* gps[]={"lat","lon"};
char* wind[]={"windSpeed", "windDirection"};
char* comp[]={"heading","var","dev"};
char* overGround[] = {"courseOG", "speedOG"};
char** vars;
int stat;
void setup() {
        Serial.begin(115200);
	Serial1.begin(38400);
	am = new Airmar("airmar", &Serial1);

}

void loop() {
	Serial.println("Polling AIRMAR...");
	stat = am->update();
	if(stat!=0){ 
		Serial.println("Polling failed.");
	} else {
		vars = am->getVariables(2,gps);
		Serial.print("Lat: ");
		Serial.print(vars[0]);
		Serial.print(", Lon: ");
		Serial.print(vars[1]);

		vars = am->getVariables(2,wind);
		Serial.print(", wSpeed: ");
		Serial.print(vars[0]);
		Serial.print(", wHead: ");
		Serial.print(vars[1]);

		vars = am->getVariables(3, comp);
		Serial.print(", cHeading: ");
		Serial.print(vars[0]);
		Serial.print(", wVar: ");
		Serial.print(vars[1]);
		Serial.print(", wDev: ");
		Serial.print(vars[2]);

		vars = am->getVariables(2, overGround);
		Serial.print(", cOG: ");
		Serial.print(vars[0]);
		Serial.print(", sOG: ");
		Serial.println(vars[1]);
	}
	
	
}

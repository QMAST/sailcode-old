#include <MemoryFree.h>

#include <Arduino.h>
#include <compass.h>

Compass* c;
char* comp[]={"compassHeading", "compassStatus"};
char** vars;
int stat;

void setup() {
	Serial.begin(115200);
	Serial2.begin(9600);
	c = new Compass("compass", &Serial2);
	//Serial.println(freeMemory());
//        Serial2.println("@B6=1*78");//Set the baud rate to 4800BPS
//        delay(200);
//        char buf[10];
//        Serial2.readBytes(buf, 10);
//        Serial.println(buf);
//        delay(1000);
//        //Serial2.begin(4800);
//        Serial2.println("@F0.3=1*67");//Reset the compass.
//        Serial2.readBytes(buf, 10);
//        Serial.println(buf);
//        delay(1000);
//        //Serial2.begin(4800);
//        Serial2.println("@F28.6=1*58");//Reset the compass.
//        Serial2.readBytes(buf, 10);
//        Serial.println(buf);
//        Serial2.println("@B6?*4B");//Reset the compass.
//        Serial2.readBytes(buf, 10);
//        Serial.println(buf);
        //Serial2.begin(4800);
        delay(1000);
        
       
}

void loop() {
	//Serial.println(freeMemory());
	Serial2.println("$PTNT,HTM*63");
        stat = c->update();
	if(stat!=0) {
		Serial.println("Polling failed.");
	}else {
		vars = c->getVariables(2,comp);
		if(vars!=NULL){
			Serial.print("Compass Heading: ");
			Serial.print(vars[0]);
			Serial.print(", Status: ");
			Serial.println(vars[1]);
			for(int i = 0; i <2; i++) {
				free(vars[i]);
			}
			free(vars);
		}
	}
    
}

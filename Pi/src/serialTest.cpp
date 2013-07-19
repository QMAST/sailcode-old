//A simple test to see if I can just get a serial echo from the Arduino onto standard output.
//This will help test and debug the serial communications stuff. 
//The arduino will just spit out a line of text every once in a while, and the Pi will attempt to read it.
//This does not test interrupts!

#include <string>
#include <stdlib>
#include <iostream>

#include "arduinoCom.h"
#include "logging.h"
int main(int argc, char* argv[]) {
	
	Logging::init();
	ArduinoCom ard = new ArduinoCom("/dev/ttyACM0", 2);
	std::string msg="";
	int stat;


	while(true) {
		stat=ard.readBlock(msg);
		if(stat==0) {
			std::cout<<msg<<endl;
		}
		else {
			std::cout<<"Read failed"<<endl;
		}
		usleep(1000*1000);
	}
}


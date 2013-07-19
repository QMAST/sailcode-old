#include <string>
#include <stdlib.h>
#include <iostream>

#include "arduinoCom.h"
#include "logging.h"
int main(int argc, char* argv[]) {
	
	Logging::init();
	ArduinoCom* ard = new ArduinoCom("/dev/ttyACM0", 2);
	std::string msg="";
	int stat;
	int i=0;

	while(i<10) {
		ard->raiseInterrupt();
		usleep(1000*10);

		stat=ard->readBlock(msg);
		if(stat==0) {
			std::cout<<msg;
		}
		else {
			std::cout<<"Read failed"<<std::endl;
		}
		usleep(1000*1000);
		i++;
	}
}

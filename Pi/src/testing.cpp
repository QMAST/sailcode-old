#include <string>
#include <iostream>
#include <unistd.h>
#include "logging.h"
#include "arduinoCom.h"
#include "gpio.h"

using namespace std;

ArduinoCom* ac;

int main(int argc, char* argv[]) {

	//Simple place to test individual features.
	ac = new ArduinoCom("/dev/ttyACM0", 2);
	std::string str = "";

	for(int i=0;i<10;i++) {
		
		ac->requestVariables("test","test1 test2", str);
		cout<<str<<endl;
	}
	cout<<"End test"<<endl;

	/*
	int stat;
	stat = GPIO::init();
	if(stat!=0) {
		std::cout<<"GPIO not initialized."<<endl;
		return -1;
	}

	stat = GPIO::setPin(2,OUTPUT);
	if(stat!=0) {
		std::cout<<"GPIO pin not set."<<endl;
		return -1;
	}


	while(true) {
		stat = GPIO::digitalWrite(2, LOW);
		std::cout<<"Pin lowered"<<endl;
		usleep(1000*2000);
		stat = GPIO::digitalWrite(2, HIGH);
		std::cout<<"Pin raised"<<endl;
		usleep(1000*5000);
	}
	*/
}
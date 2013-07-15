#include "arduinoCom.h"

ArduinoCom::ArduinoCom(const std::string &path, int pin){
	//Takes as an argument the pin 
	//which the arduino interrupt is connected to, 
	//and the path of the usb port which that same arduino is hooked up to.
	int stat;
	this->fildes =-1;
	stat = GPIO::init();
	if(stat!=0) {
		Logging::error(__func__, "Error Setting up the Arduino.");
		return;
	}
	GPIO::setPin(pin, OUTPUT);
	this->interruptPin = pin;

	stat = this->openPort(path);
	if(stat!=0) {
		Logging::error(__func__, "Error setting up the arduino.");
	}
}

int ArduinoCom::requestVariables(const std::string &source ,
							const std::string &labels, 
							std::string &vars) {
	/*
		This method takes a name of a Sensor (registered in the arduino),
		And a space-separated string of variable id's
		and returns a comma seperated string of those variable values.
		Ex: 
		requestVariables("airmar","lat lon heading",vars);
	*/

	std::string resp = "";
	//First, raise an interrupt, and wait for a '>' from the arduino.
	GPIO::digitalWrite(this->interruptPin, HIGH);
	usleep(10*1000);
	GPIO::digitalWrite(this->interruptPin, LOW);
	GPIO::digitalWrite(this->interruptPin, HIGH);


	/*
	Want to wait for response for Arduino, but not get thrown 
	off by any leftover debugging statements in the arduino code.
	Actual communications from the Arduino start with a >. 
	How to do this?
	Just keep reading lines until we get one that starts with a >, within a timeout.

	*/
	time_t startTime = time(NULL);
	int stat = 1;
	while(difftime(time(NULL) , startTime) < 10) {//Wait for up to 5 seconds for a response
		
		
		stat = this->readBlock(resp);//Read a line...
		if(stat == 0) {
			if(resp.find(">")!=-1) {
			//Found the > sign, arduino is ready to respond.
				break;
			}
		}
	}

	if(stat!=0 || resp.find(">")==-1){
		//Something went wrong - haven't received anything yet.
		Logging::error(__func__,"Arduino not responsive to interrupt - timeout occured.");
		return -1;
	}

	stat = this->sendCommand("req "+source+" "+labels+"\n", vars);
	if(stat!=0) {
		Logging::error(__func__,"Variables not returned. Response: "+resp+", Variables:"+vars);
		return -1;
	}
	
	return 0;
}
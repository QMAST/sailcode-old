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
	int stat;
	
	//First, raise an interrupt, and wait for a '>' from the arduino.
	this->raiseInterrupt();


	if(this->waitForResponse()!=0) {
		//Error occured.
		Logging::error(__func__, "Wait for response failed.");
		return -1;
	}
	

	stat = this->sendCommand("req "+source+" "+labels+"\n", vars);
	if(stat!=0) {
		Logging::error(__func__,"Variables not returned. Variables:"+vars);
		return -1;
	}
	
	return 0;
}

int ArduinoCom::setHeading(int direction) {
	std::string vars = "";
	this->raiseInterrupt();

	if(this->waitForResponse()!=0) {
		//Error occured.
		Logging::error(__func__, "Wait for response failed.");
		return -1;
	}
	//Convert direction to string, send it to arduino

	int stat = this->sendCommand("dir "+std::to_string(direction)+"\n", vars);
	if(stat!=0) {
		Logging::error(__func__, "Response not received: "+vars);
	}

	return 0;
}

void ArduinoCom::raiseInterrupt() {
	GPIO::digitalWrite(this->interruptPin, HIGH);
	usleep(10*100);
	GPIO::digitalWrite(this->interruptPin, LOW);
	usleep(10*100);
	GPIO::digitalWrite(this->interruptPin, HIGH);
}

int ArduinoCom::waitForResponse() {
	/*
	Want to wait for response for Arduino, but not get thrown 
	off by any leftover debugging statements in the arduino code.
	Actual communications from the Arduino start with a >. 
	How to do this?
	Just keep reading lines until we get one that starts with a >, within a timeout.
	Also need to limit the rate at which readBlock is called -
	A couple of times when tested, readBlcok would return an error immediately, and go into a crazy fast loop.
	Want to avoid that by limiting the "frame rate"
	*/
	std::string resp = "";

	time_t startTime = time(NULL);
	time_t frameBegin;
	int stat = 1;
	while(difftime(time(NULL) , startTime) < 5) {//Wait for up to 5 seconds for a response
		frameBegin = time(NULL);
		
		stat = this->readBlock(resp);//Read a line...
		if(stat == 0) {
			if(resp.find(">")!=-1) {
			//Found the > sign, arduino is ready to respond.
				break;
			}
		}
		while(difftime(time(NULL) , frameBegin) < 1) {//Wait for at least 1 second between calls to readBlock
			usleep(100*1000);//Sleep for 100 milliseconds.
		}

	}

	if(stat!=0 || resp.find(">")==-1){
		//Something went wrong - haven't received anything yet.
		Logging::error(__func__,"Arduino not responsive to interrupt - timeout occured.");
		return -1;
	}

	return 0;
}
#include "rc.h"

int RC::getPWMValue(int pinIn) {
	int RCVal = pulseIn(pinIn, HIGH, 20000);
	return RCVal;
}

/*The following four functions return the positions
of the 4 remote throttles from -100 to 100
*/
int RC::getValueRV() {
	int pwm = this->getPWMValue(CHANNEL2);
	if(pwm < 100)//Incredibly low value, an error
	{
		return -1000;
	}
	pwm = map(pwm, 1000,2000, -100, 100);
	if(pwm>100) {
		pwm=100;
	}
	else if(pwm<-100){
	 	pwm=-100;
	}
	return pwm;
}

int RC::getValueRH() {
	int pwm = this->getPWMValue(CHANNEL1);
	if(pwm < 750) {
		return -1000;
	}
	pwm = map(pwm, 1000, 1900, -100, 100);
	if(pwm>100) {
		pwm=100;
	}
	else if(pwm<-100){
	 	pwm=-100;
	}
	return pwm;
}

int RC::getValueLV() {
	int pwm = this->getPWMValue(CHANNEL3);
	if(pwm < 750) {
		return -1000;
	}
	pwm = map(pwm, 1000, 1800, -100, 100);
	if(pwm>100) {
		pwm=100;
	}
	else if(pwm<-100){
	 	pwm=-100;
	}
	return pwm;
}

int RC::getValueLH() {
	int pwm = this->getPWMValue(CHANNEL4);
	if(pwm < 750) {
		return -1000;
	}
	pwm = map(pwm, 950, 1950, -100, 100);
	if(pwm>100) {
		pwm=100;
	}
	else if(pwm<-100){
	 	pwm=-100;
	}
	return pwm;
}

//Returns true if the gear switch is "up" (relative to how you hold the remote)
bool RC::gearSwitchUp() {
	int pwm = this->getPWMValue(CHANNEL5);
	return (pwm < 1500);
}

int RC::getValueAux() {
	//Returns a value between 0 and 100 based on the auxilliary switch.
	int pwm = this->getPWMValue(CHANNEL6);
	if(pwm < 800) {
		return -1000;
	}
	pwm = map(pwm, 1150,1850,0,100);
	if(pwm > 100) {
		pwm = 100;
	} else if(pwm<0) {
		pwm = 0;
	}
	return pwm;
}
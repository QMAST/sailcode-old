#ifndef _ARDUINOCOM_H
#define _ARDUINOCOM_H

#include "serial.h"
#include "logging.h"
#include "gpio.h"
#include <string>



class ArduinoCom : public Serial {
public:
	ArduinoCom(const std::string &path, int pin);
private:
int requestVariables(const std::string &source, 
					const std::string &labels, 
					std::string &vars);

int interruptPin;
};


#endif
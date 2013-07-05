#ifndef _RC_H
#define _RC_H

#include <Arduino.h>

//Pin numbers for each channel
#define CHANNEL1 4 //Right knob, left/right level.
#define CHANNEL2 5
#define CHANNEL3 6
#define CHANNEL4 7
#define CHANNEL5 8
#define CHANNEL6 9
#define CHANNEL7 10 //Should be unused

class RC {
public:
	int getPWMValue(int pinIn);

	int getValueRV();
	int getValueRH();
	int getValueLV();
	int getValueLH();
	bool gearSwitchUp();
	int getValueAux();
};

#endif
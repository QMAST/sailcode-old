#ifndef _GAELFORCE_H
#define _GAELFORCE_H

#include <string>
#include "logging.h"

class Gaelforce {
public:
	Gaelforce(ArduinoCom* lineIn);
	int updateGPS();//Update Lat/Lon with most recent arduino data.
	int updateCompass();//Update heading/dev/var with most recent arduino data.
	int updateOG();//Update courseOG/speedOG

	double heading, dev, var;
	double courseOG, speedOG;
	double lat, lon;
private:
	ArduinoCom* lineIn;
};

#endif
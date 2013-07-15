#ifndef _GAELFORCE_H
#define _GAELFORCE_H

#include <string>
#include "logging.h"

class Gaelforce {
public:
	Gaelforce(Airmar* am);

	int updateCompass();
	int updateGPS();
	
	double *heading, *pitch, *roll, *dip;
	//double *courseOG, *speedOG;
	double *lat, *lon;
private:
	Airmar* airmar;
	Compass* compass;
};

#endif
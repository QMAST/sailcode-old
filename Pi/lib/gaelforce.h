#ifndef _GAELFORCE_H
#define _GAELFORCE_H

#include <string>
#include "logging.h"

class Gaelforce {
public:
	Gaelforce(Airmar* am);

	double heading, dev, var;
	double courseOG, speedOG;
	double lat, lon;
private:
	Airmar* airmar;
};

#endif
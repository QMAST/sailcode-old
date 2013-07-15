#include "gaelforce.h"

Gaelforce::Gaelforce(Airmar* am, Compass* comp) {
	this->airmar = am;
	this->compass = comp;
}

int Gaelforce::updateCompass() {
	//Right now, its stupid simple, just because I don't have multiple sensors going.
	//When I get multiple sensors, I need to get all those values, 
	//debate on which one is the best and obtain a single good value.
	this->compass->getValues(this->heading, this->pitch, this->roll, this->dip);
	return 0;
}


int Gaelforce::updateGPS() {
	this->airmar->getGPS(lat, lon);
	return 0;
}


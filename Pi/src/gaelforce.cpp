#include "gaelforce.h"

Gaelforce::Gaelforce(Airmar* am) {
	this->airmar = am;

	
}

int Gaelforce::updateCompass() {
	//Right now, its stupid simple, just because I don't have multiple sensors going.
	//this->airmar->getCompass();
	return 0;
}


int Gaelforce::updateGPS() {
	return 0;
}


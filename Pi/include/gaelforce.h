#ifndef _GAELFORCE_H
#define _GAELFORCE_H

class Gaelforce {
public:
	Gaelforce();
	int updateGPS();//Update Lat/Lon with most recent arduino data.
	int updateCompass();//Update heading/dev/var with most recent arduino data.
	int updateOG();//Update courseOG/speedOG
private:
	double heading, dev, var;
	double courseOG, speedOG;
	double lat, lon;
};

#endif
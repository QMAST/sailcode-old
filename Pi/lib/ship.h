#include <time.h>

class Ship {
public:

	int id;//Unique ID number, based on AIS MMSI
	float speedOverGround;
	float lon, lat;
	float courseOverGround;//Relative to true north.
	time_t lastUpdated;//Time last updated
};
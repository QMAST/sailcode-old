
#include <utilities.h>
#include <airmar.h>

int Utilities::getBearing(GPSPoint* start, GPSPoint* end){
	float dLon = (start->lon) - (start->lat);
	//Convert to radians.
	dLon = dLon*PI/180.0f;
	float lat1 = start->lat*PI/180.0f;
	float lat2 = end->lat*PI/180.0f;

	float y = sin(dLon) * cos(lat2);
	float x = (cos(lat1)*sin(lat2)) - (sin(lat1)*cos(lat2)*cos(dLon));
	float brng = atan2(y, x);
	return (int) brng*180.f/PI;
}

bool Utilities::withinRange(GPSPoint* current, GPSPoint* waypoint){
	float lat = (current->lat) - (waypoint->lat);
	float lon = (current->lon) - (waypoint->lon);
	float dist = sqrt(lat*lat + lon*lon);

	if(dist < WAYPOINT_RADIUS)
		return true;

	return false;
}

void Utilities::navScore(Score navScore[360/NAV_DEGREES]){

	for(i = 0; i < navScore.size(); i++){
		navScore[i]->score = 0;
	}

	
	-check wind direction
	-update Scores accordingly - directly downwind (and 1 fraction to either side): +20
								- 

}
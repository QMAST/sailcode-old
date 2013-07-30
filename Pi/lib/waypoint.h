//Class to handle waypoints which are maintained as a linked list
//Really just handles interacting with a list


#ifndef _NAVPOINTS_H_
#define _NAVPOINTS_H_ 

#include <list>
#include "utilities.h"

#define WAYPOINT_RADIUS 1 //acceptable radius around waypoint (in seconds)

typedef struct 
{
	float lat;
	float lon;
	float radius;
	int angle; //for checking if we have past the waypoint yet - 0 for east check
} waypoint;


class navPoints{
public:
	navPoints();

	void addPointFront(waypoint& newPoint); //add a single waypoint to front of list
	//void addPoints(int size, GPSPoint* newPoints[size]); //add an array of points in order
	void withinRange(GPSPoint& current);
	void passedOutofRange(GPSPoint& current); //check if we have gone based the waypoint (uses waypoint.angle)
	void removeWaypoint();

	int numWaypoints;
	waypoint nextPoint;
	std::list<waypoint> points;

};



#endif

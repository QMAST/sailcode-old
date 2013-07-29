//Class to handle waypoints which are maintained as a linked list
//Really just handles interacting with a list


#ifndef _WAYPOINT_H_
#define _WAYPOINT_H_ 

#include <list>
#include "utilities.h"



class waypoint{
public:
	waypoint();

	void addPointFront(GPSPoint* newPoint); //add a single waypoint to front of list
	void addPoints(int size, GPSPoint* newPoints[size]); //add an array of points in order
	void removeWaypoint();

	int numWaypoints;
	GPSPoint nextPoint;
	list<GPSPoint> points;

};



#endif

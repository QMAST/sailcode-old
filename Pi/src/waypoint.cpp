#include "waypoint.h"

waypoint::waypoint(){

	//this->points = list<GPSPoint> pointList(points, points + sizeof(points)/sizeof(GPSPoint));
	std::list<GPSPoint> pointList;
	this->numWaypoints = 0;

}

/*
	for(int i = size-1; i => 0; i--)
	{
		this->points.push_front(newPoints[i]);
	}
	this->numWaypoints = numWaypoints + size;
	this->nextPoint = points.front();

}*/

void waypoint::addPointFront(GPSPoint newPoint){

	this->points.push_front(newPoint);
	this->numWaypoints++;
	this->nextPoint = newPoint;

}

void waypoint::removeWaypoint(){

	if( this->numWaypoints == 1)
		return;

	this->points.pop_front();
	this->numWaypoints--;
	this->nextPoint = points.front();
}

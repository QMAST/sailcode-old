#include "waypoint.h"

waypoint::waypoint(){

	//this->points = list<GPSPoint> pointList(points, points + sizeof(points)/sizeof(GPSPoint));
	list<GPSPoint> pointList;
	this->numWaypoints = 0;

}

void waypoint::addPoints(int size, GPSPoint newPoints[size]){

	for(int i = size-1; i => 0; i--)
	{
		this->points.push_front(newPoints[i]);
	}
	this->numWaypoints = numWaypoints + size;
	this->nextPoint = points.front();

}

void waypoint::addPointFront(GPSPoint* newPoint){

	this->points.push_front(newPoint);
	this->size++;
	this->nextPoint = newPoint;

}

void waypoint::removeWaypoint(){

	this->points.pop_front();
	this->size--;
	this->nextPoint = points.front();
}

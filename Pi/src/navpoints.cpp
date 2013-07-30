#include "waypoint.h"
#include <string>
#include <iostream>
using namespace std;

#define testing 1

navPoints::navPoints(){

	//this->points = list<GPSPoint> pointList(points, points + sizeof(points)/sizeof(GPSPoint));
	std::list<waypoint> pointList;
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

void navPoints::addPointFront(waypoint& newPoint){

	this->points.push_front(newPoint);
	this->numWaypoints++;
	this->nextPoint = newPoint;
	if (testing)
		cout << "New waypoing added" <<endl;

}

void navPoints::removeWaypoint(){

	if( this->numWaypoints == 1)
		return;

	this->points.pop_front();
	this->numWaypoints--;
	this->nextPoint = points.front();
}

void withinRange(GPSPoint& current){

	float lat = (current.lat) - (nextPoint.lat);
	float lon = (current.lon) - (nextPoint.lon);
	float dist = sqrt(lat*lat + lon*lon);

	if(dist < nextPoint.radius)
	{
		removeWaypoint();
		if(testing)
				cout<<"Within range - waypoint removed" <<endl;
	}
	if(testing)
		cout<<"Not in range - keep going" << endl;

}

void passedOutofRange(GPSPoint& current){

	if(nextPoint.angle == 0) //check if past east
	{
		if(current.lon <= nextPoint.lon) //if we hit 0 we have gone past the Atlantic anyway =P
		{
			removeWaypoint();
			if(testing)
				cout<<"Passed Waypoint - removed" <<endl;
		}
	}
	else if(nextPoint.angle == 90) //check if past south
	{
		if(current.lat <= nextPoint.lat) //for north atlantic - really shouldn't have to worry about the equator
		{
			removeWaypoint();
			if(testing)
				cout<<"Passed Waypoint - removed" <<endl;
		}
	}
	else if(nextPoint.angle == 180) //check if past west
	{
		if(current.lon >= nextPoint.lon)
		{
			removeWaypoint();
			if(testing)
				cout<<"Passed Waypoint - removed" <<endl;
		}
	}
	else if(nextPoint.angle == 270) //check if past north
		if(current.lat >= nextPoint.lat){
			removeWaypoint();
			if(testing)
				cout<<"Passed Waypoint - removed" <<endl;
		}
	}
	else
	{
		GPSPoint next = {nextPoint.lat, nextPoint.lon};
		int bearing = getBearing(current, next);
		if(nextPoint.angle < 180)
		{
			if((bearing > nextPoint.angle) && (bearing < (nextPoint.angle+180)))
			{
				removeWaypoint();
				if(testing)
					cout<<"Passed Waypoint - removed" <<endl;
			}
		}
		else
		{
			if((bearing > nextPoint.angle) || (bearing < (nextPoint.angle-180)))
			{
				removeWaypoint();
				if(testing)
					cout<<"Passed Waypoint - removed" <<endl;
			}
		}
	}
	if(testing)
		cout << "Not yet passed, keep going" << endl;
}









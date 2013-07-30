#include "navpoints.h"
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

void navPoints::withinRange(GPSPoint& current){

	float lat = (current.lat) - (this->nextPoint.lat);
	float lon = (current.lon) - (this->nextPoint.lon);
	float dist = sqrt(lat*lat + lon*lon);

	if(dist < this->nextPoint.radius)
	{
		this->removeWaypoint();
		if(testing)
				cout<<"Within range - waypoint removed" <<endl;
	}
	if(testing)
		cout<<"Not in range - keep going" << endl;

}

void navPoints::passedOutofRange(GPSPoint& current){

	if(this->nextPoint.angle == 0) //check if past east
	{
		if(current.lon <= this->nextPoint.lon) //if we hit 0 we have gone past the Atlantic anyway =P
		{
			this->removeWaypoint();
			if(testing)
				cout<<"Passed Waypoint - removed" <<endl;
		}
	}
	else if(this->nextPoint.angle == 90) //check if past south
	{
		if(current.lat <= this->nextPoint.lat) //for north atlantic - really shouldn't have to worry about the equator
		{
			this->removeWaypoint();
			if(testing)
				cout<<"Passed Waypoint - removed" <<endl;
		}
	}
	else if(this->nextPoint.angle == 180) //check if past west
	{
		if(current.lon >= this->nextPoint.lon)
		{
			this->removeWaypoint();
			if(testing)
				cout<<"Passed Waypoint - removed" <<endl;
		}
	}
	else if(this->nextPoint.angle == 270) //check if past north
		if(current.lat >= this->nextPoint.lat){
			this->removeWaypoint();
			if(testing)
				cout<<"Passed Waypoint - removed" <<endl;
		}
	}
	else
	{
		GPSPoint next = {this->nextPoint.lat, this->nextPoint.lon};
		int bearing = getBearing(current, next);
		if(this->nextPoint.angle < 180)
		{
			if((bearing > this->nextPoint.angle) && (bearing < (this->nextPoint.angle+180)))
			{
				this->removeWaypoint();
				if(testing)
					cout<<"Passed Waypoint - removed" <<endl;
			}
		}
		else
		{
			if((bearing > this->nextPoint.angle) || (bearing < (this->nextPoint.angle-180)))
			{
				this->removeWaypoint();
				if(testing)
					cout<<"Passed Waypoint - removed" <<endl;
			}
		}
	}
	if(testing)
		cout << "Not yet passed, keep going" << endl;
}









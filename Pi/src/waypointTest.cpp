//waypoint class testing

#include "navpoints.h"
#include "utilities.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

	GPSPoint first = {4415.4000, 7633.3137}; // not in range - keep going
	GPSPoint second = {4413.0000, 7629.9999}; //for testing - should be in range of first point but not passed
	GPSPoint third = {4410.0000, 7615.0000}; // should be passed secondW 

	waypoint firstW = {4413.4334, 7629.3137, 1, 0};
	waypoint secondW = {4400.0000, 7620.0000, 1, 0};


	navPoints* test = new navPoints();
	test->addPointFront(secondW);
	test->addPointFront(firstW);

	cout<< "Testing - should not be in range x2" <<endl;
	test->withinRange(first);
	test->withinRange(first);

	cout << "Should not be passed:  "<<endl;
	test->passedOutofRange(second);
	cout << "Should be in range: " <<endl;
	test->withinRange(second);

	cout << "Not in range: " << endl;
	test->withinRange(third);
	cout << "Should be passed" <<endl;

	cout << "second waypoint should not be removed - waypoints should be 1: " <<endl;
	cout<< test.numWaypoints <<endl;


	

	/* Used for previous test
	test->removeWaypoint();
	test->removeWaypoint();
	test->removeWaypoint();
	GPSPoint next = test->nextPoint;
	//test->removeWayPoint();


	cout<<"Testing GPSPoint"<<endl;
	cout<< "Lat: " <<next.lat<< " Lon: " << next.lon<<endl; */

}

#include "utilities.h"
#include "airmar.h"
#include "buffer.h"



void Utilities::navScore(Score navScore[NAV_ELEMENTS], Airmar* windSensor){

	//reset to zero
	for(int i = 0; i < NAV_ELEMENTS; i++){
		navScore[i].score = 0;
	}

	//get wind average
	int windDir = windSensor->wHeading->avg;

	//set navScore based on windDir
	for(int i = 0; i< NAV_ELEMENTS;i++){
		int diff = abs(windDir- navScore->direction);
		if (diff > 180)
			diff = 360 - diff;
		if(diff >= 170)
			navScore[i].score+= 20;
		else if(diff >=135)
			navScore[i].score+=10;
		else if(diff >=90)
			navScore[i].score+=5;
	}
}
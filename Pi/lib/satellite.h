#ifndef _SATELLITE_H_
#define _SATELLITE_H_ 
#endif

#include <string>
#include <path>
#include <termios.h>
#include <vector>
//Enum containing all the error codes that are currently supported. More will be added
enum ErrorCode {
	//Airmar errors
	AMNR = 0, //Airmar not responsive
	AMIWV = 1, //
	AMPBT = 2,

	//Compass errors
	CNR = 64, //Compass not responsive
	CEPV = 65, //Extreme pitch value
	CERV = 66, //Extreme roll value
	CEDV = 67,  //Extreme dip value

	//AIS Errors
	AISNR = 128,//AIS not responsive

	//Generic Errors/messages.
	PIRW = 192, //Reached waypoint succesfully
	PIPW = 193, //Passed Waypoint without reaching it 
	PIRD = 194, //Reached destination
	PISR = 195 //System rebooted
}


class Satellite : public Serial{
public:
	Satellite(const std::string& path);
	int sendMessage(float lat, float lon, float avgWind, 
		short int windDir, short int heading, float peakWind);
	void addError(ErrorCode err, char* payload);
private:
	int send(const char[] msg, int length);
	std::vector<char> errList;
};
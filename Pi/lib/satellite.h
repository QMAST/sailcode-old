#ifndef _SATELLITE_H_
#define _SATELLITE_H_ 
#endif

#include <string>
#include <path>
#include <termios.h>

class Satellite : public Serial{
	public:
	Satellite(const std::string& path);
	int sendMessage(const std::string &msg);
};
#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H

#include <time.h>

class Environment
{
public:
	Environment();
	int updateWind();
	int updateTime();
	
private:
	double windSpeed, windDir;
	struct tm time;
};

#endif
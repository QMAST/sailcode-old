#ifndef NMEA_H
#define NMEA_H

#include <string>

typedef enum {//Enum which stores all the different possible NMEA headings we may encounter.
	HCHDG,
	WIMWV,
	GPVTG,
	GPGLL,
	GPRMC
} NMEA_head_t;

typedef struct NMEAData {
	NMEA_head_t header;
	char** data;
};

class NMEA {
public:
	static int parseString(char* msg, NMEAData* nmea);
private:
	static int hexToDecimal(char hex);
};
#endif
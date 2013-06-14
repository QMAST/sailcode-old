#include "nmea.h"

int NMEA::parseString(char* msg, NMEAData* nmea) {
	//This message parses a generic NMEA string and returns it in an NMEAData struct.
	//This separates the data types making it easier for further parsing, and will check the checksum.
	//Will return a -1 if the checksum is invalid.
	int i, j;
	unsigned char check=0;
	if(msg==NULL || nmea==NULL) {
		return -1;
	}
	j=0;
	while(msg[j]!='*' && msg[j]!='\0') j++;//Find the index of the * or end of the string, whichever is first.

	//Calculate the checksum;
	for(i = 0; i<j; i++) {
		check ^= (unsigned char) msg[i]; //Compute the checksum
	}

	//Compare the computed sum against the given sum.
	//The given sum is given as two Hex characters. 
	unsigned char sum = 0;
	sum += (unsigned char) hexToDecimal(msg[j+2]); 
	sum += (unsigned char) 16 * hexToDecimal(msg[j+1]);
	if(sum!=check) {
		return -1;
	}

	//First, get heading info.
	//Assume we have the $ as the first character.
	char* headString = strtok(&(msg[1]), ",*");

	//Look up how many arguments this header has:
	int numArgs;
	
	if(strcmp(headString, "HCHDG")) { //Heading, deviation and variation
		//5 data fields
		nmea->header = HCHDG;
		numArgs = 5;
	}
	else if(strcmp(headString, "WIMWV")) {//Wind speed, angle relative to bow/centerline
		//5 data fields
		nmea->header = WIMWV;
		numArgs = 5;
	}
	else if(strcmp(headString, "GPVTG")) {//Course over ground/speed
		//9 data fields
		nmea->header = GPVTG;
		numArgs = 9;
	}
	else if(strcmp(headString, "GPGLL")) {//Geographic position
		//Has 7 data fields
		nmea->header = GPGLL;
		numArgs = 7;
	}
	else if(strcmp(headString, "GPRMC")) {//Recommended minimum specific data
		//Has 12 data fields
		nmea->header = GPRMC;
		numArgs = 12;
	}//Add more as necessary, for other sensors.
	else {//Unrecognized NMEA header
		return -1; 
	}

	nmea->data = (char**) malloc(sizeof(char*)*numArgs);
	for(i=0; i<numArgs; i++) {
		nmea->data[i] = strtok(NULL, ",*");
	}

	return 0;
}

int NMEA::hexToDecimal(char hex) {
	return (hex>='A') ? (hex- 'A' + 10) : (hex - '0'); //converts a hex character into a decimal number.
}

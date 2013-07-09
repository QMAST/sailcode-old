#include "nmea.h"
#define DEBUG 0

using namespace std;

int NMEA::parseString(char* msg, NMEAData* nmea) {
	//This message parses a generic NMEA string and returns it in an NMEAData struct.
	//This separates the data types making it easier for further parsing, and will check the checksum.
	//Will return a -1 if the checksum is invalid.

	int i, j;
	unsigned char check=0;
	if(msg==NULL || nmea==NULL) {
		if(DEBUG) {
			Serial.println("Passed a null value.");
		}
		return -1;
	}
	
	if(msg[0]!='$') {
		//Invalid NMEA String, at least from AIRMAR
		if(DEBUG) {
			Serial.println("No $ detected");
		}
		
		return -1;
	}

	j=0;
	while(msg[j]!='*' && msg[j]!='\0') j++;//Find the index of the * or end of the string, whichever is first.

	//Calculate the checksum;
	for(i = 1; i<j; i++) {
		check ^= (unsigned char) msg[i]; //Compute the checksum
	}

	//Compare the computed sum against the given sum.
	//The given sum is given as two Hex characters. 
	unsigned char sum = 0;
	sum += (unsigned char) hexToDecimal(msg[j+2]); 
	sum += (unsigned char) 16 * hexToDecimal(msg[j+1]);
	if(sum!=check) {
		if(DEBUG) {
			Serial.println("Invalid Checksum: ");
		}
		return -1;
	}

	
	//First, get heading info.
	//Assume we have the $ as the first character.
	char* headString = strtok(msg, ",");
	if(headString==NULL) {
	} else {
		headString = &(headString[1]);
	}
	//Look up how many arguments this header has:
	int numArgs;
	//Serial.print("Header String:");
	//Serial.println(headString);
	if(strncmp(headString, "HCHDG",5)==0) { //Heading, deviation and variation
		//5 data fields
		nmea->header = HCHDG;
		numArgs = 5;
	}
	else if(strncmp(headString, "WIMWV",5)==0) {//Wind speed, angle relative to bow/centerline
		//5 data fields
		nmea->header = WIMWV;
		numArgs = 5;
	}
	else if (strncmp(headString, "PTNTHTM",7)==0) { //heading from compass
		//8 data fields
		nmea->header = PTNTHTM;
		numArgs = 8;
	}
	else if(strncmp(headString, "GPVTG",5)==0) {//Course over ground/speed
		//9 data fields
		nmea->header = GPVTG;
		numArgs = 9;
	}
	else if(strncmp(headString, "GPGLL", 5)==0) {//Geographic position
		//Has 7 data fields
		nmea->header = GPGLL;
		numArgs = 7;
	}
	else if(strncmp(headString, "GPRMC", 5)==0) {//Recommended minimum specific data
		//Has 12 data fields
		nmea->header = GPRMC;
		numArgs = 12;
	}
	else if(strncmp(headString, "GPGGA", 5)==0) {//Recommended minimum specific data
		//Has 12 data fields
		nmea->header = GPGGA;
		numArgs = 14;
	}
	else if(strncmp(headString, "GPZDA", 5)==0) {//Recommended minimum specific data
		//Has 12 data fields
		nmea->header = GPZDA;
		numArgs = 6;
	}
	else if(strncmp(headString, "WIMDA", 5)==0) {//Recommended minimum specific data
		//Has 12 data fields
		nmea->header = WIMDA;
		numArgs = 20;
	}
	else if(strncmp(headString, "WIMWD", 5)==0) {//Recommended minimum specific data
		//Has 12 data fields
		nmea->header = WIMWD;
		numArgs = 8;
	}//Add more as necessary, for other sensors.
	else {//Unrecognized NMEA header
		if(DEBUG) {
			//Serial.print("Unrecognized NMEA Header");
		}
		return -1; 
	}
	nmea->data = (char**) malloc(sizeof(char*)*numArgs);
	nmea->count = numArgs;
	j=0;
	

	while(msg[j] != '\0') j++;//Go through the header info
	j++;
	//Serial.println(&(msg[j]));
	int k;
	//In the next loop, we find all the values, delimited by commas.
	//We use j to index the start of a value, and k to index the end.
	int len;
	for(i=0; i<numArgs; i++) {
		//Right now, j is the beggining of the token.

		//Make k the index of the end of the token.
		k=j;
		while(msg[k]!=',' && msg[k]!='*') k++;
		len = k - j;
		if(len==0){ 
			nmea->data[i] = NULL;
		}
		else{
			
			nmea->data[i] = (char*) malloc(sizeof(char)*(len+1));
			strncpy(nmea->data[i], &(msg[j]), len);
			nmea->data[i][len] = '\0';
			
		}
		j=k+1;
	}
	return 0;
}

int NMEA::hexToDecimal(char hex) {
	return (hex>='A') ? (hex- 'A' + 10) : (hex - '0'); //converts a hex character into a decimal number.
}

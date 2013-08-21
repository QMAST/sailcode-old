#include "aisManager.h"
#include "aisMessage.h"
#include "logging.h"

#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;
int main(int argc, char* argv[]) {

	Logging::init();
	string testMsg = "35Mva0POhoG?Wj6EdWkQ9Aeb023@";
	AISMessage* msg = new AISMessage(testMsg);
	unsigned char* bits;

	cout<<"Testing string 1:\n";
	cout<<"Printing out bytestream:\n";
	for(int i=0; i<msg->streamSize; i++) {
		printf("%.2X ", msg->bitstream[i]);
	}
	
	cout<<"\n";
	cout<<"Message type: "<< msg->getUInt(0, 6)<<"\n";
	cout<<"Longitude: "<< msg->getInt(61, 28) / 600000.0f <<"\n";
	cout<<"Latitude: "<< msg->getInt(89, 27) / 600000.0f <<"\n";
	

	cout<<"Raw test - get first 16 bits individually from the string.\n";
	for(int i = 0; i<16; i++){
		bits = msg->getBits(i, 1);
		printf("%.1X ", *bits);
		delete[] bits;
	}
	cout<<"\n";
	
	cout<<"Raw test 2 - get first 16 bits in 4 bit chunks \n";
	for(int i = 0; i<16; i++) {
		bits = msg->getBits(i, 4);
		printf("%.1X ", *bits);
		delete[] bits;
	}

	cout<<"\nEnd of parsing tests.\n";
	cout<<"Now testing the actual hardware.\n";

	delete[] msg;
	//Create an AIS manager object and attempt to connect with the AIS

	AISManager* manager = new AISManager("/dev/ttyUSB0");

	//Test readSentence
	cout<<"First, test reading a few single sentences:\n";
	
	for(int i=0; i<5; i++) {
		testMsg = "";
		manager->readSentence(testMsg);
		cout<<testMsg<<"\n";
	}
	
	return 0;
}
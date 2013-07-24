#include "aisManager.h"
#include "aisMessage.h"
#include <string>
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
	string testMsg = "35Mva0POhoG?Wj6EdWkQ9Aeb023@";
	AISMessage* msg = new AISMessage(testMsg);
	cout<<"Testing string 1:\n";
	cout<<"Message type: "<< msg->getUInt(8, 30)<<"\n";
	cout<<"Longitude: "<< msg->getInt(61, 28) / 600000.0f <<"\n";
	cout<<"Latitude: "<< msg->getInt(89, 27) / 600000.0f <<"\n";
	cout<<"Raw test - get first 16 bits individually from the string.\n";
	for(int i = 0; i<16; i++){
		cout<< std::hex << msg->getBits(i, 1)<<"\n";
	}

	cout<<"Raw test 2 - get first 16 bits in 4 bit chunks \n";
	for(int i = 0; i<16; i++) {
		cout<<std::hex<< msg->getBits(i, 4)<<"\n";
	}
	cout<<"End of tests.\n";
}
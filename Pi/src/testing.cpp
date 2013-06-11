#include <string>
#include <iostream>

#include "logging.h"
#include "arduinoCom.h"

using namespace std;

ArduinoCom* ac;

int main(int argc, char* argv[]) {
	//Simple place to test individual features.
	ac = new ArduinoCom("/dev/ttyACM0", 9);
	std::string str = "";

	for(int i=0;i<10;i++) {
		ac->requestVariables("test","test1 test2", str);
		cout<<str<<endl;
	}
	cout<<"End test"<<endl;
}
#include <string>
#include <iostream>
#include <unistd.h>
#include "arduinoCom.h"
#include "logging.h"
using namespace std;

int main(int argc, char* argv[]) {

	Logging::init();
	ArduinoCom* ac = new ArduinoCom("/dev/ttyACM0", 2);

	if(!(ac->isValid())) {
		cout<<"Arduino failed to open"<<endl;
		return -1;
	}

	std::string str = "";
	int stat;

	for(int i=0;i<10; i++){
		cout<<"Request no. "<<i+1<<endl;
		stat = ac->requestVariables("test","test1 test2", str);
		if(stat==0) {
			cout<<str<<endl;
		}
		else {
			cout<<"Request failed."<<endl;
		}
	}

	Logging::clean();
}
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
	int i=0;
	while(true){
		i++;
		cout<<"Request no. "<<i+1<<endl;
		stat = ac->requestVariables("compass","compassHeading pitch", str);
		if(stat==0) {
			cout<<str<<endl;
		}
		else {
			cout<<"Request failed."<<endl;
		}
	}

	Logging::clean();

}
#include <string>
#include <iostream>
#include <unistd.h>
#include "logging.h"
#include "arduinoCom.h"
#include "gpio.h"

using namespace std;

ArduinoCom* ac;

int main(int argc, char* argv[]) {

	//Simple place to test individual features.
	ac = new ArduinoCom("/dev/ttyACM0", 2);
	std::string str = "";
	Logging::init();
	double test1, test2;

	Logging::addDataSource(DOUBLE, "test1", &test1);
	Logging::addDataSource(DOUBLE, "test2", &test2);

	char* buf;
	int stat;
	for(int i=0;i<10;i++) {
		cout<<"Request no. "<<i<<endl;
		stat = ac->requestVariables("test","test1 test2", str);
		if(stat==0) {
			buf = new char[str.length()];
			strcpy(buf, str.c_str());
			test1 = atof(strtok(buf, ","));
			test2 = atof(strtok(NULL, ","));

			delete[] buf;
			cout<<str<<endl;
			stat=Logging::log();
			if(stat!=0) {
				cout<<"Log failed to close"<<endl;
			}
		} else {
			cout<<"Request failed"<<endl;
		}
		
	}
	cout<<"End test"<<endl;
	return 0;
}
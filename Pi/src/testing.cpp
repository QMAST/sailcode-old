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

	for(int i=0;i<10;i++) {
		cout<<"Request no. "<<i<<endl;
		ac->requestVariables("test","test1 test2", str);
		buf = new char[resp.length()];
		strcpy(buf, resp.c_str());
		test1 = atof(strtok(buf, ","));
		test2 = atof(strtok(NULL, ","));

		delete[] buf;

		cout<<str<<endl;
		Logging::log();
	}
	cout<<"End test"<<endl;
	return 0;
}
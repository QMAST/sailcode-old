#include <iostream>
#include "logging.h"

using namespace std;

int main(int argc, char* argv[]) {

	Logging::init();

	double* test1 = new double;
	double* test2 = new double;

	Logging::addDataSource(DOUBLE, "test1", &test1);
	Logging::addDataSource(DOUBLE, "test2", &test2);

	for(int i=0;i<10; i++) {
		//Generate some weird numbers to log.
		*test1 = i*3.1415;
		*test2 = i*2.718;
		cout<<"Write "<<i<<endl;
		Logging::log();
	}
}
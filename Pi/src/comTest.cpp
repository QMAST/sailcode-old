#include <string>
#include <iostream>
#include <unistd.h>
#include "arduinoCom.h"

using namespace std;

int main(int argc, char* argv[]) {

	ArduinoCom* ac = new ArduinoCom("/dev/ttyACM0", 2);
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

}
#include <iostream>
#include "serial.h"

using namespace std;


int main(int argc, char* argv[]) {
	int fd;

	cout<<"Testing Serial Communication with arduino over USB" <<endl;

	fd = openSerialPort("/dev/ttyACM0");
	if(fd<0){
		cout<<"Error Opening Serial Port"<<endl;
		return -1;
	}

	

	return 0;
}
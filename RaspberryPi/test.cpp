#include <iostream>
#include "serial.h"

using namespace std;


int main(int argc, char* argv[]) {
	int fd, length, end;

	char* testCommand = "help\r";
	char* buf = (char*) malloc(sizeof(char)*255);
	length=0;
	while(testCommand[length]!='\0')length++;

	cout<<"Testing Serial Communication with arduino over USB" <<endl;

	fd = openSerialPort("/dev/ttyACM0");
	if(fd<0){
		cout<<"Error Opening Serial Port"<<endl;
		return -1;
	}

	write(fd, testCommand, length);


	end =0;
	length=0;
	do {
		end = read(fd, buf, 255);
		if(end==0) length++;
	} while(end>0 && length<100);
	cout<<buf<<endl;
	free(buf);
	return 0;
}
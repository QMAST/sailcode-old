#include "satellite.h"

Satellite::Satellite(const std::string &path) {
	this->fildes=-1;
	stat = this->openPort(path, B19200);
	if(stat!=0) {
		Logging::error(__func__, "Unable to set up the Satellite Communicator.");
	}
}

int Satellite::sendMessage(const std::string &msg) {
	//Compute checksum
	unsigned int checksum = 0;
	for(int i; i<msg.length();i++) {
		checksum += (unsigned int) msg[i];
	}
	//Extract the two bytes needed.
	unsigned char chk[2];
	chk[1] = checksum & 0x00FF;
	chk[0] = (checksum >> 8) & 0x00FF;

	//Send command AT+SBDWB=<message length>
	//Wait for "READY<CR><LF>"
	std::string cmd = "AT+SBDWB="+std::to_string(msg.length());
	std::string ready="";
	this->sendCommand(cmd, ready);

	//Send message followed by two-byte checksum.
	write(this->fildes, msg.c_str(), msg.length());
	write(this->fildes, chk, 2);
}

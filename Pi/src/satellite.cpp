#include "satellite.h"

Satellite::Satellite(const std::string &path) {
	this->fildes=-1;
	stat = this->openPort(path);
	if(stat!=0) {
		Logging::error(__func__, "Unable to set up the Satellite Communicator.");
	}
}

int Satellite::sendMessage(const std::string &msg) {
	//Send command AT+SBDWB=<message length>
	//Wait for "READY<CR><LF>"
	//Send message followed by two-byte checksum.
}
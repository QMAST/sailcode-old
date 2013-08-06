#include "satellite.h"

Satellite::Satellite(const std::string &path) {
	this->fildes=-1;
	stat = this->openPort(path, B19200);
	if(stat!=0) {
		Logging::error(__func__, "Unable to set up the Satellite Communicator.");
	}
	this->errList();
}

int Satellite::send(const char[] msg, int length) {
	//Compute checksum
	unsigned int checksum = 0;
	for(int i; i<length; i++) {
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
	write(this->fildes, msg.c_str(), length);
	write(this->fildes, chk, 2);
}

void Satellite::addError(ErrorCode err, char* payload) {
	//Add the error code as a char to the errList;
	char errCode = (char) err;
	this->errList.push_back(errCode);

	if(payload!=NULL) {
		switch(err) {
			case CEPV:
			case CERV:
			case CEDV:
				//Payload length of 2.
				this->errList.push_back(payload[0]);
				this->errList.push_back(payload[1]);

			break;
			default:
				//Some unknown error code. could cause issues.
			break;
		}
	}
	return;
}

int Satellite::sendMessage(float lat, float lon, float avgWind,
				short int windDir, short int heading, float peakWind) {
	//Construct the byte stream, and determine the length.
	int size = (20 + this->errList.size());
	int length=0;
	//Want to round size to the nearest multiple of 50.
	if(size/50 > 6) {//More than 300 bytes
		length = 300;
	} else {
		length = size - (size % 50);
	}
	char* msg = new char[length];//Might as well make it this long, can expand if necessary to 100 or 150, or so on.
	
	memcpy(msg, &lat, 4);
	memcpy(&(msg[4]), &lon, 4);
	memcpy(&(msg[8]), &avgWind,4);
	memcpy(&(msg[12]), &windDir, 2);
	memcpy(&(msg[14]), &heading, 2);
	memcpy(&(msg[16]), &peakWind, 4);

	size = 20;
	//Now the first 20 bytes should be filled properly.
	//The tricky bit is to not stop sending in the midst of a payload. That'd be bad.
	//So we loop through the list, adding bits to the buffer.
	//If we see one of the bits that has a payload, we add it if there's room, or
	//remove the error and finish sending if there isn't
	char temp;
	int nextSize=1;
	for(int i=0; i<this->errList.size(); i++) {
		temp = this->errList[i];
		switch(temp) {
			case CEPV:
			case CERV:
			case CEDV:
				nextSize = 3;
			break;
			default:
				nextSize = 1;
			break;
		}

		if(length - i < nextSize) {
			break; //Out of space, we're done here.
		}
		for(int j =0; j<nextSize; j++) {
			msg[size] = this->errList[i];
			i++;
			size++;
		}
	}

	//Send the message
	send(msg, size);

	//Clear the error list, saving everything past size.
	this->errList.erase(this->errList.begin(), this->errList.begin()+size);
	
	delete[] msg;
}
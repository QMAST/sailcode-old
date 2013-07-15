#include "serial.h"

Serial::Serial() {
	this->fildes = -1;
}

bool Serial::isValid() {
	return (this->fildes==-1) ? false : true;
}

int Serial::openPort(const std::string &path) {
	int fd, stat;
	struct termios tio;
	fd = open(path.c_str(), O_RDWR | O_NOCTTY);
	if(fd<0) {
		//Catch an error, log it.
		Logging::error(__func__, "Unable to Open Serial Port at " + path + ", errno:" + strerror(errno));
		return -1;
	}

	if(tcgetattr(fd, &tio) < 0) {
		//An error
		std::string errString = strerror(errno);
		Logging::error(__func__, "Unable to get serial port attributes. Errno:" +errString);
		return -1;
	}

	stat = cfsetspeed(&tio, BAUDRATE);
	if(stat!=0) {
		//Another error!
		std::string errString = strerror(errno);
		Logging::error(__func__, "Unable to set baudrate. Errno:" + errString);
		return -1;
	}

	//Set some options
    tio.c_cflag &= ~PARENB;
    tio.c_cflag &= ~CSTOPB;
    tio.c_cflag &= ~CSIZE;
    tio.c_cflag |= CS8;
    // no flow control
    tio.c_cflag &= ~CRTSCTS;
    tio.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
	tio.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
    tio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    tio.c_oflag &= ~OPOST; // make raw
    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
    tio.c_cc[VMIN]  = 0;
    tio.c_cc[VTIME] = TIMEOUT;//Wait 2 full seconds before timing out.

    //Flush the modem line and enable the new settings.

    stat = tcflush(fd, TCIFLUSH);
    stat |= tcsetattr(fd, TCSANOW, &tio);
    if(stat!=0) {
    	//One last error.
    	std::string errString = strerror(errno);
    	Logging::error(__func__, "Unable to set serial port properties. Errno:" + errString);
    	return -1;
    }
    this->fildes = fd;
    usleep(1000*1000); //Wait for the Arduino to reset - approximate, so may need tweaking.
    
    return 0;
}

int Serial::readBlock(std::string &msg) {
	if(!this->isValid()) {
		Logging::error(__func__, "Serial port not initialized properly.");
		return -1;
	}

	char* buf = new char[2];
	int num;
	msg ="";

	buf[0]='\0';
	num=1;

	while((num>0) && buf[0]!='\n' && buf[0]!='\r' && buf[0]!='>') {
		num = read(this->fildes, buf, 1);
		buf[num] = '\0';

		if(num>0) {
			msg +=buf;//omgzors, this is so much easier than before.
		}
	}
	delete[] buf;
	if(num<0) {
		//Error while reading.
		Logging::error(__func__, "Problem while reading from serial port: "+msg+ ". Errno:" + strerror(errno));
		return -1;
	} else if(num==0) {
		Logging::error(__func__, "Didn't read anything from file. Timeout likely occured.");
	}
	else if(buf[0]!='\n' && buf[0]!='\r') {
		//Timeout before reading full line, be cautious
		Logging::error(__func__, "Full line not read :"+msg);
		return -1;
	}
	return 0;
}

int Serial::sendCommand(const std::string &cmd, std::string &resp) {
	int num;
	
	num = write(this->fildes, cmd.c_str(), cmd.length());

	if(num<0) {
		//Log an error
		std::string errString = strerror(errno);
		Logging::error(__func__, "Could not write command. Errno:" + errString);
		return -1;
	}

	if(num<cmd.length()) {
		//Entire command wasn't written, an error occured.
		Logging::error(__func__, "Command not written completely.");
		return -1;
	}

	num = readBlock(resp);
	
	return num;
}

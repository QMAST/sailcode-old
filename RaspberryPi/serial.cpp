int open_serial_port(char* path) {
	int fd, stat;
	struct termios tio;

	fd = open(path, O_RDWR | O_NOCTTY);
	if(fd<0) {
		//Catch an error, return it.
		//I feel like now its okay to use STDIO, for debugging. huzzah.
		return -1;
	}

	bzero(&tio, sizeof(tio)); //Set the memory in this spot to 0.
	//Set Baudrate
	stat = cfsetspeed(&tio, BAUDRATE);
	if(stat!=0) {
		return -1;
	}

	//Set some options
	tio.c_cflag = CS8 | CLOCAL | CREAD;
	tio.c_iflag = IGNPAR | ICRNL;
	tio.c_oflag = 0;
	tio.c_lflag = ICANON;

	//Set the escape characters
	tio.c_cc[VEOF] = 4; //End of file (or transmission)
	tio.c_cc[VEOL] = 0; //End of line ('\0')
	tio.c_cc[VERASE] = 8; //Erase character (backspace)
	tio.c_cc[VINTR] = 3; //Interrupt (ctrl-c)
	tio.c_cc[VKILL] = 21; // Kill line (ctrl-u)
	tio.c_cc[VQUIT] = 27; // Quit (esc)
	tio.c_cc[VSTART] =17; // Start (ctrl-q)
	tio.c_cc[VSTOP] =19; //Stop (ctrl-s)
	tio.c_cc[VSUSP] =26; //Suspend (ctrl-z)
	tio.c_cc[VTIME] = 0; //Inter-character timer unused
	tio.c_cc[VMIN] = 1; //Blocking read until 1 character arrives

	//Flush the modem line and enable the new settings
	stat = tcflush(fd, TCIFLUSH);
    stat |= tcsetattr(fd,TCSANOW,&tio);
    if(stat!=0) {
    	return -1;
    }

    return 0;
}
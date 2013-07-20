#ifndef _SERIAL_H
#define _SERIAL_H

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <sys/stat.h>


#include <errno.h>
#include <string>
#include <string.h>
#include "logging.h"
#include <time.h>

#define BAUDRATE B115200
#define TIMEOUT 30
class Serial {

public:

int fildes;
int openPort(const std::string &path);
int readBlock(std::string &msg);
int sendCommand(const std::string &cmd, std::string &msg);
Serial();
bool isValid();

};

#endif

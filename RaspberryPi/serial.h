#ifndef _SERIAL_H
#define _SERIAL_H 1

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#define BAUDRATE B115200

int openSerialPort(char* path);


#endif
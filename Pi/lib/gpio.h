#ifndef _GPIO_H
#define _GPIO_H

#include "logging.h"

//We also need a bunch of low-level IO for interrupts and such. 
//This will be defined here, unless it grows big enough to merit its own spot.
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

//Pin Options, each GPIO pin has I/O and 6 alt functions.
//Most of the ALTS aren't used, but it's easy to implement so
//Might as well use them.
#define INPUT	0
#define OUTPUT	1
#define ALT0	4
#define ALT1	5
#define ALT2	6
#define ALT3	7
#define ALT4	3
#define ALT5	2

#define LOW 	0
#define HIGH	1

class GPIO {
public:
	static int init();
	static int setPin(int pin, int status); 
	static int digitalWrite(int pin, int level);
private:
	static volatile void* gpio;
};

#endif
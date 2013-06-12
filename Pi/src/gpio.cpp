#include "gpio.h"

volatile int* GPIO::gpio = NULL;

int GPIO::init() {
  if(gpio==NULL) {
    //Already initialized. Not really an error, but should avoid calling multiple times
    Logging::error(__func__, "GPIO attempted to initialize twice");
    return 0;
  }
	int mem_fd;
	void* gpio_map;

	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      Logging::error(__func__, "Error opening Physical Memory.");
      return -1;
    }

    //Map Physical memory (in linux, a file at /dev/mem) 
    //to a pointer in virtual memory. Fun times.
    gpio_map = mmap(
    	NULL, //We don't care where in the virtual address space we are
    	BLOCK_SIZE, //Block size of the memory space
     	PROT_READ|PROT_WRITE, //Give read/write access
     	MAP_SHARED, //Share this mapping with other processess
     	mem_fd, //File to be mapping.
     	GPIO_BASE);//Offset to GPIO peripherals. 
    /*We don't need to worry about unmapping this, 
    	it is automatically unmapped when the process is terminated.
    */

    close(mem_fd);//Close the file, it isn't needed anymore.

    if(gpio_map == MAP_FAILED) {
    	Logging::error(__func__, "Error Mapping Physical Addresses");
    	return -1;
    }

    gpio = (volatile int*) gpio_map;//convert to a volatile pointer.

    return 0;
}

int GPIO::setPin(int pin, int status) {
	if(status<0 || status>7) {
    Logging::error(__func__, "Invalid pin status attempted");
    return -1;
  }
  if(GPIO::gpio==NULL) {
    Logging::error(__func__, "GPIO not initialized - invalid attempted write");
    return -1;
  }
  int offset = pin/10;//Which function set select register to set.
	int shift = (pin%10)*3;//bits to set in the register.
	


  
  //First, set the 3 function select bits to 0, then set them appropriately
  *(GPIO::gpio+offset) &= ~(7<<(shift));
  *(GPIO::gpio+offset) |= (status<<(shift));
  return 0;
}

int GPIO::digitalWrite(int pin, int level){
//Write a pin to be either high or low

  if(pin<0 || pin>53){
    Logging::error(__func__, "Invalid pin number:" + pin);
    return -1;
  }

  //Anything but a 0 is treated as a high.
  int offset = (level==0)? 10 : 7;
  if(pin>31) {
    offset++;
    pin -=31;
  }

  *(GPIO::gpio+offset) &= (1<<pin); 
  return 0;
}
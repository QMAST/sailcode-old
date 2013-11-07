#ifndef CMDLINE_FUNCTIONS_H
#define CMDLINE_FUNCTIONS_H value

#include <Arduino.h>
#include <ashcon.h>
#include <pololu_controller.h>
#include <RadioControl.h>

// Global instances declared in the main sketch that need to be used by the
// command line functions
extern ashcon* Console;
extern polcore* motor;
extern polcore* sail;
extern polcore* mast;
extern RC* radio;
extern PololuMSC* rudder;

// Prototype declarations for cmdline functions
int uabout(char* argv[]); // 
int urctest(char* argv[]);
int urcpollall(char* argv[]);
int umotorGo(char* argv[]); // Sets the speed of a motor or the angle of a servomotor
int ustartRCControl(char* argv[]); // Sets the rudder angle or sail motor speed by RC control
#endif

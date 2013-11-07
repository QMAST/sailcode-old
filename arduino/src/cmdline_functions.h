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
extern RC* radio;

// Prototype declarations for cmdline functions
int uabout(char* argv[]);
int urctest(char* argv[]);
int urcpollall(char* argv[]);
int umon(char* argv[]);
#endif

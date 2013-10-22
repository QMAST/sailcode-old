#ifndef CMDLINE_FUNCTIONS_H
#define CMDLINE_FUNCTIONS_H value

#include <Arduino.h>
#include <ashcon.h>
#include <pololu_controller.h>

// Global instances declared in the main sketch that need to be used by the
// command line functions
extern ashcon* Console;
extern polcore* motor;

// Prototype declarations for cmdline functions
int uabout(char* argv[]);
int upol(char* argv[]);
#endif

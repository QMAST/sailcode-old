/** RC Arduino Library
 *
 * Data structures to model and store preferences for the analog joysticks and
 * switches on the RC controller/receiver.
 */
#ifndef RCSTRUCT_H
#define RCSTRUCT_H
#include <Arduino.h>

#define STD_TIMEOUT 20000 //standard timeout, recommend at least 20000
#define LOOP_DELAY 500

/*Default Pin Values*/
#define RSX_PIN 12
#define RSY_PIN 11
#define LSX_PIN 9
#define LSY_PIN 10

#define GEAR_PIN 8
#define AUX_PIN 7

/* Default output range for axis/knob output */
#define STD_HIGH_OUTPUT 1000
#define STD_LOW_OUTPUT -1000

/* Default Offset Values */
// RSX Receiver ch 1
#define RSX_LOW_OFFSET 1842  // Full left
#define RSX_HIGH_OFFSET 1074 // Full right

                             // RSY Receiver ch 2
#define RSY_HIGH_OFFSET 1855 // Full left
#define RSY_LOW_OFFSET 1123  // Full right

// LSX Receiver ch 4
#define LSX_HIGH_OFFSET 1862 
#define LSX_LOW_OFFSET 1079  

// LSY Receiver ch 3
#define LSY_HIGH_OFFSET 1894 // Full left
#define LSY_LOW_OFFSET 1117  // Full right

// Gear receiver ch 5
#define GEAR_HIGH_OFFSET 1500
#define GEAR_LOW_OFFSET 1089

// AUX knob receiver ch 6
#define AUX_HIGH_OFFSET 1891
#define AUX_LOW_OFFSET 1073

// channel 7 is affected by everything!!!!!!
// lol

// For channels that connect to an RC stick axis or knob
typedef struct RCAxisChannel {
    int pin;         // The input pin

    int highOffset;  // The max length of the pulse
    int lowOffset;   // The min length of the pulse

    int highOutput;  // Range for output
    int lowOutput;

    int outputLevel; // Current output level relative to a given range
} RCAxisChannel;

// For channels that connect to an RC switch
typedef struct RCSwitchChannel {
    int pin;

    int highOffset;
    int lowOffset;

    int numberOfOptions; // Number of switch options
    int outputSelection; // Stores which option is currently selected
} RCSwitchChannel;

// All of the channels required to model our RC controller
typedef struct RC {
    RCAxisChannel* RSX;
    RCAxisChannel* RSY;
    RCAxisChannel* LSY;
    RCAxisChannel* LSX;

    RCSwitchChannel* gearSwitch;
    RCAxisChannel* AUX;
} RC;


RCAxisChannel* initRCAxisChannel( int pinIn, int highOffset, int lowOffset );

/* Initiates a default RC Switch Channel
 *
 * Sets the pin the channel is associate with, declares the maximum and minimum
 * expected values for the channel.
 */
RCSwitchChannel* 
initRCSwitchChannel( int pinIn, int highOffset, int lowOffset );

/* Create and return an instance of the RC object
 *
 * Using all the values specific to our RC controller.
 */
RC* initRC();

/* Updates all channels within the RC object
 */
void updateControllerValues( RC* rc );

/* Sets a custom output range for axis/knob channels
 */
void setOutputRange( RCAxisChannel* ch, int low, int high );

/* Updates Channel from Pulses */
void updateAxisChannelOutput( RCAxisChannel* ch );

void updateSwitchChannelOutput( RCSwitchChannel* ch );

/* Updates channel then returns channel output */
int getAxisOutput( RCAxisChannel* ch );
int getSwitchOutput( RCSwitchChannel* ch );

/* Updates Channel and returns output, 
 *
 * Output is limited to the channel's range
 */
int getBoundedOutput( RCAxisChannel* ch );

/* Updates axis channel from pulse */
void updateAxisPulse( RCAxisChannel* ch );

/* Updates switch channel from pulse */
void updateSwitchPulse( RCSwitchChannel* ch );

/* Prints stick cords. from the two axis channels */
void printStickCords( RCAxisChannel* X, RCAxisChannel* Y );
void printSwitchState( RCSwitchChannel* ch );

void printAll( RC* rc );
void printAll( RCAxisChannel* RSX, RCAxisChannel* RSY, RCAxisChannel* LSX, RCAxisChannel* LSY, RCAxisChannel* AUX, RCSwitchChannel* gear );

#endif


#ifndef POLOLU_CONTROLLER_H
#define POLOLU_CONTROLLER_H 1

#include <Arduino.h>
#include <HardwareSerial.h>

#define PCON_MAX_TO_DEV 4
#define PCON_MAX_FROM_DEV 3

// Time allowed for the pololu to generate a response
#define PCON_RESPONCE_BREATH_TIME 100

#define PCON_DEFAULT_COMMAND_BYTE 0xAA

#define PCON_VAR_BATTERY
#define PCON_VAR_ERROR

// Defined in the .cpp file of same name
extern uint8_t pcon_buffer_to_dev[PCON_MAX_TO_DEV];
extern uint8_t pcon_buffer_from_dev[PCON_MAX_FROM_DEV];

// For debugging, needs to be replaced with something more general
extern HardwareSerial Serial;

enum PCON_CONTROL {
    PCON_IS_RUNNING = 0x1,
    PCON_IS_ATTACHED = 0x2,
    PCON_FEEDBACK_ENABLED = 0x4
};

enum PCON_DIRECTION {
    PCON_FORWORD,
    PCON_BACKWORD
};

typedef struct polcore {
    HardwareSerial* serial_line;
    uint8_t device_number;
    uint32_t shedule_stop_time;
    uint8_t control;
} polcore;

/* Take a pointer to a polcore object and give it a memory address with
 * initialised values.
 */
uint8_t pconInitialise( polcore** dev, 
        HardwareSerial* serial_line, uint8_t dev_number );

/** Writes the command string out on the serial line,
 * Returns an error code
 */
uint8_t pconSendCommand( polcore* dev, uint8_t* cmd );

/** Shortcut function, sends the global buffer down the serial line.
 */
uint8_t pconSendCommandBuffer( polcore* dev );

/** Generate a command to begin turning the motor at a specified power in the
 * specified direction. Uses the PCON_DIRECTION struct.
 *
 * Doesn't actually send the string down the serial line, call
 * pconSendCommand with the buffer as an argument, or store the value to the
 * global buffer and call pconSendCommandBuffer
 *
 * Uses the low-resolution motor speed within the pololu protocol.
 * Specifically, it just sends percentage of the maximum.
 */
uint8_t pconGenMotorGo( polcore* dev, uint8_t* buffer,
        uint8_t percent_power, enum PCON_DIRECTION direction );

/** Shortcut to send a 0 power command to the motor to get it to stop. This is
 * different from braking as there will be no applied voltage.
 */
uint8_t pconGenMotorStop( polcore* dev, uint8_t* buffer );

/** Try and read from the pololu for diagnostic information.
 *
 * Store the result in the given buffer, generally you will only want to use
 * the global return buffer pcon_from_dev...
 */
uint8_t pconGetResponse(polcore* dev, uint8_t* buffer );

/** Send the safe start message to the Pololu
 *
 * This needs to be done really often, especially if feedback from the Pololu
 * isn't working/implemented.
 */
void pconSendSafe( polcore* dev );

/** Performs the bitwise operations needed to check the status of the control
 * bit.
 *
 * Allows only the values declared in the PCON_CONTROL enum type definition. It
 * doesn't matter what the numerical result is, only whether it is zero or a
 * non-zero. In the case of a non-zero you will be able to check it against one
 * of the enumeration codes
 */
uint8_t pconCheckControl( polcore* dev, PCON_CONTROL bit );
void pconSetControl( polcore* dev, PCON_CONTROL bit );
void pconClearControl( polcore* dev, PCON_CONTROL bit );

/** Planned functions
 *
 * Schedule stop time
 * Poll for motor stop conditions
 *
 * Get return information from motor
 */

#endif

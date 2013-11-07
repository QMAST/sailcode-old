#include "cmdline_functions.h"

#define SERVO_MAX_ANGLE 250 // The minimum angle is assumed to be 0

#define RC_MAX_MAGNITUDE 1000 // The minumum output and maximum output are assumed to be the same magnitude, just opposite signs.

int uabout(char* argv[]) {
    // Cool little ascii art made with a program called figlet, gotta
    // escape the special characters though

    // Remember, printf has a 80 char limit at a time
    // This eats a tonne of sram, TODO switch this into a PROGMEM string
    Console->out->printf("  ___|    \\    ____| |     ____| _ \\   _  \\ "
            " ___| ____| \\ \\  / |     \n");
    Console->out->printf(" |       _ \\   __|   |     |    |   | |   | |"
            "     __|    \\  /  |     \n");
    Console->out->printf(" |   |  ___ \\  |     |     __|  |   | __ <  |"
            "     |         \\  |     \n");
    Console->out->printf("\\____|_/    _\\_____|_____|_|   \\___/ _| \\_"
            "\\\\____|_____|  _/\\_\\_____| \n\n\n");

    Console->out->printf("AshCon Version 0.021 \n");

	Console->out->printf("Compiled at __DATE__ __TIME__.\n");

    return 0;
}

int uhelp(char* argv[]) {
}

int urcpollall(char* argv[]) {
    char c = '1';

    while( c != 'q' ) {
        updateControllerValues( radio );
        Console->out->printf("LS: (%d,%d) RS: (%d,%d) SW[%d] AUX[%d]\n",
                getAxisOutput( radio->LSX ),
                getAxisOutput( radio->LSY ),
                getAxisOutput( radio->RSX ),
                getAxisOutput( radio->RSY ),
                getSwitchOutput( radio->gearSwitch ),
                getAxisOutput( radio->AUX )
                    );

        if( Serial.available() ) c = Serial.read();
    }
}

int umotorGo(char* argv[]) {
	char motorId;
	int motorSpeed;
	uint8_t pololuId = 0;
	uint8_t angle = 0;
	polcore *motorDev;
	sscanf(argv[1], "%c", &motorId);
	sscanf(argv[2], "%d", &motorSpeed);

	if (motorId == 'm') {
		motorDev = mast;
	} else if (motorId == 's') {
		motorDev = sail;
	}else if (motorId == 'p') {
		sscanf(argv[2], "%SCNu8", &pololuId);
		sscanf(argv[3], "%SCNu8", &angle);
	} else {
		Console->out->printf("Unknown device.  First param must be \"m\" \
	\"s\", or \"p\".\n");
		return 1;
	}
  
	if (motorDev == mast || motorDev == sail) {
		sscanf(argv[2], "%d", &motorSpeed);
    
		setMotorSpeed(motorDev, motorSpeed);
	}

	if (motorId == 'p') {
		setServoAngle(rudder, pololuId, angle);	
	}

	if (motorDev == mast || motorDev == sail) {
		if (motorDev == mast) {
			Console->out->printf("Mast");	
		} else {
			Console->out->printf("Sail");
		}
		Console->out->printf(" motor ");
		if (motorSpeed != 0) {
			Console->out->printf("speed set to %d%% ", abs(motorSpeed));
			if (motorSpeed > 0) {
				Console->out->printf("forwArds.");
			} else {
				Console->out->printf("backwArds.");
			}
		} else {
			Console->out->printf("turned off.");
		}
	} else {
		Console->out->printf("Pololu pin #%SCNu8 angle set to %SCNu8.", pololuId, angle);
	}

	return 0;
}

int ustartRCControl(char* argv[]) {
	int leftStickX, rightStickX, rudderAngle, sailSpeed, offSwitch;
	char input = 'a';
      
	while (input != 'q') {

        offSwitch = getSwitchOutput(rc->gearSwitch);
        if (offSwitch == 1) {
			Console->out->printf("Emergency Off Switch Activated!\n");    
			break;
        } else if (offSwitch == -2) {
			Console->out->printf("Lost Connection to RC!\n");
			break;
        }

		leftStickX = getBoundedOutput(rc->LSX);
		rightStickX = getBoundedOutput(rc->RSX);

		rudderAngle = (leftStickX / (SERVO_MAX_ANGLE / (2 * RC_MAX_MAGNITUDE)) ) + (SERVO_MAX_ANGLE / 2);
		sailSpeed = abs(rightStickX)>50 ? rightStickX / (RC_MAX_MAGNITUDE/100) : 0;

		setServoAngle(rudder, 7, rudderAngle);
		setMotorSpeed(sail, sailSpeed);

		Console->out->printf( "R:%d\tS:%d\n", rudderAngle, sailSpeed);
        if(Serial.available()) input = Serial.read();
	}

	setMotorSpeed(sail, 0);

	return 0;
	
}

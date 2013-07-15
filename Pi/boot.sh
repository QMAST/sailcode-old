#!/bin/bash
echo "Running startup script."
echo "If you would not like to run the sailbot code, press any key."

read -t 5 -r -n 1 VAR
if [ $? -gt 129 ]; then
	echo "Timeout occured, starting sailcode."
	ls /dev/tty* > /home/pi/devices.txt
	sudo /home/pi/sailcode/Pi/comtest
fi
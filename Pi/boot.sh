#!/bin/bash
echo "Running startup script."
echo "If you would not like to run the sailbot code, press any key."

read -t 5 -r -n 1 VAR
if [$? -gt 129]; then
	echo "Timeout occured, starting sailcode."
	sudo bash /home/pi/sailcode/Pi/main
fi
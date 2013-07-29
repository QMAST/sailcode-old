#When unspecified, compile the main thing.
#Use the g++ compiler
CXX = g++
LIB = lib
SRC = src
CFLAGS = -c -g -std=c++0x -Wall -I$(LIB)

#system stuff to setup properly. 
VPATH = $(SRC):$(LIB)
SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .o .cpp

all: main

main: main.o logging.o arduinoCom.o gpio.o serial.o airmar.o compass.o buffer.o anglesensor.o
	$(CXX) $^ -o $@

testing: testing.o logging.o arduinoCom.o gpio.o serial.o
	$(CXX) $^ -o $@ 

logtest: logtest.o logging.o
	$(CXX) $^ -o $@

comtest: comtest.o arduinoCom.o gpio.o serial.o logging.o
	$(CXX) $^ -o $@

serialtest: serialtest.o arduinoCom.o serial.o gpio.o logging.o
	$(CXX) $^ -o $@

waypointtest: utilities.o waypoint.o waypointtest.o
	$(CXX) $^ -o $@

interrupttest: interrupttest.o arduinoCom.o serial.o gpio.o logging.o
	$(CXX) $^ -o $@

aistest: aistest.o aismessage.o aismanager.o utilities.o buffer.o serial.o logging.o
	$(CXX) $^ -o $@

aistest.o: aisTest.cpp
	$(CXX) $(CFLAGS) $< -o $@

aismessage.o: aisMessage.cpp
	$(CXX) $(CFLAGS) $< -o $@

aismanager.o: aisManager.cpp
	$(CXX) $(CFLAGS) $< -o $@

interrupttest.o: interruptTest.cpp
	$(CXX) $(CFLAGS) $< -o $@

waypointtest.o: waypointTest.cpp
	$(CXX) $(CFLAGS) $< -o $@

serialtest.o: serialTest.cpp
	$(CXX) $(CFLAGS) $< -o $@

anglesensor.o: angleSensor.cpp buffer.h logging.h
	$(CXX) $(CFLAGS) $< -o $@

utilities.o: utilities.cpp utilities.h 
	$(CXX) $(CFLAGS) $< -o $@

compass.o: compass.cpp buffer.h logging.h
	$(CXX) $(CFLAGS) $< -o $@

airmar.o: airmar.cpp buffer.h logging.h
	$(CXX) $(CFLAGS) $< -o $@

buffer.o: buffer.cpp buffer.h
	$(CXX) $(CFLAGS) $< -o $@

comtest.o: comTest.cpp logging.h
	$(CXX) $(CFLAGS) $< -o $@

logtest.o: logTest.cpp logging.h
	$(CXX) $(CFLAGS) $< -o $@

testing.o: testing.cpp logging.h arduinoCom.h
	$(CXX) $(CFLAGS) $< -o $@

main.o: main.cpp logging.h arduinoCom.h
	$(CXX) $(CFLAGS) $< -o $@

arduinoCom.o: arduinoCom.cpp arduinoCom.h gpio.o serial.o
	$(CXX) $(CFLAGS) $< -o $@

gpio.o: gpio.cpp gpio.h logging.o
	$(CXX) $(CFLAGS) $< -o $@

serial.o: serial.cpp serial.h logging.o
	$(CXX) $(CFLAGS) $< -o $@

logging.o: logging.cpp logging.h
	$(CXX) $(CFLAGS) $< -o $@

waypoint.o: waypoint.cpp waypoint.h
	$(CXX) $(CFLAGS) $< -o $@

#Clean up everything.
.PHONY: clean
clean: 
	rm *.o
	rm *.log

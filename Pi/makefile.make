#When unspecified, compile the main thing.
#Use the g++ compiler
CXX = g++
LIB = lib
SRC = src
CFLAGS = -c -I$(LIB)

#system stuff to setup properly. 
VPATH = $(SRC):$(LIB)
SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .o .cpp

all: main

main: main.o logging.o arduinoCom.o
	$(CXX) main.o -o $@

testing: testing.o logging.o arduinoCom.o
	$(CXX) testing.o -o testing 

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

#Clean up everything.
.PHONY: clean
clean: 
	rm *.o temp

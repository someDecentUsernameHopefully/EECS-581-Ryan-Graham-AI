# Define the compiler
CC = g++

# Define any compile-time flags
CFLAGS = -Wall -g

all: main.o IpAddress.o IpDetector.o
	$(CC) $(CFLAGS) -o output main.o IpAddress.o IpDetector.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
	
IpAddress.o: IpAddress.cpp IpAddress.hpp
	$(CC) $(CFLAGS) -c IpAddress.cpp IpAddress.hpp

IpDetector.o: IpDetector.cpp IpDetector.hpp
	$(CC) $(CFLAGS) -c IpDetector.cpp IpDetector.hpp

clean:
	rm *.o
	rm *.gch

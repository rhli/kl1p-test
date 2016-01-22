# the compiler to use
CC=g++

# compiling options
CFLAGS=-c -Wall

all: csTest

csTest: CompressedSensingExample.o main.o
		$(CC) CompressedSensingExample.o main.o -L. -lKLab64 -lpthread -ldl -larmadillo -o csTest

main.o: main.cpp
		$(CC) $(CFLAGS) -I./include main.cpp

CompressedSensingExample.o: CompressedSensingExample.cpp
		$(CC) $(CFLAGS) -I./include CompressedSensingExample.cpp

clean:
		rm *.o
		rm csTest

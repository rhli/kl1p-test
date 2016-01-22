# the compiler to use
CC=g++

# compiling options
CFLAGS=-c -Wall

all: csTest

csTest: main.o
		$(CC) main.o -L. -lKLab64 -lpthread -ldl -larmadillo -o csTest

main.o: main.cpp TestCSAlgorithm.h MatrixIO.h DataProc.h CreatSignal.h 
		$(CC) $(CFLAGS) -I./include main.cpp

clean:
		rm *.o
		rm csTest

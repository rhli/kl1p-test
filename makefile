# The compiler to use g++ or clang++
# CC = g++++
CC = clang++-3.6

# Compiling options
# ---------------------------------------------------------
CFLAGS = -c -Wall

ifeq ($(BUILD), debug)   
# "Debug" build - no optimization, and debugging symbols
CFLAGS += -O0 -g
else
# "Release" build - optimization, and no debug symbols
CFLAGS += -O2 -s -DNDEBUG
endif
# ---------------------------------------------------------

# Compiling rules
all: csTest

csTest: main.o
		$(CC) main.o -L. -lKLab64 -lpthread -ldl -larmadillo -o csTest

main.o: main.cpp TestCSAlgorithm.h MatrixIO.h DataProc.h CreatSignal.h Constants.h
		$(CC) $(CFLAGS) -I./include main.cpp

clean:
		rm *.o
		rm csTest

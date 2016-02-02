# The compiler to use g++ or clang++
CC = clang++

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
all: test

test: test.o
		$(CC) test.o -L. -lKLab64 -lpthread -ldl -larmadillo -o test

test.o: test.cpp TestCSAlgorithm.h MatrixIO.h DataProc.h CreatSignal.h Constants.h
		$(CC) $(CFLAGS) -I./include test.cpp

clean:
		rm *.o
		rm test

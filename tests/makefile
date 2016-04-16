# Compiler
CC = clang++

# Compiling options
CFLAGS = -c -Wall

ifeq ($(BUILD), debug)   
# "Debug" build - no optimization, and debugging symbols
CFLAGS += -O0 -g
else
# "Release" build - optimization, and no debug symbols
CFLAGS += -O2 -s -DNDEBUG
endif

# Compiling header and libs
HEADER = -I../include
LIBB = -L../ -lKLab64 -lKLab64_d 
LIBRA = -lpthread -ldl -larmadillo

# Compiling rules
all: test

test: testCalcSuccess.o
		$(CC) testCalcSuccess.o $(LIBB) $(LIBRA) -o test

testCalcSuccess.o : testCalcSuccess.cpp
		$(CC) $(CFLAGS) $(HEADER) testCalcSuccess.cpp

clean:
		rm *.o
		rm test

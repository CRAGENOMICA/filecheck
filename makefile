# Command lines must start with a '\t' otherwise make shows: "make: *** falta un separador: Alto"
# If Eclipse debug shows: "No source available for main()", then set this to the gcc command: -g -O0
# If make shows "make: Error 1" then be sure that you set the gcc arguments correctly
# If Eclipse says: Errors (1 item)  make: *** [main.o] Error 1. Set Properties > C/C++ Build > [] Generate Makefiles automatically 
# Build directory: ${workspace_loc:/filecheck}/
# And Use Linux GCC Tool Chain!!

all: clean filecheck


# This makefile mixes C++ with C:
# First, it compiles C and it generated *.o files
# Then, it compiles CPP with *.o and it generates the output binary

filecheck:
	gcc *.c -c -Wdiscarded-qualifiers
	g++ *.cpp *.o -lm -o ./bin/filecheck -Wall -g -O0 -lz -std=c++11
	@rm -f *.o

clean:
	@rm -f *.o filecheck

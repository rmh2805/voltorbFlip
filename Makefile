#
#	Commands
#
# Compilers
CC=gcc

# C Flags
CLIBS=-lm -lcurses
CFLAGS=-Wall -std=c99 -Wextra -pedantic -ggdb

# Misc
ECHO=@echo

#
#	Multiple Targets
#

all: voltorbFlip

#
#	Executables
#
voltorbFlip: voltorbFlip.o flipDisp.o
	$(CC) $(CFLAGS) -o voltorbFlip $^ $(CLIBS)
	$(ECHO)

#
#	Object Files
#

voltorbFlip.o: voltorbFlip.c flipDisp.h
	$(CC) $(CFLAGS) -c -o voltorbFlip.o voltorbFlip.c
	
flipDisp.o: flipDisp.c flipDisp.h
	$(CC) $(CFLAGS) -c -o flipDisp.o flipDisp.c

#
#	Utils
# 
clean:
	rm *.o

realclean: clean
	rm voltorbFlip

GIT_VERSION := $(shell git describe --dirty --always --tags)

CC = gcc
LD = gcc

CFLAGS = -Wall -ansi -c -DVERSION=\"$(GIT_VERSION)\"
LFLAGS = -Wall -ansi -o

EXECS = Circuiteer
CIRCUITEEROBJS = Circuiteer.o chipsLoader.o generalFunctions.o menu.o expressionSimplifier.c



all: $(EXECS)

#implicit rule

.c.o:
	$(CC) $(CFLAGS) $<
	
Circuiteer: $(CIRCUITEEROBJS)
	$(LD) $(LFLAGS) $@ $(CIRCUITEEROBJS)
	
clean:
	rm -f *.o $(EXECS)

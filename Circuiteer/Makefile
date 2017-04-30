
CC = gcc
LD = gcc

CFLAGS = -Wall -ansi -c
LFLAGS = -Wall -ansi -o

EXECS = Circuiteer
CIRCUITEEROBJS = chipsLoader.o Circuiteer.o 

#regra implicita

all: $(EXECS)

.c.o:
	$(CC) $(CFLAGS) $<
	
Circuiteer: $(CIRCUITEEROBJS)
	$(LD) $(LFLAGS) $@ $(CIRCUITEEROBJS)
	
clean:
	rm -f *.o $(EXECS)

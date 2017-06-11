#GIT_VERSION := $(shell git describe --dirty --always --tags)

CC = gcc
LD = gcc

CFLAGS = -Wall -ansi -c #-DVERSION=\"$(GIT_VERSION)\"
LFLAGS = -Wall -ansi -o


EXECS = Circuiteer
TEST_EXECS = tests/OrdenateExpressionTerms

CIRCUITEEROBJS = chipsLoader.o generalFunctions.o menu.o expressionSimplifier.o Circuiteer.o

#Tests
ORDENATE_EXPRESSION_TERMS_OBJ = expressionSimplifier.o OrdenateExpressionTerms.o

all: $(TEST_EXECS) $(EXECS)

#run: $(EXECS)

#implicit rule
.c.o:
	$(CC) $(CFLAGS) $<

Circuiteer: $(CIRCUITEEROBJS)
	$(LD) $(LFLAGS) $@ $(CIRCUITEEROBJS)


#Tests
OrdenateExpressionTerms.o:
	$(CC) $(CFLAGS) tests/OrdenateExpressionTerms.c
tests/OrdenateExpressionTerms: $(ORDENATE_EXPRESSION_TERMS_OBJ)
	$(LD) $(LFLAGS) $@ $(ORDENATE_EXPRESSION_TERMS_OBJ)

clean:
	rm -f *.o $(EXECS)

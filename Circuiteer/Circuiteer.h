
#ifndef _CIRCUITEER_
#define _CIRCUITEER_

/* Gates and their correspondent value */
#define AND_INDEX						0
#define OR_INDEX						1

#define NAND_INDEX						2
#define NOR_INDEX						3

#define XOR_INDEX						4
#define XNOR_INDEX						5

#define NOT_INDEX						6
/* - - - - - - - - - - - - - - - - - - */

/* The total number of gates kinds */
#define NUMBER_OF_GATES_KINDS			7

/* - - - - - - - - - - - - - - - - */

/* Max values, to make the size of the array static */
#define MAX_NUMBER_OF_INPUTS_PER_OUTPUT		8
#define MAX_NUMBER_OF_OUTPUTS 				8
#define MAX_NUMBER_CHIPS_PER_GATES			4

#define MAX_CHIP_NAME_SIZE					32
#define MAX_CHIP_DESCRIPTION_SIZE			128

/* - - - - - - - - - - - - - - - - - - - - - - - - -*/

/* Program validation */
#define OK									0

/* - - - - - - - - -*/

/* General macros */
#define EOS									'\0'

/* - - - - - - - -*/

typedef struct
{
	char name[16];
	char description[64];
	unsigned short gateKind; /*see the gates index. eg: AND = 0, NOT = 6. */
	unsigned short inputs;
	unsigned short outputs;
	unsigned short inputsPerOutput;
} ChipType; 

unsigned
readTextFileLine (FILE *pFile, char arrayToReturn[]);

unsigned short
LoadChips (ChipType chipsArrayToReturnToProgram[NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS][MAX_NUMBER_CHIPS_PER_GATES]);

#endif

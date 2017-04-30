#include <stdio.h>
#include <stdlib.h>
#include "Circuiteer.h"


#define OK									0
#define MAX_ENTRY_LENGHT					128

int
main (int argc, char *argv[])
{
	ChipType chipsArray[NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS][MAX_NUMBER_CHIPS_PER_GATES];
	char agroupments[64];
	unsigned short inputs, outputs, numberAgroupments;
	unsigned short validationLoadChips;
	
	validationLoadChips = LoadChips (chipsArray);
	printf("LoadChip Exit Code: %u\n", validationLoadChips);
	
	inputs = scanfUnsigned("Enter the number of inputs ([1, 4]):\n", MAX_ENTRY_LENGHT, 1, 4);
	printf ("%u", inputs);
	return OK;
}

unsigned short
scanfUnsigned (char printfString[], unsigned maxEntryLenght, unsigned minValue, unsigned maxValue)
{
	char *validationStrToUl;
	char stringInput[maxEntryLenght];
	unsigned short value, loopAgain;
	do
	{
		loopAgain = 0;
		printf ("%s", printfString);
		scanf ("%s", stringInput);
		value = (unsigned short) strtoul (stringInput, &validationStrToUl, 10);
		if (*validationStrToUl != EOS || stringInput[0] == '-')
		{
			printf ("\nEnter a non-negative integer.\n");
			loopAgain = 1;
		}
		else if (value < minValue)
		{
			printf ("\nEnter with a number greater than or equal to %u.\n", minValue);
			loopAgain = 1;
		}
		else if (value != 0 && value > maxValue)
		{
			printf ("\nEnter with a number lesser than or equal to %u.\n", maxValue);
			loopAgain = 1;
		}
	}
	while (loopAgain != 0);
	return value;
}

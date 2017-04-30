#include <stdio.h>
#include <stdlib.h>
#include "Circuiteer.h"


#define OK									0


unsigned short counterChipModels = 0;

int
main (int argc, char *argv[]
{
	ChipType chipsArray[NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS][MAX_NUMBER_CHIPS_PER_GATES];
	char agroupments[64];
	unsigned short numberAgroupments;
	unsigned short validationLoadChips;
	
	validationLoadChips = LoadChips (chipsArray);
	if (validationLoadChips != 0)
	{
		printf ("%ubbb\n", validationLoadChips);
	}
	printf("Enter the number of outputs\n");
	return OK;
}

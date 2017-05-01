#include <stdio.h>
#include <stdlib.h>
#include "Circuiteer.h"
#include <string.h>


#define OK									0
#define MAX_ENTRY_LENGHT					128
#define INPUTS_OUTPUTS_MAX_LENGHT_NAME		1
#define MAX_INPUTS							4
#define MAX_OUTPUTS							8
#define MOTD								" - Circuiteer -\nThis program still in development. If found bugs, please contact.\n\n"
int
main (int argc, char *argv[])
{
	ChipType chipsArray[NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS][MAX_NUMBER_CHIPS_PER_GATES];
	unsigned short inputs, outputs, uSCounter, numberAgroupments[MAX_OUTPUTS];
	unsigned short validationLoadChips;
	char agroupments[MAX_OUTPUTS][32];
	char inputsNames[MAX_INPUTS][INPUTS_OUTPUTS_MAX_LENGHT_NAME];
	char outputsNames[MAX_OUTPUTS][INPUTS_OUTPUTS_MAX_LENGHT_NAME];
	char auxString[128];
	
	/* Print the Message of the day */
	printf (MOTD);
	
	/* Load the chips from the .txt file */
	validationLoadChips = LoadChips (chipsArray);
	printf("DEBUG: LoadChip Exit Code: %u\n\n", validationLoadChips);
	
	/* Get the number of inputs */
	sprintf (auxString, "Enter the number of inputs ([1, %u]):\n", MAX_INPUTS);
	inputs = scanfUnsigned(auxString, 1, MAX_INPUTS, MAX_ENTRY_LENGHT);
	printf("\n");
	
	/* Get the letters corresponding to each input */
	for (uSCounter = 0; uSCounter < inputs; uSCounter ++)
	{
		sprintf (auxString, "Enter the corresponding letter to the input number %u:\n", uSCounter);
		inputsNames[uSCounter][0] = scanfChar (auxString, 0, MAX_ENTRY_LENGHT);
	}
	printf("\n");
	
	/* Get the number of outputs */
	sprintf (auxString, "Enter the number of outputs ([1, %u]):\n", MAX_OUTPUTS);
	outputs = scanfUnsigned(auxString, 1, MAX_OUTPUTS, MAX_ENTRY_LENGHT);
	printf("\n");
	
	/* Get the letters corresponding to each output */
	for (uSCounter = 0; uSCounter < outputs; uSCounter ++)
	{
		sprintf (auxString, "Enter the corresponding letter to the output number %u:\n", uSCounter);
		outputsNames[uSCounter][0] = scanfChar (auxString, 0, MAX_ENTRY_LENGHT);
	}
	printf("\n");
	
	/* Get the expression for each output WIP*/
	for (uSCounter = 0; uSCounter < outputs; uSCounter ++)
	{
		sprintf (auxString, "Enter the expression for output %c\n%c = ", outputsNames[uSCounter][0], outputsNames[uSCounter][0]);
		numberAgroupments[0] = readExpression (auxString, agroupments[0], inputsNames[0], inputs, MAX_ENTRY_LENGHT);
	}
	return OK;
}


#include <stdio.h>
#include <stdlib.h>
#include "Circuiteer.h"
#include <string.h>


#define OK									0
#define MAX_ENTRY_LENGHT					128
#define INPUTS_OUTPUTS_MAX_LENGHT_NAME		1
#define MAX_INPUTS							4
#define MAX_OUTPUTS							8

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
	
	validationLoadChips = LoadChips (chipsArray);
	printf("LoadChip Exit Code: %u\n\n", validationLoadChips);
	
	sprintf (auxString, "Enter the number of inputs ([1, %u]):\n", MAX_INPUTS);
	inputs = scanfUnsigned(auxString, 1, MAX_INPUTS, MAX_ENTRY_LENGHT);
	
	printf("\n");
	for (uSCounter = 0; uSCounter < inputs; uSCounter ++)
	{
		sprintf (auxString, "Enter the corresponding letter to the input number %u:\n", uSCounter);
		inputsNames[uSCounter][0] = scanfChar (auxString, 0, MAX_ENTRY_LENGHT);
	}
	
	printf("\n");
	sprintf (auxString, "Enter the number of outputs ([1, %u]):\n", MAX_OUTPUTS);
	outputs = scanfUnsigned(auxString, 1, MAX_OUTPUTS, MAX_ENTRY_LENGHT);
	
	printf("\n");
	for (uSCounter = 0; uSCounter < outputs; uSCounter ++)
	{
		sprintf (auxString, "Enter the corresponding letter to the output number %u:\n", uSCounter);
		outputsNames[uSCounter][0] = scanfChar (auxString, 0, MAX_ENTRY_LENGHT);
	}
	
	printf("\n");
	numberAgroupments[0] = readExpression ("Enter the expression for output X\nX = ", agroupments[0], inputsNames[0], inputs, MAX_ENTRY_LENGHT);

	return OK;
}


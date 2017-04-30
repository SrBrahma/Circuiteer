#include <stdio.h>
#include <stdlib.h>
#include "Circuiteer.h"

#define ERROR_OPENING_FILE					1
#define ERROR_STR_TO_UL						2

#define COMMENTARY_START					'#'

/* Will load the array with the chars, and will return the amount of chars, including the EOS.
 * EX: "abc\0" will return 4 chars */
 
unsigned
ReadTextFileLine (FILE *pFile, char arrayToReturn[])
{
	arrayToReturn[0] = '0';
	unsigned charCounter = 0;
	do
	{
		arrayToReturn[charCounter] = fgetc(pFile);
		charCounter ++;
	}
	while (arrayToReturn[charCounter-1] != '\n' && arrayToReturn[charCounter-1] != EOF && arrayToReturn[charCounter-1] != EOS);
	
	arrayToReturn[charCounter-1] = EOS;
	return charCounter;
}

void
CopyString (char destinationArray[], char sourceArray[], unsigned sizeToCopy)
{
	unsigned counter;
	for (counter = 0; counter < sizeToCopy; counter ++)
		destinationArray[counter] = sourceArray[counter];
}
/* Will load the chips into the given array */
unsigned short
LoadChips (ChipType chipsArrayToReturnToProgram[NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS][MAX_NUMBER_CHIPS_PER_GATES])
{
	unsigned short counterChipModels [NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS];
	ChipType auxChipVar;
	char *stringValidation;
	char myString [MAX_CHIP_DESCRIPTION_SIZE];
	int short controlString = 0;
	unsigned charCounter;

	myString[0] = 0;
	
	FILE *pFile;
	

	pFile = fopen ("./ChipsFamilies/TTL_Chips.txt" , "r");
	
	if (pFile == NULL) return ERROR_OPENING_FILE;
	
	while (feof (pFile) == 0)
	{
		charCounter = ReadTextFileLine (pFile, myString);
		/*printf ("RAW: %s, control = %i\n", myString, controlString);*/
		if (controlString == 0) /* Check if the line is a commentary or empty line */
		{

			if (myString[0] == EOS || myString[0] == COMMENTARY_START)
			{
				controlString = -1;
			}
			else
			{
				controlString = 1;
			}
		}
		
		if (controlString == 1) /* Chip Name */
		{
			CopyString (auxChipVar.name, myString, charCounter);
		}
		
		else if (controlString == 2) /* Chip Description */
		{
			CopyString (auxChipVar.description, myString, charCounter);
		}
		
		else if (controlString == 3) /* Chip kind */
		{
			auxChipVar.gateKind = (unsigned short) strtoul (myString, &stringValidation, 10);
		}
		
		else if (controlString == 4) /* Chip number of inputs */
		{
			auxChipVar.inputs = (unsigned short) strtoul (myString, &stringValidation, 10);
		}
		
		else if (controlString == 5) /* Chip number of outputs */
		{
			auxChipVar.outputs = (unsigned short) strtoul (myString, &stringValidation, 10);
		}
		
		else if (controlString == 6) /* Chip ratio of inputs per output */
		{
			auxChipVar.inputsPerOutput = (unsigned short) strtoul (myString, &stringValidation, 10);
			controlString = -1; /* Restart the counter/control */
			printf ("Name: %s\n", auxChipVar.name);
			printf ("Description: %s\n", auxChipVar.description);
			printf ("Gate: %u\n", auxChipVar.gateKind);
			printf ("Inputs: %u\n", auxChipVar.inputs);
			printf ("Outputs: %u\n", auxChipVar.outputs);
			printf ("InputsPerOutputs: %u\n\n", auxChipVar.inputsPerOutput);
		}
		
		if (controlString > 2 && *stringValidation != EOS)
		{
			printf ("Error at stringValidation =: (%c)\n", *stringValidation);
			return ERROR_STR_TO_UL;
		}
		
		controlString += 1;
	} 									/* END OF WHILE LOOP */
	fclose (pFile);
	return 0;
}



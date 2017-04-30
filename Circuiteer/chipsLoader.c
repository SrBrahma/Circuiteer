#include <stdio.h>
#include "Circuiteer.h"

#define ERROR_OPENING_FILE					1
#define ERROR_STR_TO_UL						2

#define STRING_SIZE					128
#define COMMENTARY_START			'#'

/*will load the chips into the given array*/

unsigned short
LoadChips (ChipType chipsArrayToReturnToProgram[NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS][MAX_NUMBER_CHIPS_PER_GATES])
{
	unsigned short counterChipModels[NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS];
	ChipType auxChipVar;
	char myString [STRING_SIZE];
	int short controlString = 0;


	FILE *pFile;
	

	pFile = fopen ("./ChipsFamilies/TTL_Chips.txt" , "r");
	
	if (pFile == NULL) return ERROR_OPENING_FILE;
	
	while (fgets (myString, STRING_SIZE, pFile) != NULL)
	{
		if (controlString == 0) /* Check if the line is a commentary or empty line */
		{
			while (myString[0] == COMMENTARY_START || myString[0] == EOS) /* Read the file until commentary/empty line ends */
			{
				fgets (myString, STRING_SIZE, pFile);
			}
			controlString = 1;
		}
		
		if (controlString == 1) /* Chip Name */
		{
			memcpy(auxChipVar.name, myString, strlen(STRING_SIZE
			printf ("%s\n", myString);
		}
		
		else if (controlString == 2) /* Chip Description */
		{
			auxChipVar.description = myString;
			printf ("%s\n", myString);
		}
		
		else if (controlString == 3) /* Chip kind */
		{
			auxChipVar.gateKind = (unsigned short) strtoul (myString, *stringValidation, 10);
			printf ("%s\n", myString);
		}
		
		else if (controlString == 4) /* Chip number of inputs */
		{
			auxChipVar.inputs = (unsigned short) strtoul (myString, *stringValidation, 10);
			printf ("%s\n", myString);
		}
		
		else if (controlString == 5) /* Chip number of outputs */
		{
			auxChipVar.outputs = (unsigned short) strtoul (myString, *stringValidation, 10);
			printf ("%s\n", myString);
		}
		
		else if (controlString == 6) /* Chip ratio of inputs per output */
		{
			auxChipVar.inputsPerOutput = (unsigned short) strtoul (myString, *stringValidation, 10);
			printf ("%s\n", myString);
			controlString = 0; /*restart the counter/control */
		}
	
		controlString += 1;
		
		if (stringValidation != EOS) {
			return ERROR_STR_TO_UL;
		}
	} /* END OF WHILE LOOP */
	fclose (pFile);
	return 0;
}



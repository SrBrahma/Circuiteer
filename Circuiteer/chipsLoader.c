#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Circuiteer.h"

#define ERROR_OPENING_FILE                  1
#define ERROR_STR_TO_UL                     2

#define COMMENTARY_START                    '#'

/* Will load the chips into the given array */
unsigned short
LoadChips (ChipType chipsArrayToReturnToProgram[NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS][MAX_NUMBER_CHIPS_PER_GATES])
{
    unsigned short counterChipModels [NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS];
    ChipType auxChipVar;
    char *stringValidation;
    char textLineString [MAX_CHIP_DESCRIPTION_SIZE];
    int short controlString = 0;
    unsigned charCounter;
    FILE *pFile;
    

    pFile = fopen ("./ChipsFamilies/TTL_Chips.txt" , "r");
    
    if (pFile == NULL) return ERROR_OPENING_FILE;
    
    while (fgets (textLineString, MAX_ENTRY_LENGHT, pFile)) /* Read the lines until fgets returns NULL, aka EOF */
    {
        CheckLenghtRemoveEndSpacesNewLineToEOS (textLineString, MAX_ENTRY_LENGHT); /* String treatment */
        charCounter = strlen (textLineString);
        
        /*printf ("RAW: %s, control = %i\n", textLineString, controlString);*/
        if (controlString == 0) /* Check if the line is a commentary or empty line */
        {

            if (textLineString[0] == EOS || textLineString[0] == COMMENTARY_START) /* If the line IS a commentary/blank line */
            {
                controlString = -1;
            }
            else /* If the line ISN'T a commentary/blank line */
            {
                controlString = 1;
            }
        }
        
        if (controlString == 1) /* Chip Name */
        {
			strcpy (auxChipVar.name, textLineString);
        }
        
        else if (controlString == 2) /* Chip Description */
        {
			strcpy (auxChipVar.description, textLineString);
        }
        
        else if (controlString == 3) /* Chip kind */
        {
            auxChipVar.gateKind = (unsigned short) strtoul (textLineString, &stringValidation, 10);
        }
        
        else if (controlString == 4) /* Chip number of inputs */
        {
            auxChipVar.inputs = (unsigned short) strtoul (textLineString, &stringValidation, 10);
        }
        
        else if (controlString == 5) /* Chip number of outputs */
        {
            auxChipVar.outputs = (unsigned short) strtoul (textLineString, &stringValidation, 10);
        }
        
        else if (controlString == 6) /* Chip ratio of inputs per output */
        {
            auxChipVar.inputsPerOutput = (unsigned short) strtoul (textLineString, &stringValidation, 10);
            controlString = -1; /* Restart the counter/control */
            /* DEBUG
            printf ("Name: %s\n", auxChipVar.name);
            printf ("Description: %s\n", auxChipVar.description);
            printf ("Gate: %u\n", auxChipVar.gateKind);
            printf ("Inputs: %u\n", auxChipVar.inputs);
            printf ("Outputs: %u\n", auxChipVar.outputs);
            printf ("InputsPerOutputs: %u\n\n", auxChipVar.inputsPerOutput);
            */
            
        }
        
        if (controlString > 2 && *stringValidation != EOS)
        {
            printf ("Error at stringValidation =: (%c)\n", *stringValidation);
            return ERROR_STR_TO_UL;
        }
         
        controlString += 1;
    }                                   /* END OF WHILE LOOP */
    fclose (pFile);
    return OK;
}



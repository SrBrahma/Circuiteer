/* This file contains useful functions */

#include <stdio.h>
#include <stdlib.h>
#include "Circuiteer.h"

void
CopyString (char destinationArray[], char sourceArray[], unsigned sizeToCopy)
{
	unsigned counter;
	for (counter = 0; counter < sizeToCopy; counter ++)
		destinationArray[counter] = sourceArray[counter];
}

char
scanfChar (char printfString[], unsigned short allowSpecialChars, unsigned maxEntryLenght)
{
	char stringInput[maxEntryLenght];
	unsigned short loopAgain;
	do
	{
		loopAgain = 0;
		printf ("%s", printfString);
		scanf ("%s", stringInput);
		if (stringInput[1] != EOS)
		{
			printf ("\nEnter only a single char.\n");
			loopAgain = 1;
		}
		else if (allowSpecialChars == 0)
		{
			if (stringInput[0] < 'A' || (stringInput[0] > 'Z' && stringInput[0] < 'a') || stringInput[0] > 'z')
			{
				printf ("\nNo special characters allowed. Enter only a letter.\n");
				loopAgain = 1;
			}
		}
	}
	while (loopAgain != 0);
	return stringInput[0];
}


unsigned short
scanfUnsigned (char printfString[], unsigned minValue, unsigned maxValue, unsigned maxEntryLenght)
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
		else if (maxValue != 0 && value > maxValue)
		{
			printf ("\nEnter with a number lesser than or equal to %u.\n", maxValue);
			loopAgain = 1;
		}
	}
	while (loopAgain != 0);
	return value;
}


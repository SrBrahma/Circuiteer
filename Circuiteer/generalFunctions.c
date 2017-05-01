/* This file contains useful functions */

#include <stdio.h>
#include <stdlib.h>
#include "Circuiteer.h"

#define EXPRESSION_DEFAULT_CHARS " ()'¬+"

unsigned short
readExpression (char agroupmentsReturn[], char inputsNames[], unsigned short numberOfInputs, unsigned maxEntryLenght)
{
	unsigned short numberOfAgroupments = 0;
	unsigned short numberOpenParenthesis = 0, numberCloseParenthesis = 0;
	unsigned short invalidExpression;
	unsigned short counter;
	unsigned short stringLenght;

	unsigned short lenExpressionDefaultChars = strlen (EXPRESSION_DEFAULT_CHARS);
	char stringInput [maxEntryLenght];
	
	char validChars [lenExpressionDefaultChars + numberOfInputs + 1]; /* +1 for EOS */
	
	/* Add the values of the macro expression default chars to the var validChars */
	for (counter = 0; counter < lenExpressionDefaultChars); counter ++)
		validChars [counter] = EXPRESSION_DEFAULT_CHARS [counter];
	
	/* Add to the same var, the expression inputs letters */
	for (; counter < lenExpressionDefaultChars + numberOfInputs; counter ++)
		validChars [counter] = inputNames [counter - lenExpressionDefaultChars];
		
	
	do
	{
		scanf ("%s", stringInput);
		/* First look for garbage */
		for (counter = 0; counter < stringLenght; counter ++);
		{
		if stringInput[positionStr]
	}
	}
	while (invalidExpression != 0);
	
	return numberOfAgroupments;
}
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


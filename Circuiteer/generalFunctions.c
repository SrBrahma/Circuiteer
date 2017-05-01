/* This file contains useful functions */

#include <stdio.h>
#include <stdlib.h>
#include "Circuiteer.h"
#include <string.h>

#define EXPRESSION_DEFAULT_CHARS " ()'¬+"

unsigned short
readExpression (char printfString[], char agroupmentsReturn[], char inputsNames[], unsigned short numberOfInputs, unsigned maxEntryLenght)
{
	unsigned short numberOfAgroupments = 0;
	unsigned short numberOpenParenthesis, numberCloseParenthesis;
	unsigned short foundInvalidChar, invalidExpression;
	unsigned short counter, counter2;
	unsigned short stringLenght;

	unsigned short lenExpressionDefaultChars = strlen (EXPRESSION_DEFAULT_CHARS);
	char stringInput [maxEntryLenght];
	
	char validChars [lenExpressionDefaultChars + numberOfInputs + 1]; /* +1 for EOS */
	
	/* Add the values of the macro expression default chars to the var validChars */
	for (counter = 0; counter < lenExpressionDefaultChars; counter ++)
		validChars [counter] = EXPRESSION_DEFAULT_CHARS [counter];
	
	/* Add to the same var, the expression inputs letters */
	for (; counter < lenExpressionDefaultChars + numberOfInputs; counter ++)
		validChars [counter] = inputsNames [counter - lenExpressionDefaultChars];
	
	validChars [counter] = EOS;
	
	do
	{
		numberOpenParenthesis = 0;
		numberCloseParenthesis = 0;
		invalidExpression = 0;
		printf ("%s", printfString);
		scanf ("%s", stringInput);
		stringLenght = strlen(stringInput);
		
		/* First look for garbage (chars that are not allowed) */
		for (counter = 0; (counter < stringLenght && invalidExpression == 0); counter ++)
		{
			foundInvalidChar = 1;
			for (counter2 = 0; (counter2 < lenExpressionDefaultChars + numberOfInputs && foundInvalidChar != 0); counter2 ++)
			{
				if (stringInput[counter] == validChars [counter2])
					foundInvalidChar = 0;
			}
			if (foundInvalidChar == 1)
			{
				printf ("Invalid character found (%c) on position %u of the string.\n", stringInput[counter], counter);
				invalidExpression = 1;
			}
		}
		/* - - - */
		/* Now look for invalid parenthesis */
		for (counter = 0; (counter < stringLenght && invalidExpression == 0); counter ++)
		{
			if (stringInput[counter] == '(')
				numberOpenParenthesis ++;
			else if (stringInput[counter] == ')')
			{
				numberCloseParenthesis ++;
				if (numberCloseParenthesis > numberOpenParenthesis)
				{
					printf ("Invalid parenthesis \')\' found on position %u of the string.\n", counter);
					invalidExpression = 1;
				}
			}
		}
		if (numberOpenParenthesis != numberCloseParenthesis && invalidExpression == 0)
		{
			printf ("Unclosed parenthesis found.\n");
			invalidExpression = 1;
		}
		/* - - - */
		/* Next, deal with ' and + */
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


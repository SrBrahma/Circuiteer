/* This file contains useful functions.
 * fgets:
 * "You put in 'apple'.
 * Internally your string was stored as 'apple\n\0'.
 *strlen then returned 6 for 'apple' + '\n'
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Circuiteer.h"

#define EXPRESSION_DEFAULT_CHARS            " ()'¬+*\0"
#define INVALID_LAST_CHARS_FOR_AFTER_NOT    " (+*"          /* For ' not char. This can't happen +' */




void
ReadExpression (const char printfString[], char rawExpression[], char inputLetter[], unsigned short numberOfInputs, unsigned maxEntryLenght)
{
        /* Text Input */
    unsigned short rawExpressionLenght;
        /* Valid Chars */
    unsigned short validCharsLenght = strlen (EXPRESSION_DEFAULT_CHARS) + numberOfInputs; /* This var is used later */
    char validChars [validCharsLenght];
        /* Error treatment */
    unsigned short counter, counter2;
    unsigned short lastOperatorPosition;
    unsigned short foundOperandBefore, foundOperandAfter, foundOperator;
    unsigned short numberOpenParenthesis, numberCloseParenthesis;
        /* Errors */
    unsigned short foundInvalidChar, invalidInput;
    
    /* Load the valid chars variable */
    strcpy (validChars, EXPRESSION_DEFAULT_CHARS);
    strcat (validChars, inputLetter);
    
    /* Main Loop to get the expression*/
    do
    {
        numberOpenParenthesis = numberCloseParenthesis = 0;
        foundOperandBefore = foundOperandAfter = foundOperator = 0;
        invalidInput = 0;
        
        printf ("%s", printfString);
        
        fgets (rawExpression, maxEntryLenght, stdin);
        rawExpressionLenght = CheckLenghtRemoveEndSpacesNewLineToEOS (rawExpression, maxEntryLenght);
        if (rawExpressionLenght == -1)
        {
            printf ("\nThe input exceeds the maximum lenght allowed (%u).\n", maxEntryLenght);
            invalidInput = 1;
        }       
        
        
        if (rawExpressionLenght == 0)
        {
            printf ("\nThe input must contain at least one char.\n");
            invalidInput = 1;
        }
        
    /* First look for garbage (chars that are not allowed) */
        for (counter = 0; (counter < rawExpressionLenght && invalidInput == 0); counter ++)
        {
            foundInvalidChar = 1;
            for (counter2 = 0; (counter2 < validCharsLenght && foundInvalidChar != 0); counter2 ++)
            {
                if (rawExpression[counter] == validChars [counter2])
                    foundInvalidChar = 0;
            }
            if (foundInvalidChar == 1)
            {
                printf ("\nInvalid character \"%c\" on position %u of the string.\n", rawExpression[counter], counter);
                invalidInput = 1;
            }
        }
        
    /* Now look for invalid parenthesis and invalid operators*/
        for (counter = 0; (counter < rawExpressionLenght && invalidInput == 0); counter ++)
        {
                /* Look for operands */
            for (counter2 = 0; counter2 < numberOfInputs; counter2 ++)
            {
                if (rawExpression[counter] == inputLetter[counter2] || rawExpression[counter] == '(' || rawExpression[counter] == ')')
                {
                    if (foundOperandBefore == 0)
                        foundOperandBefore = 1;
                    else if (foundOperandBefore == 1 && foundOperator == 1)
                    {
                        foundOperator = 0;
                    }
                }
            }
            
                /* Look for operators */
            if (rawExpression[counter] == '+' || rawExpression[counter] == '*')
            {
                if (foundOperandBefore == 0 || foundOperator == 1)
                {
                    printf ("\nInvalid operator \"%c\" on position %u of the string.\n", rawExpression[counter], counter);
                    invalidInput = 1;
                }
                else
                {
                    foundOperator = 1;
                    lastOperatorPosition = counter;
                }
            }
				/* Look for NOT ', ex: A' */
            else if (rawExpression[counter] == '\'')
            {
                if (counter == 0)
                {
                    printf ("\nInvalid negation (\') on position %u of the string.\n", counter);
                    invalidInput = 1;
                }
                else
                {
                    for (counter2 = 0; counter2 < strlen (INVALID_LAST_CHARS_FOR_AFTER_NOT); counter2 ++)
                    {
                        if (rawExpression[counter-1] == INVALID_LAST_CHARS_FOR_AFTER_NOT[counter2])
                        {
                            printf ("\nInvalid negation (\') on position %u of the string.\n", counter);
                            invalidInput = 1;
                        }
                    }
                }
            }
                /* Look for parenthesis */
            else if (rawExpression[counter] == '(')
            {
                numberOpenParenthesis ++;
                foundOperandBefore = 0; /* To avoid stuff like A (+ B) */
            }
            else if (rawExpression[counter] == ')')
            {
                numberCloseParenthesis ++;
                foundOperandAfter = 0; /* To avoid stuff like A (B +) */

                if (numberCloseParenthesis > numberOpenParenthesis)
                {
                    printf ("\nInvalid parenthesis \")\" on position %u of the string.\n", counter);
                    invalidInput = 1;
                }
            }
        } /* End of parenthesis and operators for */
        if (numberOpenParenthesis != numberCloseParenthesis && invalidInput == 0)
        {
            printf ("\nUnclosed parenthesis found.\n");
            invalidInput = 1;
        }
        
        /* If there is a operator unused on the end */
        else if (foundOperator == 1 && invalidInput == 0)
        {
            printf ("\nInvalid operator \"%c\" on the position %u of the string.\n", rawExpression[lastOperatorPosition], lastOperatorPosition);
            invalidInput = 1;
        }
    }
    while (invalidInput != 0);   /* End of Main Loop */
} /* End of getExpression function */

unsigned short
ExpressionToAgroupments (const char originalExpression[],  char newExpression[],
                         char agroupmentsReturn[MAX_AGROUPMENTS][MAX_AGROUPMENT_LENGHT], unsigned maxStringLenght)
{
    unsigned short numberAgroupments = 0;
    unsigned short counter, counter2 = 0;
    unsigned short originalStringLenght = strlen (originalExpression);
    
    
    /* Copy the old string to the new string, but without the spaces */
    for (counter = 0; counter <= originalStringLenght; counter ++)
        if (originalExpression[counter] != ' ')
        {
            newExpression[counter2] = originalExpression[counter];
            counter2 ++;
        }
    printf ("New expression is: %s\n", newExpression);
    return numberAgroupments;
}
char
FgetsChar (char printfString[], unsigned short allowNotLettersChars, unsigned maxEntryLenght)
{
    char stringInput[maxEntryLenght];
    unsigned short invalidInput;
    do
    {
        invalidInput = 0;
        printf ("%s", printfString);
        
        fgets (stringInput, maxEntryLenght, stdin);
        if (CheckLenghtRemoveEndSpacesNewLineToEOS (stringInput, maxEntryLenght) == -1)
        {
            printf ("\nThe input exceeds the maximum lenght allowed (%u)\n", maxEntryLenght);
            invalidInput = 1;
        }       
        else if (stringInput[0] == EOS)
        {
            printf ("\nThe input must contain a char.\n");
            invalidInput = 1;   
        }
        else if (stringInput[1] != EOS)
        {
            printf ("\nEnter only a single char.\n");
            invalidInput = 1;
        }
        else if (allowNotLettersChars == 0)
        {
            if (stringInput[0] < 'A' || (stringInput[0] > 'Z' && stringInput[0] < 'a') || stringInput[0] > 'z')
            {
                printf ("\nNo special characters allowed. Enter only a letter.\n");
                invalidInput = 1;
            }
        }
    }
    while (invalidInput != 0);
    return stringInput[0];
}


unsigned short
FgetsUnsigned (char printfString[], unsigned minValue, unsigned maxValue, unsigned maxEntryLenght)
{
    char *validationStrToUl;

    char stringInput[maxEntryLenght];
    unsigned short value, invalidInput;
    do
    {
        invalidInput = 0;
        printf ("%s", printfString);
        
        fgets (stringInput, maxEntryLenght, stdin);
        if (CheckLenghtRemoveEndSpacesNewLineToEOS (stringInput, maxEntryLenght) == -1)
        {
            printf ("\nThe input exceeds the maximum lenght allowed (%u)\n", maxEntryLenght);
            invalidInput = 1;
        }
        else if (stringInput[0] == EOS)
        {
            printf ("\nThe input must contain a number.\n");
            invalidInput = 1;   
        }
        else
        {
            value = (unsigned short) strtoul (stringInput, &validationStrToUl, 10);
            if ((*validationStrToUl != EOS || stringInput[0] == '-') && invalidInput == 0)
            {
                printf ("\nEnter a non-negative integer.\n");
                invalidInput = 1;
            }
            else if (value < minValue)
            {
                printf ("\nEnter with a number greater than or equal to %u.\n", minValue);
                invalidInput = 1;
            }
            else if (maxValue != 0 && value > maxValue)
            {
                printf ("\nEnter with a number lesser than or equal to %u.\n", maxValue);
                invalidInput = 1;
            }
        }
    }
    while (invalidInput != 0);
    return value;
}

/* Will return string lenght, but if the string has no end, will return -1. */
int
CheckLenghtRemoveEndSpacesNewLineToEOS (char stringVar[], unsigned maxEntryLenght)
{
    unsigned short foundNewLineChar = 0, foundEOSChar = 0;
    short int lastValidCharPosition = -1; /* So if the first char is \n, the "stringVar [lastValidCharPosition + 1] = EOS;" will still work. */
    unsigned counter;
    
    /* This "for" must be incremental, as if it was decremental it could find false-positive garbage */ 
    for (counter = 0; (counter < maxEntryLenght && foundNewLineChar == 0 && foundEOSChar == 0); counter ++)
    {
        if (stringVar [counter] == '\n')
            foundNewLineChar = 1;
            
        else if (stringVar [counter] == EOS)
            foundEOSChar = 1;   
            
        else if (stringVar [counter] != ' ')
            lastValidCharPosition = counter;
    }
    
    /* If no newLine char found, the user filled the entire string buffer, so, return ERROR */
    if (foundNewLineChar == 0 && foundEOSChar == 0)
        return ERROR_EXCEEDS_MAX_STRING_LENGHT;
    
    /* Remove the useless spaces at the end of the string */
    stringVar [lastValidCharPosition + 1] = EOS;
        
    return (lastValidCharPosition + 1);
}
    

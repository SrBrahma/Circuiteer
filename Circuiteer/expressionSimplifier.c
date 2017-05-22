#include <string.h>
#include <stdio.h>
#include "Circuiteer.h"

unsigned short
RawExpressionToMinterms (const char oldExpression[],  char newExpression[],
                         char agroupmentsReturn[MAX_AGROUPMENTS][MAX_AGROUPMENT_LENGHT], unsigned maxExpressionLenght)
{
    char auxExpression[maxExpressionLenght];
    unsigned short numberAgroupments = 0;
    unsigned short counter, counter2 = 0;
    unsigned short openParenthesisBeforeClosePos, firstCloseParenthesisPos;
    char *pointerFirstCloseParenthesis;
    byte finishedDealingParenthesis = 0;
    byte removeParentheses;
    unsigned short oldStringLenght = strlen (oldExpression);
    
    
    /* Copy the old string to the new string, but without the spaces */
    for (counter = 0; counter <= oldStringLenght; counter ++)
        if (oldExpression[counter] != ' ' && oldExpression[counter] != '*')
        {
            newExpression[counter2] = oldExpression[counter];
            counter2 ++;
        }
        
    /* Now look parenthesis and treat to remove them */
    while (!finishedDealingParenthesis)
    {
        removeParentheses = 0;
        
        pointerFirstCloseParenthesis = strchr (newExpression, ')');
        if (pointerFirstCloseParenthesis == NULL)
        {
            finishedDealingParenthesis = 1;
        }
        else
        {
            firstCloseParenthesisPos = strchr (newExpression, ')') - newExpression;
            printf (") pos = %u\n", firstCloseParenthesisPos);
            
            for (counter = firstCloseParenthesisPos; newExpression[counter-1] != '('; counter --);
            openParenthesisBeforeClosePos = counter - 1;
            printf ("( pos = %u\n", openParenthesisBeforeClosePos);
            
            if (newExpression[firstCloseParenthesisPos+1] == '\'')
            {
                /* De morgan */
            }
            
            
            /* If the openParenthesis is on the position 0 and there is a sum on the right (or EOS on right) */
            else if (openParenthesisBeforeClosePos == 0 && (newExpression[firstCloseParenthesisPos + 1] == '+'
                                                        || newExpression[firstCloseParenthesisPos + 1] == ')'
                                                        || newExpression[firstCloseParenthesisPos + 1] == EOS))
                    removeParentheses = 1;
            /* If there are sums on both sides (or EOS on right) */
            else if (openParenthesisBeforeClosePos > 0)
            {
                if ((newExpression[openParenthesisBeforeClosePos - 1] == '+' 
                || newExpression[openParenthesisBeforeClosePos - 1] == '(') && (newExpression[firstCloseParenthesisPos + 1] == '+'
                                                                            || newExpression[firstCloseParenthesisPos + 1] == ')'
                                                                            || newExpression[firstCloseParenthesisPos + 1] == EOS))
                    removeParentheses = 1;
            }
            
            /* If none of above, must have a multiplication on some side (or both) */
            else
            {
                /* if (openParenthesisBeforeClosePos == 0 || ) */
            }
            
            
            /* Remove Parentheses */
            if (removeParentheses == 1)
            {
                sprintf (auxExpression, "%.*s%.*s%s", openParenthesisBeforeClosePos, newExpression,
                                                      firstCloseParenthesisPos - openParenthesisBeforeClosePos - 1, newExpression + openParenthesisBeforeClosePos + 1,
                                                      pointerFirstCloseParenthesis + 1);
                memcpy (newExpression, auxExpression, maxExpressionLenght);
            }
            
        } /* End of ELSE */
        
    } /* End of WHILE */

    printf ("New expression is: %s\n", newExpression);
    return numberAgroupments;
}


byte
KarnaughRowPos (byte originalRow, short int additionalRowValue, byte karnaughHeight)
{
    short int result;
    
    result = originalRow + additionalRowValue;
    if (result < 0)
        result = karnaughHeight - 1 - result;
    else if (result >= karnaughHeight)
        result -= karnaughHeight;
        
    return ((byte) result);
}

byte
KarnaughColumnPos (byte originalColumn, short int additionalColumnValue, byte karnaughWidth)
{
    short int result;
    
    result = originalColumn + additionalColumnValue;
    if (result < 0)
        result = karnaughWidth - 1 - result;
    else if (result >= karnaughWidth)
        result -= karnaughWidth;
        
    return ((byte) result);
}


void
ApplyKarnaugh (const char sourceExpression[], unsigned short sourceExpressionLenght, char newExpression [], byte getNegated, unsigned maxEntryLenght)
{
    /* NOTE: Will only accept minterms not negated and without parentheses ( (A+B)' are not accepted now) */
    /* Will simplify AA to A, AA' to 0, A+A' to 1. */
    
    byte numberOfInputs = 0;
    char inputLetter[MAX_INPUTS];
    unsigned short counter, counter2;
    
    byte ignoreCharsLenght = 2;
    const char ignoreChars[2] = {"'+"};
    
    byte foundOperand;
    char thisMintermExpression[maxEntryLenght];
    
    byte karnaughWidth, karnaughHeight;
    karnaughMapCell *karnaughZeroZeroPosition;
    byte arrayKarnaugh[4][4] = {0};
    
    short int rowCounter, columnCounter;
    
    byte karnaughOnValue = 1;
    byte karnaughOffValue = 0;
    
    /* Check the entire expression inputs */
    /* First get the number of inputs and its corresponding letters */
    for (counter = 0; counter < sourceExpressionLenght; counter ++)
    {
        foundOperand = 1; /* Initial value */
        
        /* Check if the char is an operand or not */
        for (counter2 = 0; counter2 < ignoreCharsLenght; counter2 ++)
            if (sourceExpression[counter] == ignoreChars[counter2])
                foundOperand = 0;
                
        if (foundOperand) 
        {
            /* Check if this input is already added */
            for (counter2 = 0; counter2 < numberOfInputs; counter2 ++)
                if (sourceExpression[counter] == inputLetter[counter2])
                    foundOperand = 0;
        
            /* If the input wasn't already added, add it */
            if (foundOperand)
            {
                inputLetter[numberOfInputs] = sourceExpression[counter];
                numberOfInputs ++;
            }
        }
    }
    
    /* Check the minterm */
    if (numberOfInputs == 1)
    {
        karnaughWidth = 2;
        karnaughHeight = 1;
    }
    if (numberOfInputs == 2)
    {
        karnaughWidth = karnaughHeight = 2;
    }
    if (numberOfInputs == 3)
    {
        karnaughWidth = 2;
        karnaughHeight = 4;
    }
    if (numberOfInputs == 4)
    {
        karnaughWidth = karnaughHeight = 4;
    }
    
    /* Put the expression into the map */
    for (counter = 0; sourceExpression[counter] != EOS; counter++)
    {
        
    
    /* DO THE KARNAUGH */
    /* Test if all cells are ON, if yes, expression output will be 1.*/
    }
    
    for (rowCounter = 0; rowCounter < karnaughHeight; rowCounter ++)
    {
        for (columnCounter = 0; columnCounter < karnaughWidth; columnCounter ++)
        {
            if (arrayKarnaugh[rowCounter][columnCounter] == karnaughOffValue)
            {
                /* If the cell of the right have OnValue */
                if (arrayKarnaugh[rowCounter][KarnaughColumnPos (columnCounter, 1, karnaughWidth)] == karnaughOnValue)
                {
                }
                /* If the cell of the top have OnValue */
                if (arrayKarnaugh[KarnaughRowPos (rowCounter, -1, karnaughHeight)][columnCounter] == karnaughOnValue)
                {
                }
                /* If the cell of the left have OnValue */
                if (arrayKarnaugh[rowCounter][KarnaughColumnPos (columnCounter, -1, karnaughWidth)] == karnaughOnValue)
                {
                }
                /* If the cell of the bottom have OnValue */
                if (arrayKarnaugh[KarnaughRowPos (rowCounter, 1, karnaughHeight)][columnCounter] == karnaughOnValue)
                {
                }
            }
        }
    }
    
    /*DEBUG*/
    printf ("Number of differents inputs = %u; ", numberOfInputs);
    for (counter = 0; counter < numberOfInputs; counter ++)
        printf ("%c", inputLetter[counter]);
    printf("\n");
    
}



/* This function will transform "AAABB'B'CCD" into ABB'CD. 
 * originalMinterm must end with EOS. The newMinterm return will also include a EOS.
 * If checkControversialTerms == true, "AAAA'BBBCD", newMinterm will output "0", as A AND A' will never output 1. */
void
RemoveRepeatingTermInMinterm (const char originalMinterm[], char newMinterm[], boolean checkControversialTerms)
{
    unsigned short counter = 0, counter2;
    unsigned short lenghtOriginalMinterm = strlen (originalMinterm);
    char termsString[MAX_INPUTS+1] = "", negatedTermsString[(MAX_INPUTS*2)+1] = ""; /* negatedTermsString includes '\'' after each letter. */
    boolean thisLetterIsNegated;
    
    /* Get the termsString */
    while(originalMinterm[counter] != EOS)
    {
        thisLetterIsNegated = false;
        /* Check if is negated, and if the char isn't already added. If not, add it. */
        if (counter + 1 < lenghtOriginalMinterm)
        {
            if (originalMinterm[counter+1] == '\'')
            {
                if (!strchr(negatedTermsString, originalMinterm[counter])) /* Not merged with previous if to don't mess next else */
                {
                    sprintf (negatedTermsString, "%s%c%c", negatedTermsString, originalMinterm[counter], '\'');
                }
                counter ++;
                thisLetterIsNegated = true;
            }
        }
        
        /* If not negated, check if the char isn't already added. If not, add it. */
        if (!thisLetterIsNegated && !strchr(termsString, originalMinterm[counter]))
        {
            sprintf (termsString, "%s%c", termsString, originalMinterm[counter]);
        }
        if (checkControversialTerms)
            for (counter2 = 0; counter2 < strlen (termsString); counter2++)
                if (strchr (negatedTermsString, termsString[counter2]))
                {
                    sprintf (newMinterm, "0");
                    return;
                }
        counter ++;
        
    }
    
    sprintf (newMinterm, "%s%s", termsString, negatedTermsString);
    return;
}

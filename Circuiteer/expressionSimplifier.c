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
KarnaughTwoInputsToExpression (byte position, char letter1, char letter2, char expressionReturn[])
{
    if (position == 0)
    {
        sprintf (expressionReturn, "%c'%c'+", letter1, letter2);
        return;
    }
    if (position == 1)
    {
        sprintf (expressionReturn, "%c'%c+", letter1, letter2);
        return;
    }
    if (position == 2)
    {
        sprintf (expressionReturn, "%c%c+", letter1, letter2);
        return;
    }
    /* implicit: if (position == 3) */
    sprintf (expressionReturn, "%c%c'+", letter1, letter2);
    return;
}

void
KarnaughOneInputToExpression (byte position, boolean goingDownOrRight, char letter1, char letter2, char expressionReturn[])
{
    if (goingDownOrRight)
    {
        if (position == 0)
        {
            sprintf (expressionReturn, "%c'+", letter1);
            return;
        }
        else if (position == 1)
        {
            sprintf (expressionReturn, "%c+", letter2);
            return;
        }
        else if (position == 2)
        {
            sprintf (expressionReturn, "%c+", letter1);
            return;
        /* implicit: if (position == 3) */
        sprintf (expressionReturn, "%c'+", letter2);
        return;
    }
    else /* If going Up or Left */
    {
        if (position == 0)
        {
            sprintf (expressionReturn, "%c'+", letter2);
            return;
        }
        else if (position == 1)
        {
            sprintf (expressionReturn, "%c'+", letter1);
            return;
        }
        else if (position == 2)
        {
            sprintf (expressionReturn, "%c+", letter2);
            return;
        }
        /* implicit: if (position == 3) */
        sprintf (expressionReturn, "%c+", letter1);
        return;
    }
}

void
GetAggroupments (const byte arrayKarnaugh[][4], byte karnaughWidth, byte karnaughHeight,
        const char inputLetter[], char expressionReturn[])
{
    byte cellIsAggrouped[karnaughHeight][karnaughWidth];
    byte counterRow, counterColumn;
    byte activeToLeft, activeToRight, activeToUp, activeToDown, sidesPossibilities;
    int getSingleOption;
    
    for (getSingleOption = 1; getSingleOption > 0; getSingleOption ++)
    {
        for (counterRow = 0; counterRow < karnaughHeight; counterRow ++)
        {
            for (counterColumn = 0; counterColumn < karnaughWidth; counterColumn++)
            {
                if (arrayKarnaugh[counterRow][counterColumn] && !cellIsAggrouped[counterRow][counterColumn])
                {
                    sidesPossibilities = 0;
                    
                    for (activeToRight = 0; ((activeToRight < karnaughWidth) && 
                    (arrayKarnaugh[counterRow][KarnaughColumnPos (counterColumn, activeToRight + 1, karnaughWidth)])); activeToRight ++);
                    for (activeToLeft = 0; ((activeToLeft < karnaughWidth) && 
                    (arrayKarnaugh[counterRow][KarnaughColumnPos (counterColumn, activeToLeft - 1, karnaughWidth)])); activeToLeft ++);
                    for (activeToUp = 0; ((activeToUp < karnaughHeight) && 
                    (arrayKarnaugh[counterRow][counterColumn])); activeToUp ++);
                    for (activeToDown = 0; ((activeToDown < karnaughHeight) && 
                    (arrayKarnaugh[counterRow][KarnaughColumnPos (counterColumn, activeToRight + 1, karnaughWidth)])); activeToDown ++);
                    
                    if (activeToRight)
                        sidesPossibilities ++;
                    if (activeToLeft)
                        sidesPossibilities ++;
                    if (activeToUp)
                        sidesPossibilities ++;
                    if (activeToDown)
                        sidesPossibilities ++;
                        
                    if (getSingleOption == 0)
                    {
                        if (sidesPossibilities == 0) /* For alone cells */
                        {
                            KarnaughTwoInputsToExpression (counterRow, inputLetter[0], inputLetter[1], expressionReturn);
                            KarnaughTwoInputsToExpression (counterColumn, inputLetter[2], inputLetter[3], expressionReturn);
                        }
                        
                        else if (sidesPossibilities == 1) /* For alone cells */
                        {
                            if (activeToUp)
                            {
                                KarnaughOneInputToExpression (counterRow, false, inputLetter[0], inputLetter[1], expressionReturn);
                                KarnaughTwoInputsToExpression (counterColumn, inputLetter[2], inputLetter[3], expressionReturn);
                            }
                            else if (activeToDown)
                            {
                                KarnaughOneInputToExpression (counterRow, true, inputLetter[0], inputLetter[1], expressionReturn);
                                KarnaughTwoInputsToExpression (counterColumn, inputLetter[2], inputLetter[3], expressionReturn);
                            }
                            else if (activeToLeft)
                            {
                                KarnaughTwoInputsToExpression (counterRow, inputLetter[0], inputLetter[1], expressionReturn);
                                KarnaughOneInputToExpression (counterColumn, false, inputLetter[2], inputLetter[3], expressionReturn);
                            }
                            else if (activeToRight)
                            {
                                KarnaughTwoInputsToExpression (counterRow, inputLetter[0], inputLetter[1], expressionReturn);
                                KarnaughOneInputToExpression (counterColumn, true, inputLetter[2], inputLetter[3], expressionReturn);
                            }
                        } /* End of only 1 possibility */
                    } /* End of get only 1 or 0 possibilities */
                } /* End of if (cell is 1 and is not aggrouped yet) */
            } /* End of counterColumn for */
        } /*End of counterRow for */
    
    } /* End of getSingleOption for */ 
    return;
}

void
ApplyKarnaugh (const char sourceExpression[], unsigned short sourceExpressionLenght, char newExpression [], byte getNegated, unsigned maxEntryLenght)
{
    /* NOTE: Will only accept minterms not negated and without parentheses ( (A+B)' are not accepted now) */
    /* Don't enter with AAB (redundant inputs), use the RemoveRepeatingTermInMinterm before. */
    
    byte numberOfInputs = 0;
    char inputLetter[MAX_INPUTS];
    unsigned short counter, counter2;
    
    byte ignoreCharsLenght = 2;
    const char ignoreChars[2] = {"'+"};
    
    byte foundOperand;
    char thisMintermExpression[maxEntryLenght];
    
    byte karnaughWidth, karnaughHeight;
    byte arrayKarnaugh[4][4] = {0};
    byte cellIsAggrouped[4][4] = {0};
    
    short int rowCounter, columnCounter;
    
    byte karnaughOnValue; /* May be changed to get the negated expression */
    
    if (getNegated)
        karnaughOnValue = 0;
    else
        karnaughOnValue = 1;

    /* Empty the newExpression string */
    strcpy (newExpression, "");
    
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
    
    /* Set the Karnaugh Map size/bounds */
    if (numberOfInputs == 1)
    {
        karnaughWidth = 1;
        karnaughHeight = 2;
    }
    if (numberOfInputs == 2)
        karnaughWidth = karnaughHeight = 2;
    if (numberOfInputs == 3)
    {
        karnaughWidth = 2;
        karnaughHeight = 4;
    }
    if (numberOfInputs == 4)
        karnaughWidth = karnaughHeight = 4;
    
    /* Put the expression into the map */
    for (counter = 0; sourceExpression[counter] != EOS; counter++)
    {
    }
    
/* DO THE KARNAUGH */
    
    
    
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
                    strcpy (newMinterm, "0");
                    return;
                }
        counter ++;
        
    }
    
    sprintf (newMinterm, "%s%s", termsString, negatedTermsString);
    return;
}

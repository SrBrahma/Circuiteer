#include <string.h>
#include <stdio.h>
#include "Circuiteer.h"

unsigned short
ExpressionToAgroupments (const char oldExpression[],  char newExpression[],
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

void
ApplyKarnaugh (const char oldExpression[], char newExpression [], unsigned maxEntryLenght)
{
    byte numberOfInputs = 0;
    char inputsLetter[MAX_INPUTS];
    unsigned short counter, counter2;
    byte oldExpressionLenght = strlen (oldExpression), ignoreCharsLenght = 4;
    const char ignoreChars[4] = {"()'+"};
    byte foundOperand;
    
    /* First get the number of inputs and its corresponding letters */
    for (counter = 0; counter < oldExpressionLenght; counter ++)
    {
        foundOperand = 1; /* Initial value */
        
        /* Check if the char is an operand or not */
        for (counter2 = 0; counter2 < ignoreCharsLenght; counter2 ++)
            if (oldExpression[counter] == ignoreChars[counter2])
                foundOperand = 0;
                
        if (foundOperand) 
        {
            /* Check if this input is already added */
            for (counter2 = 0; counter2 < numberOfInputs; counter2 ++)
                if (oldExpression[counter] == inputsLetter[counter2])
                    foundOperand = 0;
        
            /* If the input wasn't already added, add it */
            if (foundOperand)
            {
                inputsLetter[numberOfInputs] = oldExpression[counter];
                numberOfInputs ++;
            }
        }
    }
    /*DEBUG*/
    printf ("Number of differents inputs = %u; ", numberOfInputs);
    for (counter = 0; counter < numberOfInputs; counter ++)
        printf ("%c", inputsLetter[counter]);
    printf("\n");
    
}

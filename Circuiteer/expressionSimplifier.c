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
    unsigned short finishedDealingParenthesis = 0;
    unsigned short removeParentheses;
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
            
            else if (openParenthesisBeforeClosePos == 0 && (newExpression[firstCloseParenthesisPos + 1] == '+'
                                                        || newExpression[firstCloseParenthesisPos + 1] == ')'
                                                        || newExpression[firstCloseParenthesisPos + 1] == EOS))
                    removeParentheses = 1;
                    
            else if (openParenthesisBeforeClosePos > 0)
                if ((newExpression[openParenthesisBeforeClosePos - 1] == '+' 
                || newExpression[openParenthesisBeforeClosePos - 1] == '(') && (newExpression[firstCloseParenthesisPos + 1] == '+'
                                                                            || newExpression[firstCloseParenthesisPos + 1] == ')'
                                                                            || newExpression[firstCloseParenthesisPos + 1] == EOS))
                    removeParentheses = 1;
            
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

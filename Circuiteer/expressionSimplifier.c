#include <string.h>
#include "Circuiteer.h"

unsigned short
ExpressionToAgroupments (const char oldExpression[],  char newExpression[],
                         char agroupmentsReturn[MAX_AGROUPMENTS][MAX_AGROUPMENT_LENGHT], unsigned maxStringLenght)
{
    unsigned short numberAgroupments = 0;
    unsigned short counter, counter2 = 0;
    unsigned short oldStringLenght = strlen (originalExpression);
    unsigned short foundMultiplication;
    unsigned short pairsOfParenthesis = 0;
    
    
    /* Copy the old string to the new string, but without the spaces */
    for (counter = 0; counter <= oldStringLenght; counter ++)
        if (oldExpression[counter] != ' ')
        {
            newExpression[counter2] = oldExpression[counter];
            counter2 ++;
        }
        
    /* Now look parenthesis and treat to remove them */
    while (pairsOfParenthesis > 0)
    {
        strcpy (newExpression, oldExpression);
        oldStringLenght = strlen (originalExpression);
        
        while (strchr(
        
        for (counter = 0; counter <= oldStringLenght && ; counter ++)
        {
            
    
    printf ("New expression is: %s\n", newExpression);
    return numberAgroupments;
}

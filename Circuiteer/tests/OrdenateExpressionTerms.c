#include <stdio.h>
#include <string.h>
#include "../expressionSimplifier.h"


/*
b 16
r
display counter
display actualIsNegated
display nextIsNegated
display actualTerm
display expression
display startOfMinterm

*/

int
main (int argc, char *argv[])
{
    char expression[1024];

    strcpy (expression, argv[1]);
    OrdenateExpressionTerms (expression);

    printf ("Ordenated expression is: %s\n", expression);
    return 0;
}

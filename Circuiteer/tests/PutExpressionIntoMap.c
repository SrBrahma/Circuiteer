#include <stdio.h>
#include <string.h>
#include "../expressionSimplifier.h"
typedef unsigned char byte;
/*
b 102
r
s
display counter
display counter2
display beginOfMinterm
display endOfMinterm
display inputPos
display expression
display inputCode[0]
display inputCode[1]
display inputCode[2]
display inputCode[3]

*/

int
main (int argc, char *argv[])
{
    byte karnaughMap[4][4] = {{0}};
    /*
    printf ("Hiii! argv[1] is: \"%s\"\n", argv[1]); */
    PutExpressionIntoMap(argv[1], "ABCD", karnaughMap);

    printf ("Array is:\n");
    printf ("[%u][%u][%u][%u]\n", karnaughMap[0][0], karnaughMap[0][1], karnaughMap[0][2], karnaughMap[0][3]);
    printf ("[%u][%u][%u][%u]\n", karnaughMap[1][0], karnaughMap[1][1], karnaughMap[1][2], karnaughMap[1][3]);
    printf ("[%u][%u][%u][%u]\n", karnaughMap[2][0], karnaughMap[2][1], karnaughMap[2][2], karnaughMap[2][3]);
    printf ("[%u][%u][%u][%u]\n", karnaughMap[3][0], karnaughMap[3][1], karnaughMap[3][2], karnaughMap[3][3]);

    return 0;
}

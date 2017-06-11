#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Circuiteer.h"



#define OK                                  0


#define MOTD                                " =-=-= Circuiteer %s =-=-=\nThis program still in development. If found bugs, please contact.\n\n"
int
main (int argc, char *argv[])
{
    chipType chipsArray[NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS][MAX_NUMBER_CHIPS_PER_GATES];
    unsigned short inputs, outputs, uSCounter;
    byte validationLoadChips;
    unsigned short exitChoice = 0;
    char menuChoice1;
    char inputLetter[MAX_INPUTS];
    char outputsNames[MAX_OUTPUTS][OUTPUTS_MAX_LENGHT_NAME];
    char auxString[128], rawExpression[MAX_ENTRY_LENGHT], treatedExpression[MAX_ENTRY_LENGHT];

    /* Print the Message of the day */
    if (VERSION[0] == EOS)
        printf (MOTD, "Version not properly setted");
    else
        printf (MOTD, VERSION);

    /* Load the chips from the .txt file */
    validationLoadChips = LoadChips (chipsArray);
    printf("DEBUG: LoadChip Exit Code: %u\n\n", validationLoadChips);

    while (exitChoice == 0)
    {
        menuChoice1 = PrintAndReadMenu(MAX_ENTRY_LENGHT);
        printf ("\n");
        switch (menuChoice1)
        {

            /* 1 - Get expressions from outputs */
            case '1':
                /* Get the number of inputs */
                sprintf (auxString, "Enter the number of inputs ([1, %u]):\n", MAX_INPUTS);
                inputs = FgetsUnsigned(auxString, 1, MAX_INPUTS, MAX_ENTRY_LENGHT);
                printf("\n");

                /* Get the letters corresponding to each input */
                for (uSCounter = 0; uSCounter < inputs; uSCounter ++)
                {
                    sprintf (auxString, "Enter the corresponding letter to the input number %u:\n", uSCounter);
                    inputLetter[uSCounter] = FgetsChar (auxString, 0, MAX_ENTRY_LENGHT);
                }
                printf("\n");

                /* Get the number of outputs */
                sprintf (auxString, "Enter the number of outputs ([1, %u]):\n", MAX_OUTPUTS);
                outputs = FgetsUnsigned(auxString, 1, MAX_OUTPUTS, MAX_ENTRY_LENGHT);
                printf("\n");

                /* Get the letters corresponding to each output */
                for (uSCounter = 0; uSCounter < outputs; uSCounter ++)
                {
                    sprintf (auxString, "Enter the corresponding letter to the output number %u:\n", uSCounter);
                    outputsNames[uSCounter][0] = FgetsChar (auxString, 0, MAX_ENTRY_LENGHT);
                }
                printf("\n");

                /* Get the expression for each output WIP*/
                for (uSCounter = 0; uSCounter < outputs; uSCounter ++)
                {
                    sprintf (auxString, "Enter the expression for output %c\n%c = ", outputsNames[uSCounter][0], outputsNames[uSCounter][0]);
                    ReadExpression (auxString, rawExpression, inputLetter, inputs, MAX_ENTRY_LENGHT);
                    /* numberAgroupments[uSCounter] = ExpressionToAgroupments (rawExpression, treatedExpression, NULL, MAX_ENTRY_LENGHT); */
                }
                break;

            /* 2 - debug get endless expressions */
            case '2':
                while (1)
                {
                    sprintf (auxString, "IN DEBUG: Inputs are = A, B, C, D. Enter the expression\nX = ");
                    ReadExpression (auxString, rawExpression, "ABCD", 4, MAX_ENTRY_LENGHT);
                    /* ApplyKarnaugh (rawExpression, strlen (rawExpression), auxString, 1, MAX_EXPRESSION_LENGHT); */
                    printf ("NEW EXPRESSION AFTER REMOVE IS = %s\n", auxString);
                    /*
                    RemoveRepeatingTermInMinterm (rawExpression, auxString, true);



                    RawExpressionToMinterms (rawExpression, treatedExpression, NULL, MAX_EXPRESSION_LENGHT);
                    */
                }
                break;

            default:
                printf ("Invalid option.\n\n");
        } /* End of switch */
    } /* End of main while loop */
    return OK;
}

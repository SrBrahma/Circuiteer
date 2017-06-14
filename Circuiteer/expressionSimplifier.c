#include <string.h>
#include <stdio.h>
#include "Circuiteer.h"
#include "expressionSimplifier.h"

unsigned short
RawExpressionToMinterms (const char oldExpression[],  char newExpression[], char agroupmentsReturn[MAX_AGROUPMENTS][MAX_AGROUPMENT_LENGHT], unsigned maxExpressionLenght)
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
        if (position == 1)
        {
            sprintf (expressionReturn, "%c+", letter2);
            return;
        }
        if (position == 2)
        {
            sprintf (expressionReturn, "%c+", letter1);
            return;
        }
        /* implicit: if (position == 3) */
        sprintf (expressionReturn, "%c'+", letter2);
        return;
    }
    /* Implicit Else; is going Up dor Left. */
    if (position == 0)
    {
        sprintf (expressionReturn, "%c'+", letter2);
        return;
    }
    if (position == 1)
    {
        sprintf (expressionReturn, "%c'+", letter1);
        return;
    }
    if (position == 2)
    {
        sprintf (expressionReturn, "%c+", letter2);
        return;
    }
    /* implicit: if (position == 3) */
    sprintf (expressionReturn, "%c+", letter1);
    return;
}
void
GetAggroupments (const byte arrayKarnaugh[4][4], byte karnaughOnValue, byte karnaughWidth, byte karnaughHeight,
                 const char inputLetter[], char expressionReturn[])
{
    byte cellIsAggrouped[4][4] = {0};
    byte counterRow, counterColumn;
    byte activeToLeft, activeToRight, activeToUp, activeToDown, sidesPossibilities;
    short int getSingleOption;


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
                    (arrayKarnaugh[counterRow][ArrayPositionTranslator (counterColumn + activeToRight + 1, karnaughWidth)])); activeToRight ++);
                    for (activeToLeft = 0; ((activeToLeft < karnaughWidth) &&
                    (arrayKarnaugh[counterRow][ArrayPositionTranslator (counterColumn - activeToLeft - 1, karnaughWidth)])); activeToLeft ++);
                    for (activeToUp = 0; ((activeToUp < karnaughHeight) &&
                    (arrayKarnaugh[counterRow][ArrayPositionTranslator (counterColumn - activeToUp - 1, karnaughHeight)])); activeToDown ++);
                    for (activeToDown = 0; ((activeToDown < karnaughHeight) &&
                    (arrayKarnaugh[counterRow][ArrayPositionTranslator (counterColumn + activeToDown + 1, karnaughHeight)])); activeToDown ++);

                    if (activeToRight)
                        sidesPossibilities ++;
                    if (activeToLeft)
                        sidesPossibilities ++;
                    if (activeToUp)
                        sidesPossibilities ++;
                    if (activeToDown)
                        sidesPossibilities ++;

                    if (getSingleOption == 1)
                    {
                        if (sidesPossibilities == 0) /* For alone cells */
                        {
                            KarnaughTwoInputsToExpression (counterRow, inputLetter[0], inputLetter[1], expressionReturn);
                            KarnaughTwoInputsToExpression (counterColumn, inputLetter[2], inputLetter[3], expressionReturn);
                            cellIsAggrouped[counterRow][counterColumn] = 1;

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

/* NOTE: Will only accept minterms not negated and without parentheses ( (A+B)' are not accepted now) */
/* Don't enter with AAB (redundant inputs), use the RemoveRepeatingTermInMinterm before. */
/* Don't enter with ABC+CA. Enter with ABC+AC. The minterms must be ordened before. */
/* Accepts 1 or 0. */
void
ApplyKarnaugh (const char sourceExpression[], unsigned short sourceExpressionLenght, char newExpression [], byte getNegated,
               unsigned maxEntryLenght)
{


    byte numberOfInputs = 0;
    char inputLetter[MAX_INPUTS];
    unsigned short counter, counter2;

    byte ignoreCharsLenght = 2;
    const char ignoreChars[4] = "'+01";

    byte foundOperand;
    /*char thisMintermExpression[maxEntryLenght];*/

    byte karnaughWidth, karnaughHeight;
    /*
    byte arrayKarnaugh[4][4] = {0};

    byte karnaughOnValue = 1;  May be changed to get the negated expression

    if (getNegated)
        karnaughOnValue = 0; */

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


/* DO THE KARNAUGH */

    /*DEBUG*/
    /*
    printf ("Number of differents inputs = %u; ", numberOfInputs);
    for (counter = 0; counter < numberOfInputs; counter ++)
        printf ("%c", inputLetter[counter]);
    printf("\n"); */
    return;
}


/* Only accpets expressions like "ADBC'DDD+A'B'C+AAAAACAA". Dont use expressions with spaces, parentheses or weird chars.
   Input "A'AABACA'AAA' = Out "A'AAAA'AA'BC. Will not order same-input-negated.
   Also, don't enter with weird stuff in inputsInOrder. */
void
OrdenateExpressionTerms (char expression[])
{
    unsigned short counter, expressionLenght = strlen (expression);
    boolean exitFromFunction = false;
    char *startOfMinterm, actualTerm[3];
    byte actualIsNegated = 1, nextIsNegated; /* From actual, it means on current counter value.
    >> GREAT ATTETION!!!! << 1 is false, 2 is true, to simplify the execution of the code. (but makes the code a little crappy)*/

    startOfMinterm = expression;
    for (counter = 0; !exitFromFunction;)
    {
        actualIsNegated = nextIsNegated = 1;
        if (expression[counter + 1] == '+')
        {
            startOfMinterm = &expression[counter + 2];
            counter += 2;
        }
        else
        {
            if (expression[counter + 1] == '\'')
                actualIsNegated = 2;

            if (counter + actualIsNegated == expressionLenght)
                exitFromFunction = true;
            else
            {
                sprintf (actualTerm, "%.*s", actualIsNegated, &expression[counter]);

                if (expression[counter + actualIsNegated + 1] == '\'')
                    nextIsNegated = 2;

                if (expression[counter] > expression[counter + actualIsNegated])
                {
                    sprintf (expression, "%.*s%.*s%s%s", counter, expression, nextIsNegated, &expression[counter + actualIsNegated],
                             actualTerm, &expression[counter + actualIsNegated + nextIsNegated]);
                    counter = startOfMinterm - expression;
                }
                else
                    counter += actualIsNegated;
            }
        }
    }
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


/* Will not accept "0" or "1". Treat them before. */
void
PutExpressionIntoMap(char *expression, const char *inputLetter, byte karnaughMap[4][4])
{
    byte counter, counter2;
    unsigned short expressionLenght = strlen (expression);
    char *beginOfMinterm;
    char *endOfMinterm = expression - 1;  /* Includes the separator/EOS. Ex: "ABC'+". This var will point to the "+", or "A'CD\0", this var will point to \0. */
    char *inputPos;
    byte inputCode[] = {0, 0, 0, 0};

    /* From left to right:
     * First dimension is the first line letter, as A
     * Second dimension is the second line letter, as B
     * Third dimension is the start/end of the lines */
    static byte twoInputsDecoder[3][3][2] =
    {
        {
            {0, 3}, /* 0,0  */
            {1, 2}, /* 0,B  */
            {3, 4}  /* 0,B' */
        },
        {
            {2, 3}, /* A,0  */
            {2, 2}, /* A,B  */
            {3, 3}  /* A,B' */
        },
        {
            {0, 1}, /* A',0  */
            {1, 1}, /* A',B  */
            {0, 0}, /* A',B' */
        }
    };

    do
    {
        beginOfMinterm = endOfMinterm + 1;

        /* If '+' is not found, endOfMinterm is EOS */
        if (!(endOfMinterm = strchr (beginOfMinterm, '+')))
            endOfMinterm = &expression[expressionLenght];

        for (counter = 0; counter < strlen (inputLetter); counter ++)
        {
            inputPos = strchr (beginOfMinterm, inputLetter[counter]);
            if (!inputPos || inputPos > endOfMinterm) /* If don't find first inputLetter, ex "B" */
                inputCode[counter] = 0;
            else if (inputPos[1] == '\'') /* If there is the inputLetter[0], and is negated*/
                inputCode[counter] = 2;
            else /* If there is the inputLetter[0] and is not negated */
                inputCode[counter] = 1;
        }

        for (counter = twoInputsDecoder[inputCode[0]][inputCode[1]][0]; counter <= twoInputsDecoder[inputCode[0]][inputCode[1]][1]; counter ++)
        {
            for (counter2 = twoInputsDecoder[inputCode[2]][inputCode[3]][0]; counter2 <= twoInputsDecoder[inputCode[2]][inputCode[3]][1]; counter2 ++)
            {
                karnaughMap[(counter == 4? 0 : counter)][(counter2 == 4? 0 : counter2)] = 1;
            }
        }
    }
    while (endOfMinterm != &expression[expressionLenght]);
}

byte
ArrayPositionTranslator (short int position, byte dimensionLenght)
{
    while (position < 0)
        position += dimensionLenght;
    while (position >= dimensionLenght)
        position -= dimensionLenght;

    return ((byte) position);
}

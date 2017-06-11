#include "Circuiteer.h"

unsigned short
RawExpressionToMinterms (const char oldExpression[],  char newExpression[], char agroupmentsReturn[MAX_AGROUPMENTS][MAX_AGROUPMENT_LENGHT], unsigned maxExpressionLenght);

byte
ArrayPositionTranslator (short int position, byte dimensionLenght);

void
KarnaughTwoInputsToExpression (byte position, char letter1, char letter2, char expressionReturn[]);

void
KarnaughOneInputToExpression (byte position, boolean goingDownOrRight, char letter1, char letter2, char expressionReturn[]);

void
GetAggroupments (const byte arrayKarnaugh[4][4], byte karnaughOnValue, byte karnaughWidth, byte karnaughHeight,
                 const char inputLetter[], char expressionReturn[]);

/* NOTE: Will only accept minterms not negated and without parentheses ( (A+B)' are not accepted now) */
/* Don't enter with AAB (redundant inputs), use the RemoveRepeatingTermInMinterm before. */
/* Accepts 1 or 0. */
void
ApplyKarnaugh (const char sourceExpression[], unsigned short sourceExpressionLenght, char newExpression [], byte getNegated,
               unsigned maxEntryLenght);


/* Only accpets expressions like "ADBC'DDD+A'B'C+AAAAACAA". Dont use expressions with spaces, parentheses or weird chars.
   Input "A'AABACA'AAA' = Out "A'AAAA'AA'BC. Will not order same-input-negated.
   Also, don't enter with weird stuff in inputsInOrder. */
void
OrdenateExpressionTerms (char expression[]);

/* This function will transform "AAABB'B'CCD" into ABB'CD.
 * originalMinterm must end with EOS. The newMinterm return will also include a EOS.
 * If checkControversialTerms == true, "AAAA'BBBCD", newMinterm will output "0", as A AND A' will never output 1. */
void
RemoveRepeatingTermInMinterm (const char originalMinterm[], char newMinterm[], boolean checkControversialTerms);

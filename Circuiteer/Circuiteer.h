
#ifndef _CIRCUITEER_
#define _CIRCUITEER_

/* Gates and their correspondent value */
#define AND_INDEX                       0
#define OR_INDEX                        1

#define NAND_INDEX                      2
#define NOR_INDEX                       3

#define XOR_INDEX                       4
#define XNOR_INDEX                      5

#define NOT_INDEX                       6
/* - - - - - - - - - - - - - - - - - - */

/* The total number of gates kinds */
#define NUMBER_OF_GATES_KINDS           7

/* - - - - - - - - - - - - - - - - */

/* Max values, to make the size of the array static */
#define MAX_NUMBER_OF_INPUTS_PER_OUTPUT     8
#define MAX_NUMBER_OF_OUTPUTS               8
#define MAX_NUMBER_CHIPS_PER_GATES          4

#define MAX_CHIP_NAME_SIZE                  32
#define MAX_CHIP_DESCRIPTION_SIZE           128

/* - - - - - - - - - - - - - - - - - - - - - - - - -*/

/* Agroupments stuff */
#define MAX_AGROUPMENT_LENGHT               32
#define MAX_AGROUPMENTS                     MAX_ENTRY_LENGHT/32 /* = 4 */

/* - - - - - - - - -*/
/* Program validation */
#define OK                                  0

/* - - - - - - - - -*/

/* General macros */
#define EOS                                 '\0'
#define MAX_ENTRY_LENGHT                    128
#define MAX_EXPRESSION_LENGHT               256

#define OUTPUTS_MAX_LENGHT_NAME             1
#define MAX_INPUTS                          4
#define MAX_OUTPUTS                         8

/* - - - - - - - -*/

/* Errors */
#define ERROR_EXCEEDS_MAX_STRING_LENGHT             -1
/* - - - - - - - -*/

typedef unsigned char byte;
typedef enum{false, true} boolean;

typedef struct
{
    char name[MAX_CHIP_NAME_SIZE];
    char description[MAX_CHIP_DESCRIPTION_SIZE];
    unsigned short gateKind; /*see the gates index. eg: AND = 0, NOT = 6. */
    unsigned short inputs;
    unsigned short outputs;
    unsigned short inputsPerOutput;
} chipType; 

typedef struct
{
    byte cellXPos;
    byte cellYPos;
} cellPosition;

/* - chipsLoader - */
byte
LoadChips (chipType chipsArrayToReturnToProgram[NUMBER_OF_GATES_KINDS][MAX_NUMBER_OF_INPUTS_PER_OUTPUT][MAX_NUMBER_OF_OUTPUTS][MAX_NUMBER_CHIPS_PER_GATES]);

/* - generalFunctions - */


char
FgetsChar (char printfString[], unsigned short allowSpecialChars, unsigned maxEntryLenght);

unsigned short
FgetsUnsigned (char printfString[], unsigned minValue, unsigned maxValue, unsigned maxEntryLenght);

void
ReadExpression (const char printfString[], char rawExpression[], char inputLetter[], unsigned short numberOfInputs, unsigned maxEntryLenght);

int
CheckLenghtRemoveEndSpacesNewLineToEOS (char stringVar[], unsigned maxEntryLenght);

char
PrintAndReadMenu (unsigned maxEntryLenght);

/* expressionSimplifier */

unsigned short
RawExpressionToMinterms (const char oldExpression[],  char newExpression[], 
                         char agroupmentsReturn[MAX_AGROUPMENTS][MAX_AGROUPMENT_LENGHT], unsigned maxExpressionLenght);
void
ApplyKarnaugh (const char sourceExpression[], unsigned short sourceExpressionLenght, char newExpression [], byte getNegated,
               unsigned maxEntryLenght);
void
RemoveRepeatingTermInMinterm (const char originalMinterm[], char newMinterm[], boolean checkControversialTerms);


#endif

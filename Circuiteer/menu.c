#include <stdio.h>
#include "Circuiteer.h"

char
PrintAndReadMenu (unsigned maxEntryLenght)
{
	printf ("\n =-=-= Select an option =-=-=\n");
	printf ("  1 - Get expressions from outputs\n");
	printf ("  2 - debug get endless expressions\n\n");
	return FgetsChar ("", 1, maxEntryLenght);
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRING_LENGTH 255

typedef enum instructionType
{
	LDC, LD, SUB, ADD, DIVD, MUL, ST, MOD, CMP, JMP, BR, HLT, LABEL, NA, STI, LDI
} instructionType;

typedef struct instruction
{
	struct instruction * next;
	instructionType instrType;
	char * stringValue;
	int stringNumber, value;
} instruction;

char * skipSpaces ( char * string );
int stringToInt ( char ** string );
instruction * parseFile ( FILE * toParse );
int parseString ( char * string, instruction * toParse );
int parseError ( int lineNumber );
int correctness ( char * string, int line );
int labelCheck ( char * string, instruction * toParse );

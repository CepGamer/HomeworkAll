/********************
Болотов Сергей. Инфиксный калькулятор.
*********************/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define WRONG_BRACKETS 1
#define WRONG_SYNTAX 2
#define WRONG_DIVISION 3
#define WRONG_OTHER 0

typedef struct lexem
{
	char type;
	char * begin;
	int value;
} lexem;

typedef struct expression 
{
	lexem * content;
	char * begin;
} expression;

int checkChar ( char toCheck );
void delSpaces ( expression * toParse );
int begin ( char * content );
int parse ( expression * toParse );
void error ( int errType );
int strToInt ( expression * toParse );
int expr ( expression * toParse );
int term ( expression * toParse );
int factor ( expression * toParse );
int isDecimal ( char toCheck );
char previous ( expression * toParse );

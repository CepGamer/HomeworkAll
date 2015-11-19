#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack
{
	struct stack * next;
	int value;
	int isEmpty;
} stack;

int strToInt ( char * str );
void destroy ( stack * upperStack );
void fullDestroy ( stack * upperStack );
void error ();
stack * createStack ( );
stack * push ( stack * upperStack, int value );
int pop ( stack * upperStack );
void print ( stack * upperStack );
void doubleValue ( stack * upperStack );
void swap ( stack * upperStack );

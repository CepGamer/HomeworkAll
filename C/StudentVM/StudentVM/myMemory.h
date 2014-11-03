#include <stdlib.h>
#define NODELENGTH 255

typedef struct myMemory
{
	int isAllocated;
	struct myMemory * next;
	int * isInitialized;
	int * arr;
} myMemory;

int initializeMem ( myMemory * mem );
int * at (  myMemory * mem, int index );
int isInitialized (  myMemory * mem, int index );

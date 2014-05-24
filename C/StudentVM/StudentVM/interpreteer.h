#include "parser.h"
#include "StackElement.h"
#include "myMemory.h"

typedef struct interpreteer
{
	stack * spine;
	instruction * instrList;
	myMemory * virtualMem;
} interpreteer;

typedef enum errType
{
	wrongLabel
} errType;

instruction * searchLabel ( char * labl, instruction * chain );
interpreteer * initializeInterpreteer ( instruction * chain );
int interpreterError ( errType type, int stringNum );
int runProgram ( interpreteer * toRun );

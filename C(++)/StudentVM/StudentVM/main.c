#include "interpreteer.h"

int main ( int argc, char ** argv )
{
    	FILE * mainSVM = fopen ( argv[1], "r");
	instruction * chain = parseFile ( mainSVM );
	interpreteer * runner = initializeInterpreteer ( chain );
	printf("%d", runProgram ( runner ));
	return 0;
}

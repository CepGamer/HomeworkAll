/********************
Болотов Сергей. Инфиксный калькулятор.
*********************/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "infCalc.h"

#define ARR_SIZE 255

int main ()
{
	char * a = ( char * ) malloc ( ARR_SIZE * sizeof ( char ) );
	gets ( a );
	printf ( "%d\n", begin ( a ) );
	free ( a );
	return 0;
}

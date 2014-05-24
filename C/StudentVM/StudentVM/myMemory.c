#include "myMemory.h"

int initializeMem ( myMemory * mem )
{
	int i;
	if ( mem->isAllocated )
		return 1;
	mem->isInitialized = ( int * ) malloc ( 8 * sizeof ( int ) );
	for ( i = 0; i < 8; i++ )
		*( mem->isInitialized + i ) = 0;
	mem->arr = ( int * ) malloc ( 256 * sizeof ( int ) );
	for ( i = 0; i < 256; i++ )
		mem->arr [ i ] = 0;
	return mem->isAllocated = 1;
}

int * at ( myMemory * mem, int index )
{
	if ( index < 0 )
		return NULL;
	if ( index > 255 )
	{
		if ( mem->next == NULL )
		{
			mem->next = ( myMemory * ) malloc ( sizeof ( myMemory ) );
			initializeMem ( mem -> next );
		}
		return at ( mem->next, index - 256 );
	}
	return mem->arr + index;
}

int isInitialized ( myMemory * mem, int index )
{
    return mem->isInitialized [index];
}

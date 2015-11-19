#include "StackElement.h"

int strToInt ( char * str )
{
	int toRet = 0;
	do
	{
		if ( ! ( *str >= '0' && *str <= '9' ) )
		{
			error ();
			return 0;
		}
		toRet *= 10;
		toRet += *str - '0';
	} while ( *++str );
	return toRet;
}

void destroy ( stack * upperStack )
{
	if ( upperStack -> next == NULL )
	{
		upperStack -> isEmpty = 1;
		return ;
	}
	else
	{
		stack * a = upperStack -> next;
		upperStack -> value = a -> value;
		upperStack -> next = a -> next;
		free ( a );
	}
}

void fullDestroy ( stack * upperStack )
{
	while ( !upperStack -> isEmpty )
	{
		destroy ( upperStack );
	}
	free ( upperStack );
}

void error ( )
{
	char c = 0;
	printf ( "%s", "There was an error in Your input. Try to read documentation for this program:\n" );
	printf ( "%s", "http://github.com\n" );
	printf ( "%s", "Would you like to continue work with this program (y/n) ?\n" );
	while ( 1 )
	{
		while ( c == '\n' || c == ' ' )
		{
			scanf ( "%c", &c );
		}
		if ( c == 'n' || c == 'N' )
		{
			exit ( 0 );
		}
		else if ( c == 'y' || c == 'Y' )
		{
			return ;
		}
		else
		{
			printf ( "%s", "Please enter either 'n' or 'y' (no or yes)\n" );
			scanf ( "%c", &c );
		}
	}
}

stack * createStack (  )
{
	stack * upperStack = ( stack * ) malloc ( sizeof ( stack ) );
	upperStack-> value = 0;
	upperStack-> next = NULL;
	upperStack-> isEmpty = 1;
	return upperStack;
}

stack * push ( stack * upperStack, int value )
{
	if ( upperStack -> isEmpty )
	{
		upperStack -> value = value;
		upperStack -> isEmpty = 0;
		return upperStack;
	}
	else 
	{
		stack * newStack = ( stack * ) malloc ( sizeof ( stack ) );
		newStack -> next = upperStack -> next;
		upperStack -> next = newStack;
		newStack -> value = upperStack -> value;
		newStack -> isEmpty = 0;
		upperStack -> value = value;
		return upperStack;
	}
}

int pop ( stack * upperStack )
{
	if ( upperStack -> isEmpty )
	{
		error ();
		return 0;
	}
	else
	{
		int toRet;
		toRet = upperStack -> value;
		destroy ( upperStack );
		return toRet;
	}
}

void print ( stack * upperStack )
{
	if ( upperStack -> isEmpty )
	{
		error ();
		return ;
	}
	printf ( "%d\n", pop ( upperStack ) );
}

void doubleValue ( stack * upperStack )
{
	if ( upperStack -> isEmpty )
	{
		error ();
		return ;
	}
	upperStack -> value *= 2;
}

void swap ( stack * upperStack )
{
	if ( upperStack -> isEmpty )
	{
		error ();
		return ;
	}
	else
	{
		int left, right;
		left = pop ( upperStack );
		right = pop ( upperStack );
		push ( upperStack, right );
		push ( upperStack, left );
	}
}

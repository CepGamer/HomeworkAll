#include "StackCalc.h"

void sum ( stack * upperStack )
{
	int left, right;
	if ( upperStack -> isEmpty || upperStack -> next == NULL )
	{
		error ();
		return ;
	}
	left = pop ( upperStack );
	right = pop ( upperStack );
	push ( upperStack, left + right );
}

void multiply ( stack * upperStack )
{
	int left, right;
	if ( upperStack -> isEmpty || upperStack -> next == NULL )
	{
		error ();
		return ;
	}
	left = pop ( upperStack );
	right = pop ( upperStack );
	push ( upperStack, left * right );
}

void subtract ( stack * upperStack )
{
	int left, right;
	if ( upperStack -> isEmpty || upperStack -> next == NULL )
	{
		error ();
		return ;
	}
	left = pop ( upperStack );
	right = pop ( upperStack );
	push ( upperStack, left - right );
}

void divide ( stack * upperStack )
{
	int left, right;
	if ( upperStack -> isEmpty || upperStack -> next == NULL )
	{
		error ();
		return ;
	}
	left = pop ( upperStack );
	right = pop ( upperStack );
	if ( right == 0 )
	{
		error ();
		return ;
	}
	push ( upperStack, left / right );
}

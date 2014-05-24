/*
	Стековый калькулятор, Болотов Сергей, 171 группа.
*/
#include "StackCalc.h"

void operate ( stack * upperStack, char * toOperate )
{
/*	if ( strcmp ( toOperate, "push" ) == 0 )
	{
		char * x = ( char * ) malloc ( sizeof ( char ) * 15 );
		scanf ( "%s", x );
		push ( upperStack, strToInt ( x ) );
		free ( x );
		//return ;
	}*/
	if ( strcmp ( toOperate, "pop" ) == 0 )
	{
		pop ( upperStack );
		//return ;
	}
	else if ( strcmp ( toOperate, "duplicate" ) == 0 )
	{
		doubleValue ( upperStack );
		//return ;
	}
	else if ( strcmp ( toOperate, "swap" ) == 0 )
	{
		swap ( upperStack );
		//return ;
	}
	else if ( strcmp ( toOperate, "print" ) == 0 )
	{
		print ( upperStack );
		//return ;
	}
/*	if ( strlen ( toOperate ) > 1 )
	{
		error ();
		return ;
	}*/
	else
	{
		switch ( *toOperate )
		{
		case '+':
			sum ( upperStack );
			break;
		case '-':
			subtract ( upperStack );
			break;
		case '*':
			multiply ( upperStack );
			break;
		case '/':
			divide ( upperStack );
			break;
		default:
			push ( upperStack, strToInt ( toOperate ) );
			break;
		}
	}
}

int main ()
{
	char * str;
	stack * operatorStack;
	str = ( char * ) malloc ( sizeof ( char ) * 10 );
	operatorStack = createStack ( );
	while ( scanf ( "%s", str ) )
	{
		operate ( operatorStack, str );
	}
	free ( str );
	return 0;
}

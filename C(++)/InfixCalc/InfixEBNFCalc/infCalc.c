/********************
Болотов Сергей. Инфиксный калькулятор.
*********************/
#include "infCalc.h"
/*
Определения:
WRONG_BRACKETS 1
WRONG_SYNTAX 2
WRONG_DIVISION 3
WRONG_OTHER 0
*/
void error ( int errType )
{
	switch ( errType )
	{
	case WRONG_BRACKETS:
		printf ( "Неправильно расставлены скобки.\n" );
		break;
	case WRONG_DIVISION:
		printf ( "Деление на ноль.\n" );
		break;
	case WRONG_SYNTAX:
		printf ( "Синтаксическая ошибка.\n" );
		break;
	case WRONG_OTHER:
		printf ( "\"Что-то отвалилось\".\n" );
		break;
	default:
		printf ( "Неизвестная ошибка, код: %d.\n", errType );
		break;
	}
	exit ( errType );
}
int strToInt ( lexem * toParse )
{
	int a = 0;
	delSpaces ( toParse );
	if ( !( * toParse -> begin >= '0' && * toParse -> begin <= '9' ) && ( * ( toParse -> begin - 1 ) != '(' ) )
	{
		error ( WRONG_SYNTAX );
	}
	while ( * toParse -> begin >= '0' && * toParse -> begin <= '9' )
	{
		a *= 10;
		a += * toParse -> begin++ - '0';
	}
	delSpaces ( toParse );
	toParse -> value = a;
	return toParse -> value;
}

int begin ( char * content )
{
	int a;
	expression * progress = ( expression * ) malloc ( sizeof ( expression ) );
	progress -> content = ( lexem * ) malloc ( sizeof ( lexem ) );
	progress -> content -> begin = progress -> begin = content; 
	a = parse ( progress );
	free ( progress -> content );
	free ( progress );
	return a;
}

int parse ( expression * toParse )
{
	return expr ( toParse -> content );
}

int expr ( lexem * toParse )
{
	lexem a;
	a.begin = toParse -> begin;
	a.value = term ( & a );
	a.type = * a.begin;
	if ( checkChar ( * a.begin ) )
	{
		error ( WRONG_SYNTAX );
	}
	while ( a.type == '-' || a.type == '+' )
	{
		lexem b;
		a.begin++;
		b.value = term ( & a );
		if ( a.type == '+' )
		{
			a.value += b.value;
		}
		else
		{
			a.value -= b.value;
		}
		a.type = * a.begin;
		if ( checkChar ( a.type ) )
		{
			error ( WRONG_SYNTAX );
		}
	}
	toParse -> begin = a.begin;
	return a.value;
}

int term ( lexem * toParse )
{
	lexem a;
	a.begin = toParse -> begin;
	a.value = factor ( &a );
	a.type = * a.begin;
	if ( checkChar ( a.type ) )
	{
		error ( WRONG_SYNTAX );
	}
	while ( a.type == '*' || a.type == '/' )
	{
		lexem b;
		b.begin = ++a.begin;
		b.value = term ( & b );
		a.begin = b.begin;
		if ( b.value == 0 && a.type == '/' )
		{
			error ( WRONG_DIVISION );
		}
		if ( a.type == '*' )
		{
			a.value *= b.value;
		}
		else
		{
			a.value /= b.value;
		}
		a.begin = b.begin;
		a.type = * a.begin;
		if ( checkChar ( a.type ) )
		{
			error ( WRONG_SYNTAX );
		}
	}
	toParse -> begin = a.begin;
	return a.value;
}

int factor ( lexem * toParse )
{
	lexem a;
	a.begin = toParse -> begin;
	delSpaces ( & a );
	if ( !isDecimal ( * a.begin ) && * a.begin != '(' && * a.begin != ')' )
	{
		error ( WRONG_SYNTAX );
	}
	if ( * a.begin == '(' )
	{
		lexem b;
		b.begin = ++a.begin;
		b.value = expr ( &b );
		delSpaces ( & b );
		a.value = b.value;
		a.begin = b.begin;
		a.type = * a.begin;
		if ( a.type == ')' )
		{
			toParse -> begin = a.begin;
			return a.value;
		}
		error ( WRONG_BRACKETS );
	}
	else
	{
		a.value = strToInt ( & a );
		toParse -> begin = a.begin;
		return a.value;
	}
}

void delSpaces ( lexem * toParse )
{
	while ( * toParse -> begin++ == ' ' );
	toParse -> begin--;
	if ( checkChar ( * toParse -> begin ) )
	{
		error ( WRONG_SYNTAX );
	}
}

int checkChar ( char toCheck )
{
	return !( ( ( toCheck <= '9' ) && ( toCheck >= '0' ) ) || toCheck == '*' || toCheck == '+' || toCheck == '/' || toCheck == '-' || toCheck == '(' || toCheck == ')' || toCheck == 0 );
}

int isDecimal ( char toCheck )
{
	return ( toCheck >= '0' && toCheck <= '9' );
}

char previous ( lexem * toParse )
{
	char * a = toParse -> begin - 1;
	while ( *a-- == ' ' );
	a++;
	return *a;
}

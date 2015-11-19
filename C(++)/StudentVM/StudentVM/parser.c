#include "parser.h"

char * skipSpaces ( char * string )
{
	while ( *string == '\t' || *string == ' ' )
		string++;
	return string;
}

int stringToInt ( char ** string )	//	Converts string into an integer
{
	int a = 0;
	while ( **string >= '0' && *(*string)++ <= '9' )
	{
		a *= 10;
		a += *( *string - 1 ) - '0';
	}
	return a;
}

int labelCheck ( char * string, instruction * toParse )
{
	char * a = string;
	while ( *string++ )
	{
		if ( *string == ':' )
		{
			correctness ( string + 1 , toParse->stringNumber );
			break;
		}
	}
	toParse->stringValue = ( char * ) malloc ( sizeof ( char ) * ( string - a + 1 ) );
	string [0] = 0;
	strcpy ( toParse->stringValue, a);
	string [0] = ':';
	toParse->instrType = LABEL;
}

int parseError ( int lineNumber )	//	Exits with BANG.
{
	int * a = ( int * ) malloc ( sizeof ( int ) );	//	Dat Bang.
	printf ( "Syntax error in line: %d", lineNumber );
	//while ( *a-- = 5 );
	exit ( lineNumber );
}

int correctness ( char * string, int line )
{
	do
	{
		if ( ! ( *string == ' ' ) )
            if ( *string == ';' || *string == '\n' || *string == 0 )
				return 1;
			else parseError ( line );
	}
	while ( *++string );
}

instruction * parseFile ( FILE * toParse )
{
	int i = 0;
	char * a;
	char * string = ( char * ) malloc ( STRING_LENGTH * sizeof ( char ) );
	instruction * toRet = ( instruction * ) malloc ( sizeof ( instruction ) );
	instruction * parser = toRet;
	a = string;
	string = fgets ( string, STRING_LENGTH, toParse );
	while ( string != NULL )
	{
		parser->stringNumber = i++;
		parser->stringValue = NULL;
		parser->value = 0;
		parser->next = ( instruction * ) malloc ( sizeof ( instruction ) );
		parseString ( string, parser );
		parser = parser->next;
		parser->instrType = NA;
		string = fgets ( string, STRING_LENGTH, toParse );
	}
	free ( a );
	return toRet;
}

int parseString ( char * string, instruction * toParse )
{
//	add, br, cmp, divd, hlt, jmp, LDC, LD, mul, mod, sub, st
	skipSpaces ( string );
	switch ( string [ 0 ] ) // Code which checks whether the string is command, label or "F*NG NOTHING we need to BSOD!"
	{
	case 'a':	//	add type or label
		if ( string [1] == 'd' && string [2] == 'd' )
		{
			string += 3;
			string = skipSpaces ( string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = ADD;
		} else labelCheck ( string, toParse );
		break;
	case 'b':	//	br type -//-
		if ( string [1] == 'r' && string [2] == ' ' )
		{
			char * a = strchr ( string, '\n' );
			string += 2;
			string = skipSpaces ( string );
			*a = 0;
			toParse->stringValue = ( char * ) malloc ( sizeof ( char ) * strlen ( string ) );
			strcpy ( toParse->stringValue, string );
			*a = '\n';
			string = a;
			correctness ( string, toParse->stringNumber );
			toParse->instrType = BR;
		} else labelCheck ( string, toParse );
		break;
	case 'c':	//	cmp type -//-
		if ( string [1] == 'm' && string [2] == 'p' )
		{
			string += 3;
			string = skipSpaces ( string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = CMP;
		} else labelCheck ( string, toParse );
		break;
	case 'd':	//	divd type -//-
		if ( string [1] == 'i' && string [2] == 'v' )
		{
			string += 3;
			string = skipSpaces ( string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = DIVD;
		} else labelCheck ( string, toParse );
		break;
	case 'h':	//	hlt type -//-
		if ( string [1] == 'l' && string [2] == 't' )
		{
			string += 3;
			string = skipSpaces ( string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = HLT;
		} else labelCheck ( string, toParse );
		break;
	case 'j':	//	jmp type -//-
		if ( string [1] == 'm' && string [2] == 'p' && string [3] == ' ' )
		{
            char * a = strchr ( string, '\n' );
			string += 3;
            string = skipSpaces ( string );
            /*
			strcpy ( toParse->stringValue, string );
            correctness ( string, toParse->stringNumber );*/
            *a = 0;
            toParse->stringValue = ( char * ) malloc ( sizeof ( char ) * strlen ( string ) );
            strcpy ( toParse->stringValue, string );
            *a = '\n';
            string = a;
            correctness ( string, toParse->stringNumber );
			toParse->instrType = JMP;
		} else labelCheck ( string, toParse );
		break;
	case 'l':	//	LD/LDC/LDI type -//-
		if ( string [1] == 'd' && string [2] == 'c' && string [3] == ' ' )
		{
			string += 3;
			string = skipSpaces ( string );
			toParse->value = stringToInt ( &string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = LDC;
		} else if ( string [1] == 'd' && string [2] == ' ' )
		{
			string += 2;
			string = skipSpaces ( string );
			toParse->value = stringToInt ( &string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = LD;
		} else if ( string [1] == 'd' && string [2] == 'i' )
		{
			string += 3;
			string = skipSpaces ( string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = LDI;
		} else labelCheck ( string, toParse );
		break;
	case 'm':	//	mul/mod type -//-
		if ( string [1] == 'u' && string [2] == 'l' )
		{
			string += 3;
			string = skipSpaces ( string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = MUL;
		} else if ( string [1] == 'o' && string [2] == 'd' )
		{
			string += 3;
			string = skipSpaces ( string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = MOD;
		} else labelCheck ( string, toParse );
		break;
	case 's':	//	sub/st type -//-
		if ( string [1] == 'u' && string [2] == 'b' )
		{
			string += 3;
			string = skipSpaces ( string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = SUB;
		} else if ( string [1] == 't' && string [2] == ' ' )
		{
			string += 2;
			string = skipSpaces ( string );
			toParse->value = stringToInt ( &string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = ST;
		} else if ( string [1] == 't' && string [2] == 'i' )
		{
			string += 3;
			string = skipSpaces ( string );
			correctness ( string, toParse->stringNumber );
			toParse->instrType = STI;
		} else labelCheck ( string, toParse );
		break;
	default:
		labelCheck ( string, toParse );
		break;
	}
}

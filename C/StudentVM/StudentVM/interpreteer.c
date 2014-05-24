#include "interpreteer.h"

instruction * searchLabel ( char * labl, instruction * chain )
{
    while ( chain->instrType != NA )
	{
        if ( chain->instrType != LABEL )
		{
			chain = chain->next;
			continue;
		}
		if ( !strcmp ( labl, chain->stringValue ) )
			return chain;
		chain = chain->next;
	}
	interpreterError ( wrongLabel, chain->stringNumber );
}

interpreteer * initializeInterpreteer ( instruction * chain )
{
	interpreteer * mainInt = ( interpreteer * ) malloc ( sizeof ( interpreteer ) );
	mainInt->spine = ( stack * ) malloc ( sizeof ( stack ) );
	mainInt->virtualMem = ( myMemory * ) malloc ( sizeof ( myMemory ) );
	mainInt->instrList = chain;
	mainInt->spine = createStack ();
	mainInt->virtualMem->isAllocated = 0;
	initializeMem ( mainInt->virtualMem );
	return mainInt;
}

int runProgram ( interpreteer * toRun )
{
	instruction * buffer = toRun->instrList;
	while ( 1 )
	{
		int a, b;
        switch ( toRun->instrList->instrType )
		{
			//	add, br, cmp, divd, hlt, jmp, labe, ldc, ld, mul, mod, sub, st
		case ADD:
			a = pop ( toRun->spine );
			b = pop ( toRun->spine );
			push ( toRun->spine, a + b );
			toRun->instrList = toRun->instrList->next;
			break;
		case BR:
			if ( !(pop ( toRun->spine ) == 0) )
				toRun->instrList = searchLabel ( toRun->instrList->stringValue,  buffer );
			else toRun->instrList = toRun->instrList->next;
			break;
		case CMP:
			a = pop ( toRun->spine );
			b = pop ( toRun->spine );
			if ( b < a )
				push ( toRun->spine, -1 );
			else if ( b == a )
				push ( toRun->spine, 0 );
			else push ( toRun->spine, 1 );
			toRun->instrList = toRun->instrList->next;
			break;
		case DIVD:
			a = pop ( toRun->spine );
			b = pop ( toRun->spine );
			push ( toRun->spine, b / a );
			toRun->instrList = toRun->instrList->next;
			break;
		case HLT:
			return pop ( toRun->spine );
			break;
		case JMP:
			toRun->instrList = searchLabel ( toRun->instrList->stringValue, buffer );
			break;
		case LABEL:
			toRun->instrList = toRun->instrList->next;
			break;
		case LDC:
			push ( toRun->spine, toRun->instrList->value );
			toRun->instrList = toRun->instrList->next;
			break;
		case LD:
			push ( toRun->spine , *at ( toRun->virtualMem, toRun->instrList->value ) );
			toRun->instrList = toRun->instrList->next;
			break;
		case MUL:
			a = pop ( toRun->spine );
			b = pop ( toRun->spine );
			push ( toRun->spine, b * a );
			toRun->instrList = toRun->instrList->next;
			break;
		case MOD:
			a = pop ( toRun->spine );
			b = pop ( toRun->spine );
			push ( toRun->spine, b % a );
			toRun->instrList = toRun->instrList->next;
			break;
		case SUB:
			a = pop ( toRun->spine );
			b = pop ( toRun->spine );
			push ( toRun->spine, b - a );
			toRun->instrList = toRun->instrList->next;
			break;
		case ST:
			*at ( toRun->virtualMem, toRun->instrList->value ) = pop ( toRun->spine );
			toRun->instrList = toRun->instrList->next;
			break;
		case STI:
			a = pop ( toRun->spine );
			b = pop ( toRun->spine );
			*at ( toRun->virtualMem, a ) = b;
			toRun->instrList = toRun->instrList->next;
			break;
		case LDI:
			a = pop ( toRun->spine );
			push ( toRun->spine, *at ( toRun->virtualMem, a ) );
			toRun->instrList = toRun->instrList->next;
			break;
		case NA:
			exit ( pop ( toRun->spine ) );
			break;
		default:
			exit ( pop ( toRun->spine ) );
			break;
		}
	}
}

int interpreterError ( errType type, int stringNum )
{
	switch ( type )
	{
	case wrongLabel:
		printf ( "Error in string ¹%d: label not found.", stringNum );
		break;
	default:
		break;
	}
}

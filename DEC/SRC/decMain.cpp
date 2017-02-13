#include "stdafx.h"
#include "..\INC\dec.h"
#include "..\..\SYS_LINK\INC\sysLink.h"


extern SYS_LINK_DATA   *sysLinkDataPtr;


//extern DEC_DATA	*decDataPtr;

//**********************************************

//**********************************************
int decInit( DEC_DATA *decDataPtr )
{
	decDataPtr->decState = DEC_IDLE;
	decDataPtr->readAt = 0;
	decDataPtr->lineOutput = false;
	decDataPtr->markBlockCommand = false;
	decDataPtr->relative = false;
	decDataPtr->feedrate = DEFAULT_FEEDRATE;
	//decDataPtr->asciiPtr;
	//decDataPtr->block;
	decDataPtr->blockCommand = NULL_INTP;
	//decDataPtr->blockNumber = 0;
	//decDataPtr->enterHolder = 0;
	decDataPtr->lineOutput = false;
	decDataPtr->markF = false;
	decDataPtr->markG60 = false;
	decDataPtr->markM00 = false;
	decDataPtr->markM01 = false;
	decDataPtr->markN = false;
	decDataPtr->markPlane = false;
	decDataPtr->markRelAbs = false;
	//decDataPtr->plane;
	decDataPtr->programend = false;
	decDataPtr->UVWXYZ = false;
	decDataPtr->coordinate = NULL_COORDINATE;

	int i;
	for( i = 0; i < 3; i++ )
	{
		decDataPtr->ijkCoordinate[i] = 0;
		decDataPtr->markIJK[i] = false;
		decDataPtr->markUVWXYZ[i] = false;
		decDataPtr->xyzCoordinate[i] = 0;
		decDataPtr->uvwCoordinate[i] = 0;
	}
	return true;
}

//**********************************************

//**********************************************
int decReset( DEC_DATA *decDataPtr )
{
	decDataPtr->decState = DEC_IDLE;
	decDataPtr->readAt = 0;
	decDataPtr->lineOutput = false;
	decDataPtr->markBlockCommand = false;
	decDataPtr->relative = false;
	decDataPtr->feedrate = 500;
	//decDataPtr->asciiPtr;
	//decDataPtr->block;
	decDataPtr->blockCommand = NULL_INTP;
	//decDataPtr->blockNumber = 0;
	//decDataPtr->enterHolder = 0;
	decDataPtr->markF = false;
	decDataPtr->markG60 = false;
	decDataPtr->markM00 = false;
	decDataPtr->markM01 = false;
	decDataPtr->markN = false;
	decDataPtr->markPlane = false;
	decDataPtr->markRelAbs = false;
	//decDataPtr->plane;
	decDataPtr->programend = false;
	decDataPtr->UVWXYZ = false;

	int i;
	for( i = 0; i < 3; i++ )
	{
		decDataPtr->ijkCoordinate[i] = 0;
		decDataPtr->markIJK[i] = false;
		decDataPtr->markUVWXYZ[i] = false;
		decDataPtr->xyzCoordinate[i] = 0;
		decDataPtr->uvwCoordinate[i] = 0;
	}

	if( decDataPtr->ncFilePtr )
		fclose( decDataPtr->ncFilePtr );
	sysLinkDataPtr->sysToDecLinkData.fileValid = false;

	return true;
}

//**********************************************

//**********************************************
int decMain( DEC_DATA *decDataPtr )
{
	if( sysLinkDataPtr->pannelInput.reset == true )
		decReset( decDataPtr );
	//getting info
	//actions if any orders come
	switch( decDataPtr->decState )
	{
	case DEC_IDLE:
		decIdle( decDataPtr );
		break;

	case DEC_OPEN_NC_PROGRAM:
		decOpenNcProgram( decDataPtr );
		break;

	case DEC_NC_PROGRAM_RUN:
		decNcProgramRun( decDataPtr );
		break;

	case DEC_CLOSE:
		decClose( decDataPtr );
		break;

	case DEC_ERROR:
		decError( decDataPtr );
		break;
	}

	return true;
}

//**********************************************

//**********************************************
int decClose( DEC_DATA *decDataPtr )
{
	if( sysLinkDataPtr->opMode == MEM_MODE )
		fclose( decDataPtr->ncFilePtr );
	sysLinkDataPtr->sysToDecLinkData.fileValid = false;
	//需釋放記憶體 malloc() free()
	decReset( decDataPtr );
	return true;
}

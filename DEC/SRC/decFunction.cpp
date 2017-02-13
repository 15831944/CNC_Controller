#include "stdafx.h"
#include "io.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "..\INC\dec.h"
#include "..\..\SYS_LINK\INC\sysLink.h"


extern SYS_LINK_DATA   *sysLinkDataPtr;


//**********************************************

//**********************************************
int getFileLength ( DEC_DATA *decDataPtr)
{ 
	int pos = ftell( decDataPtr->ncFilePtr ); 
	int len = 0; 
	fseek (  decDataPtr->ncFilePtr, 0, SEEK_END ); 
	len = ftell(  decDataPtr->ncFilePtr ); 
	fseek (  decDataPtr->ncFilePtr, pos, SEEK_SET ); 
	return len; 
 }

//**********************************************

//**********************************************
#define TAB    0x09  //TAB鍵的定義

char *overToken( char *inPtr )
{
	char *outPtr;

	for ( outPtr = inPtr; (*outPtr ==' ')||(*outPtr == TAB); outPtr++ )
	{
	}

	return ( outPtr );
}

//**********************************************
//這個function可放到glob
//**********************************************
#define DIGIT(ch) ( ( ch >= '0' && ch <= '9' ) || ch == '-' || ch == '+' || ch == '.' ) //以DIGIT(ch)取代( ch >= '0' && ch <= '9' )

char* passDigit( char* inPtr )
{
	for ( ; DIGIT( *inPtr ); inPtr++ )
	{
	}

	return ( inPtr );
}

//**********************************************

//**********************************************
int nFunction( DEC_DATA* decDataPtr )
{
	if( decDataPtr->markN == true )
		return ( ERROR_CODE_N );
	
	decDataPtr->asciiPtr++;
	decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
	
	if( DIGIT( *decDataPtr->asciiPtr ) == false )
	{
		return ( ERROR_CODE_N );
	}
	else
	{
		decDataPtr->blockNumber = atoi( (const char*)decDataPtr->asciiPtr );
		decDataPtr->markN = true;
		decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
	}
	return true;
}

//**********************************************
//dec to blockcommand
//**********************************************
int gFunction( DEC_DATA* decDataPtr )
{
	int n;

	decDataPtr->asciiPtr++;
	decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
	
	if( DIGIT( *decDataPtr->asciiPtr ) == false )
	{
		return ( ERROR_CODE_N );
	}
	n = atoi( (const char*)decDataPtr->asciiPtr );
	switch( n )
	{
	case 0:
		if( decDataPtr-> markBlockCommand == false )
		{
			decDataPtr->blockCommand = G00_MOTION;
			decDataPtr->markBlockCommand = true;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
			decDataPtr->lineOutput = true;
			decDataPtr->motionModal = true;
			decDataPtr->markF = true;
			decDataPtr->feedrate = MAX_FEEDRATE;
		}
		else
		{
			return ( ERROR_CODE_G );
		}
		break;

	case 1:
		if( decDataPtr-> markBlockCommand == false )
		{
			decDataPtr->blockCommand = G01_MOTION;
			decDataPtr->markBlockCommand = true;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
			decDataPtr->lineOutput = true;
			decDataPtr->motionModal = true;
		}
		else
		{
			return( ERROR_CODE_G );
		}
		break;

	case 2:
		if( decDataPtr-> markBlockCommand == false )
		{
			decDataPtr->blockCommand = G02_MOTION;
			decDataPtr->markBlockCommand = true;
			decDataPtr->lineOutput = true;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
			decDataPtr->motionModal = false;
			/*if( decDataPtr->markRelAbs == false )
			{
				decDataPtr->markRelAbs = true;
				decDataPtr->relative = true;
			}
			else
			{
				return ( ERROR_CODE_G );
			}*/
		}
		else
		{
			return ( ERROR_CODE_G );
		}
		break;

	case 3:
		if( decDataPtr-> markBlockCommand == false )
		{
			decDataPtr->blockCommand = G03_MOTION;
			decDataPtr->markBlockCommand = true;
			decDataPtr->lineOutput = true;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
			decDataPtr->motionModal = false;
			/*if( decDataPtr->markRelAbs == false )
			{
				decDataPtr->markRelAbs = true;
				decDataPtr->relative = true;
			}
			else
			{
				return ( ERROR_CODE_G );
			}*/
		}
		else
		{
			return ( ERROR_CODE_G );
		}
		break;

	case 4:
		if( decDataPtr-> markBlockCommand == false )
		{
			decDataPtr->blockCommand = G04_DWELL_TIME;
			decDataPtr->markBlockCommand = true;
			decDataPtr->motionModal = false;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
		}
		else
		{
			return ( ERROR_CODE_G );
		}
		break;

	case 17:
		if( decDataPtr->markPlane == false )
		{
			decDataPtr->markPlane = true;
			decDataPtr->plane = XY_PLANE;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
		}
		else
		{
			return ( ERROR_CODE_G );
		}
		break;

	case 18:
		if( decDataPtr->markPlane == false )
		{
			decDataPtr->markPlane = true;
			decDataPtr->plane = YZ_PLANE;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
		}
		else
		{
			return ( ERROR_CODE_G );
		}
		break;

	case 19:
		if( decDataPtr->markPlane == false )
		{
			decDataPtr->markPlane = true;
			decDataPtr->plane = ZX_PLANE;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
		}
		else
		{
			return ( ERROR_CODE_G );
		}
		break;

	case 60:
		if( decDataPtr->markG60 == false )
		{
			decDataPtr->markG60 = true;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
		}
		else
		{
			return ( ERROR_CODE_G );
		}
		break;

	case 90:
		if( decDataPtr->markRelAbs == false )
		{
			decDataPtr->markRelAbs = true;
			decDataPtr->relative = false;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
		}
		else
		{
			return ( ERROR_CODE_G );
		}
		break;

	case 91:
		if( decDataPtr->markRelAbs == false )
		{
			decDataPtr->markRelAbs = true;
			decDataPtr->relative = true;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
		}
		else
		{
			return ( ERROR_CODE_G );
		}
		break;

	}
	return true;
}

//**********************************************

//**********************************************
int coordinateFunction( DEC_DATA* decDataPtr )
{
	if( decDataPtr->coordinate == UVW_COORDINATE )
	{
		return ( ERROR_CODE_COORDINATE );
	}
	else
	{
		decDataPtr->coordinate = XYZ_COORDINATE;

		switch( *decDataPtr->asciiPtr )
		{
		case 'X':
		case 'x':
			if( decDataPtr->markUVWXYZ[0] == false )
			{
				decDataPtr->asciiPtr++;
				decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
				if( DIGIT( *decDataPtr->asciiPtr ) == false )
				{
					return ( ERROR_CODE_XYZ );
				}
				else
				{
					decDataPtr->xyzCoordinate[0] = atof( decDataPtr->asciiPtr );
					decDataPtr->markUVWXYZ[0] = true;
					decDataPtr->UVWXYZ = true;
				}
			}
			else
			{
				return ( ERROR_CODE_XYZ );
			}
			break;

		case 'Y':
		case 'y':
			if( decDataPtr->markUVWXYZ[1] == false )
			{
				decDataPtr->asciiPtr++;
				decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
				if( DIGIT( *decDataPtr->asciiPtr ) == false )
				{
					return ( ERROR_CODE_XYZ );
				}
				else
				{
					decDataPtr->xyzCoordinate[1] = atof( decDataPtr->asciiPtr );
					decDataPtr->markUVWXYZ[1] = true;
					decDataPtr->UVWXYZ = true;
				}
			}
			else
			{
				return ( ERROR_CODE_XYZ );
			}
			break;

		case 'Z':
		case 'z':
			if( decDataPtr->markUVWXYZ[2] == false )
			{
				decDataPtr->asciiPtr++;
				decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
				if( DIGIT( *decDataPtr->asciiPtr ) == false )
				{
					return ( ERROR_CODE_XYZ );
				}
				else
				{
					decDataPtr->xyzCoordinate[2] = atof( decDataPtr->asciiPtr );
					decDataPtr->markUVWXYZ[2] = true;
					decDataPtr->UVWXYZ = true;
				}
			}
			else
			{
				return ( ERROR_CODE_XYZ );
			}
			break;
		}
	}

	decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
	return true;
}

//**********************************************

//**********************************************
int ijkFunction( DEC_DATA* decDataPtr )
{
	switch( *decDataPtr->asciiPtr )
	{
	case 'I':
	case 'i':
		if( decDataPtr->markIJK[0] == false )
		{
			decDataPtr->asciiPtr++;
			decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
			if( DIGIT( *decDataPtr->asciiPtr ) == false )
			{
				return ( ERROR_CODE_IJK );
			}
			else
			{
				decDataPtr->ijkCoordinate[0] = atof( decDataPtr->asciiPtr );
				decDataPtr->markIJK[0] = true;
			}
		}
		else
		{
			return ( ERROR_CODE_IJK );
		}
		break;

	case 'J':
	case 'j':
		if( decDataPtr->markIJK[1] == false )
		{
			decDataPtr->asciiPtr++;
			decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
			if( DIGIT( *decDataPtr->asciiPtr ) == false )
			{
				return ( ERROR_CODE_IJK );
			}
			else
			{
				decDataPtr->ijkCoordinate[1] = atof( decDataPtr->asciiPtr );
				decDataPtr->markIJK[1] = true;
			}
		}
		else
		{
			return ( ERROR_CODE_IJK );
		}
		break;

	case 'K':
	case 'k':
		if( decDataPtr->markIJK[2] == false )
		{
			decDataPtr->asciiPtr++;
			decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
			if( DIGIT( *decDataPtr->asciiPtr ) == false )
			{
				return ( ERROR_CODE_IJK );
			}
			else
			{
				decDataPtr->ijkCoordinate[2] = atof( decDataPtr->asciiPtr );
				decDataPtr->markIJK[2] = true;
			}
		}
		else
		{
			return ( ERROR_CODE_IJK );
		}
		break;
	}

	decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
	return true;
}

//**********************************************

//**********************************************
int uvwFunction( DEC_DATA* decDataPtr )
{
	if( decDataPtr->coordinate == XYZ_COORDINATE )
	{
		return ( ERROR_CODE_COORDINATE );
	}
	else
	{
		decDataPtr->coordinate = UVW_COORDINATE;

		switch( *decDataPtr->asciiPtr )
		{
		case 'U':
		case 'u':
			if( decDataPtr->markUVWXYZ[0] == false )
			{
				decDataPtr->asciiPtr++;
				decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
				if( DIGIT( *decDataPtr->asciiPtr ) == false )
				{
					return ( ERROR_CODE_UVW );
				}
				else
				{
					decDataPtr->uvwCoordinate[0] = atof( decDataPtr->asciiPtr );
					decDataPtr->markUVWXYZ[0] = true;
					decDataPtr->UVWXYZ = true;
				}
			}
			else
			{
				return ( ERROR_CODE_UVW );
			}
			break;

		case 'V':
		case 'v':
			if( decDataPtr->markUVWXYZ[1] == false )
			{
				decDataPtr->asciiPtr++;
				decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
				if( DIGIT( *decDataPtr->asciiPtr ) == false )
				{
					return ( ERROR_CODE_UVW );
				}
				else
				{
					decDataPtr->uvwCoordinate[1] = atof( decDataPtr->asciiPtr );
					decDataPtr->markUVWXYZ[1] = true;
					decDataPtr->UVWXYZ = true;
				}
			}
			else
			{
				return ( ERROR_CODE_UVW );
			}
			break;

		case 'W':
		case 'w':
			if( decDataPtr->markUVWXYZ[2] == false )
			{
				decDataPtr->asciiPtr++;
				decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
				if( DIGIT( *decDataPtr->asciiPtr ) == false )
				{
					return ( ERROR_CODE_UVW );
				}
				else
				{
					decDataPtr->uvwCoordinate[2] = atof( decDataPtr->asciiPtr );
					decDataPtr->markUVWXYZ[2] = true;
					decDataPtr->UVWXYZ = true;
				}
			}
			else
			{
				return ( ERROR_CODE_UVW );
			}
			break;
		}
	}

	decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
	return true;
}

//**********************************************

//**********************************************
int mFunction( DEC_DATA* decDataPtr )
{
	int n;

	decDataPtr->asciiPtr++;
	decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
	
	if( DIGIT( *decDataPtr->asciiPtr ) == false )
	{
		return ( ERROR_CODE_N );
	}
	n = atoi( (const char*)decDataPtr->asciiPtr );
	switch(n)
	{
	case 0:
		if( decDataPtr-> markM00 == false )
		{
			decDataPtr->markM00 = true;
			decDataPtr->lineOutput = true;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
		}
		else
		{
			return ( ERROR_CODE_M );
		}
		break;

	case 1:
		if( decDataPtr-> markM01 == false )
		{
			decDataPtr->markM01 = true;
			decDataPtr->lineOutput = true;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
		}
		else
		{
			return ( ERROR_CODE_M );
		}
		break;

	case 30:
		if( decDataPtr-> markBlockCommand == false )
		{
			decDataPtr->blockCommand = M30_PROGRAM_END;
			decDataPtr->markBlockCommand = true;
			decDataPtr->programend = true;
			decDataPtr->lineOutput = true;
			decDataPtr->motionModal = false;
			decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
		}
		else
		{
			return ( ERROR_CODE_M );
		}
		break;
	}
	return true;
}

//**********************************************

//**********************************************
int fFunction( DEC_DATA* decDataPtr )
{
	if( decDataPtr->markF == true )
		return ( ERROR_CODE_F );
	
	decDataPtr->asciiPtr++;
	decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );
	
	if( DIGIT( *decDataPtr->asciiPtr ) == false )
	{
		return ( ERROR_CODE_F );
	}
	else
	{
		decDataPtr->feedrate = atoi( (const char*)decDataPtr->asciiPtr );
		decDataPtr->markF = true;
		decDataPtr->asciiPtr = passDigit( decDataPtr->asciiPtr );
	}
	return true;
}

//**********************************************

//**********************************************

#define WRITE_M30     9999
#define WRITE_SUCCESS 9998

int endOfLine( DEC_DATA* decDataPtr )
{
	int  i;
	PATH_MOTION* pathMotionPtr;

	pathMotionPtr = &decDataPtr->decToIntpBlock.motionFunction.pathMotion;

	if( decDataPtr->markN == true ) 
	{
		decDataPtr->decToIntpBlock.blockNumber = decDataPtr->blockNumber;
		decDataPtr->markN = false;
	}
	
	if( decDataPtr->lineOutput == false )
	{
		return LINE_EMPTY;
	}
	else if( decDataPtr->markBlockCommand == true || decDataPtr->motionModal == true )
	{
		if( decDataPtr->blockCommand == G04_DWELL_TIME )
		{
			decDataPtr->decToIntpBlock.blockCommand = decDataPtr->blockCommand;
			if( decDataPtr->markF = true )
			{
				if( decDataPtr->feedrate > 0 )
				{
					decDataPtr->decToIntpBlock.motionFunction.rtFunction.dwellTime.value = decDataPtr->feedrate;
					decDataPtr->markF = false;
					decDataPtr->markBlockCommand = false;
				}
				else
				{
					return( ERROR_CODE_F );
				}
			}
			else
			{
				return( ERROR_CODE_G );
			}
		}//g04

		else if( decDataPtr->blockCommand == M30_PROGRAM_END )
		{
			decDataPtr->decToIntpBlock.blockCommand = decDataPtr->blockCommand;
			decDataPtr->decToIntpBlock.motionFunction.rtFunction.m30 = true;
			decDataPtr->markBlockCommand = false;
		}//m30
		
		else if( decDataPtr->blockCommand == G00_MOTION ||
				 decDataPtr->blockCommand == G01_MOTION ||
				 decDataPtr->blockCommand == G02_MOTION ||
				 decDataPtr->blockCommand == G03_MOTION    )
		{
			decDataPtr->decToIntpBlock.blockCommand = decDataPtr->blockCommand;
			decDataPtr->markBlockCommand = false;

			if( decDataPtr->UVWXYZ == true )
			{
				pathMotionPtr->coordinate = decDataPtr->coordinate;

				for( i = 0; i < 3; i++ )
				{
					pathMotionPtr->xyzCoordinate[i] = 0;
					pathMotionPtr->xyzSendValid[i] = false;
					pathMotionPtr->uvwCoordinate[i] = 0;
						pathMotionPtr->uvwSendValid[i] = false;
					if( decDataPtr->coordinate == XYZ_COORDINATE && decDataPtr->markUVWXYZ[i] == true )
					{
						pathMotionPtr->xyzCoordinate[i] = decDataPtr->xyzCoordinate[i];
						pathMotionPtr->xyzSendValid[i] = true;
						decDataPtr->xyzCoordinate[i] = 0;
						decDataPtr->markUVWXYZ[i] = false;
					}
					else if( decDataPtr->coordinate == UVW_COORDINATE && decDataPtr->markUVWXYZ[i] == true )
					{
						pathMotionPtr->uvwCoordinate[i] = decDataPtr->uvwCoordinate[i];
						pathMotionPtr->uvwSendValid[i] = true;
						decDataPtr->uvwCoordinate[i] = 0;
						decDataPtr->markUVWXYZ[i] = false;
					}
				}
				decDataPtr->UVWXYZ = false;
				decDataPtr->coordinate = NULL_COORDINATE;
			}
			else
			{
				return ( ERROR_CODE_COORDINATE );
			}

			if( decDataPtr->blockCommand == G02_MOTION || decDataPtr->blockCommand == G03_MOTION )
			{
				if( decDataPtr->markPlane = true )
				{
					for( i = 0; i < 3; i++ )
					{
						if( decDataPtr->markIJK[i] == true )
						{
							pathMotionPtr->ijkCoordinate[i] = decDataPtr->ijkCoordinate[i];
							pathMotionPtr->ijkSendValid[i] = true;
							decDataPtr->markIJK[i] = false;
						}
					}
					switch( decDataPtr->plane )
					{
					case 17:
						pathMotionPtr->plane = decDataPtr->plane;
						if( pathMotionPtr->ijkSendValid[2] == true )
						{
							return( ERROR_CODE_IJK );
						}

						if( pathMotionPtr->xyzSendValid[2] == true )
						{
							return( ERROR_CODE_XYZ );
						}
						break;

					case 18:
						pathMotionPtr->plane = decDataPtr->plane;
						if( pathMotionPtr->ijkSendValid[0] == true )
						{
							return( ERROR_CODE_IJK );
						}

						if( pathMotionPtr->xyzSendValid[0] == true )
						{
							return( ERROR_CODE_XYZ );
						}
						break;

					case 19:
						pathMotionPtr->plane = decDataPtr->plane;
						if( pathMotionPtr->ijkSendValid[1] == true )
						{
							return( ERROR_CODE_IJK );
						}

						if( pathMotionPtr->xyzSendValid[1] == true )
						{
							return( ERROR_CODE_XYZ );
						}
						break;
					}
				}
				else
				{
					return ( ERROR_CODE_G );
				}
			}//g02g03

			pathMotionPtr->relative = decDataPtr->relative;
			decDataPtr->markRelAbs = false;

			if( decDataPtr->markF == true )
			{
				pathMotionPtr->feedrate = decDataPtr->feedrate;
			}
			else if( decDataPtr->blockCommand == G00_MOTION )
			{
				pathMotionPtr->feedrate = MAX_FEEDRATE;
			}
			else
			{
				pathMotionPtr->feedrate = 500;
			}//feedrate
			decDataPtr->markF = false;

			if( decDataPtr->markG60 == true )
			{
				pathMotionPtr->g60 = true;
				decDataPtr->markG60 = false;
			}//g60
		}
		if( decDataPtr->markM00 == true )
		{
			pathMotionPtr->m00 = true;
			decDataPtr->markM00 = false;
		}//m00
		
		if( decDataPtr->markM01 == true )
		{
			pathMotionPtr->m01 = true;
			decDataPtr->markM01 = false;
		}//m01

	}
	else
	{
		if( decDataPtr->markM00 == true )
		{
			pathMotionPtr->m00 = true;
			decDataPtr->markM00 = false;
		}//m00
		
		if( decDataPtr->markM01 == true )
		{
			pathMotionPtr->m01 = true;
			decDataPtr->markM01 = false;
		}//m01
	}
	

	if( wrFifo((FIFO_HEAD*) &sysLinkDataPtr->decToIntpData.decToIntpFifo,(char*) &decDataPtr->decToIntpBlock) == true )
	{
		for ( ; *decDataPtr->asciiPtr == '\r' || *decDataPtr->asciiPtr == '\n' || *decDataPtr->asciiPtr =='\0' ; )
		{ 
			decDataPtr->asciiPtr++;
		}
		if( decDataPtr->blockCommand == M30_PROGRAM_END )
		{
			return ( WRITE_SUCCESS );
		}
		else
		{
			return ( WRITE_SUCCESS );
		}
	}
	else
	{
		return FIFO_FULL;
	}
		//
		//after write some works to set/clear dec data
		//if command == m30
			//return write_M30
		//else
			//return write_success
	//else
		//return fifo full
	return true;
}

int decWriteFifo()
{
	return true;
}

//**********************************************

//**********************************************
int decIdle( DEC_DATA *decDataPtr )
{
	if( sysLinkDataPtr->sysToDecLinkData.fileValid == true && sysLinkDataPtr->opMode == MEM_MODE )
	{
		strcpy( decDataPtr->fileName, sysLinkDataPtr->sysToDecLinkData.fileName );
		decDataPtr->decState = DEC_OPEN_NC_PROGRAM;
	}
	else if( sysLinkDataPtr->sysToDecLinkData.fileValid == true && sysLinkDataPtr->opMode == MDI_MODE )
	{
		strcpy( decDataPtr->ncBuffer, sysLinkDataPtr->sysToDecLinkData.ncBuffer );
		decDataPtr->asciiPtr = &decDataPtr->ncBuffer[0];
		decDataPtr->decState = DEC_NC_PROGRAM_RUN;
	}
	
	return true;
}

//**********************************************

//**********************************************
int decOpenNcProgram( DEC_DATA *decDataPtr )
{
	decDataPtr->ncFilePtr = fopen( decDataPtr->fileName, "r" );
	if( decDataPtr->ncFilePtr == NULL )
	{
		decDataPtr->decState = DEC_ERROR;
	}
	else
	{
		if( getFileLength( decDataPtr ) < 100000 )
		{
			int i = fread( decDataPtr->ncBuffer,sizeof(char),99999,(FILE *)decDataPtr->ncFilePtr );
			if ( i == 0 )
			{ // 沒讀到東西
				decDataPtr->decState = DEC_ERROR;	
			}
			decDataPtr->asciiPtr = &decDataPtr->ncBuffer[0];
			decDataPtr->decState = DEC_NC_PROGRAM_RUN;
		}
		else
		{
			int location;

			if( decDataPtr->readAt + 1 <= getFileLength( decDataPtr ) )
			{
				fseek( decDataPtr->ncFilePtr, decDataPtr->readAt + 1, SEEK_SET );
				fread( decDataPtr->ncBuffer,sizeof(char),100000,(FILE *)decDataPtr->ncFilePtr );
				decDataPtr->ncBuffer[99999] = '\0';

				for( location = 99998; location > -1; location-- )
				{
					if( decDataPtr->ncBuffer[location] == '\n' || decDataPtr->ncBuffer[location] == '\r' )
					{
						decDataPtr->enterHolder = location;
						break;
					}
					decDataPtr->ncBuffer[location] = ' ';
				}
			
				decDataPtr->readAt += decDataPtr->enterHolder;

				decDataPtr->asciiPtr = &decDataPtr->ncBuffer[0];
				decDataPtr->decState = DEC_NC_PROGRAM_RUN;
			}
			else
			{
				decDataPtr->decState = DEC_CLOSE;
			}
		}
		
	}

	return true;
}

//**********************************************

//**********************************************
int decNcProgramRun( DEC_DATA *decDataPtr )
{
	bool  nextLine = false;
	int   error = 1;
	int   writeResult = 0;

	for( ; ( nextLine == false ) && ( error == 1 ); )
	{
		decDataPtr->asciiPtr = overToken( decDataPtr->asciiPtr );

		switch( *decDataPtr->asciiPtr )
		{
		case 'x':
		case 'y':
		case 'z':
		case 'X':
		case 'Y':
		case 'Z':
			error = coordinateFunction ( decDataPtr );
			break;
		case 'n':
		case 'N':
			error = nFunction ( decDataPtr );
			break;
		case 'g':
		case 'G':
			error = gFunction ( decDataPtr );
			break;
		case '\r':
		case '\n':
		case '\0':
			//特殊控制用字元
			//可先判斷是否為空行再做以下
			writeResult = endOfLine( decDataPtr );
			if ( writeResult == WRITE_SUCCESS )
			{
				if ( decDataPtr->programend == false )
				{
					nextLine = true;
				}
				else
				{
					nextLine = true;
					decDataPtr->decState = DEC_CLOSE;
				}
			}
			else if( writeResult == LINE_EMPTY )
			{
				decDataPtr->asciiPtr++;
				nextLine = true;
			}
			break;

		case 'i':
		case 'I':
		case 'j':
		case 'J':
		case 'k':
		case 'K':
			error = ijkFunction ( decDataPtr );
			break;
		case 'u':
		case 'U':
		case 'v':
		case 'V':
		case 'w':
		case 'W':
			error = uvwFunction ( decDataPtr );
			break;
		case 'm':
		case 'M':
			error = mFunction ( decDataPtr );
			break;
		case 'f':
		case 'F':
			error = fFunction ( decDataPtr );
			break;
		/*default:
			error = unknownCode ( decDataPtr );
			break;*/
		}
	}

	if( error != 1 )
		decDataPtr->decState = DEC_CLOSE;

	nextLine = false;
	return true;
}

//**********************************************

//**********************************************
int decError( DEC_DATA *decDataPtr )
{
	return true;
}

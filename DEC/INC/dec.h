#ifndef DEC_H
#define DEC_H

#include "stdio.h"
#include "..\..\FIFO\INC\fifo.h"

#define DEC_IDLE              0
#define DEC_OPEN_NC_PROGRAM   1
#define DEC_NC_PROGRAM_RUN    2
#define DEC_ERROR             3
#define DEC_CLOSE             4

#define NULL_INTP      0
#define G00_MOTION     1
#define G01_MOTION     2
#define G02_MOTION     3
#define G03_MOTION     4

#define FUNCTION_COMMAND    100
#define G04_DWELL_TIME      101
#define G0_REFERENCE_POINT  102
#define M30_PROGRAM_END     999

#define XY_PLANE       17
#define YZ_PLANE       18
#define ZX_PLANE       19

#define MAX_FEEDRATE   1000
#define DEFAULT_FEEDRATE 500

#define NULL_COORDINATE 9999
#define XYZ_COORDINATE  9998
#define UVW_COORDINATE  9997

typedef struct 
{
	int     decState;

	char    fileName[100];
	FILE    *ncFilePtr;
	char    ncBuffer[100000];
	int     enterHolder;//my
	int     readAt;//my


	char    *asciiPtr;
	int     blockNumber;
	int     blockCommand;

	double  xyzCoordinate[3];
	double  ijkCoordinate[3];
	double  uvwCoordinate[3];

	bool    relative;//my 是否為相對座標
	int     plane;
	int     feedrate;
	int     coordinate;
	bool    programend;

	bool    lineOutput;//判斷行是否有效
	bool	motionModal;
	bool    markN;
	bool    markBlockCommand;
	bool    markRelAbs;//my
	bool    markUVWXYZ[3];
	bool    UVWXYZ;
	bool    markPlane;
	bool    markIJK[3];
	bool    markF;
	bool    markM00;
	bool    markM01;
	bool    markG60;

	char    block;

	PATH_BLOCK  decToIntpBlock;

} DEC_DATA;


enum DEC_ERROR_CODE 
{
	OPEN_FILE = -1000,
	EMPTY_FILE,
	UNKNOWN_CODE,
	ERROR_CODE_N,
	ERROR_CODE_G,
	ERROR_CODE_F,
	ERROR_CODE_M,
	ERROR_CODE_T,
	ERROR_CODE_D,
	ERROR_CODE_XYZ,
	ERROR_CODE_IJK,
	ERROR_CODE_UVW,
	ERROR_CODE_COORDINATE,
	ERROR_CODE_G04,
	LINE_EMPTY,
	FIFO_FULL
};


int decInit( DEC_DATA *decDataPtr );
int decMain( DEC_DATA *decDataPtr );
int decClose( DEC_DATA *decDataPtr );
int decReste( DEC_DATA *decDataPtr );

int getFileLength ( DEC_DATA *decDataPtr);
char *overToken( char *inPtr );
char* passDigit( char* inPtr );

int nFunction( DEC_DATA* decDataPtr );
int gFunction( DEC_DATA* decDataPtr );
int iFunction( DEC_DATA* decDataPtr );
int jFunction( DEC_DATA* decDataPtr );
int kFunction( DEC_DATA* decDataPtr );
int mFunction( DEC_DATA* decDataPtr );
int fFunction( DEC_DATA* decDataPtr );
int coordinateFunction( DEC_DATA* decDataPtr );
int endOfLine( DEC_DATA* decDataPtr );
int decWriteFifo();

int decIdle( DEC_DATA *decDataPtr );
int decOpenNcProgram( DEC_DATA *decDataPtr );
int decNcProgramRun( DEC_DATA *decDataPtr );
int decReset( DEC_DATA *decDataPtr );
int decError( DEC_DATA *decDataPtr );




#endif
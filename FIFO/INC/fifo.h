#ifndef FIFO_H
#define FIFO_H

#include "stdio.h"

typedef struct
{
	int  feedrate;
	bool   relative;
	bool   m00;
	bool   m01;
	bool   g60;

	double xyzCoordinate[3];
	double uvwCoordinate[3];
	double ijkCoordinate[3];
	bool   xyzSendValid[3];//決定送進來的值是否有效
	bool   uvwSendValid[3];
	bool   ijkSendValid[3];
	int    coordinate;
	int    plane;
	//EXTRA  extra;//給G02G03的
} PATH_MOTION;

typedef struct
{
	int  value;
}DWELL_TIME;

typedef struct
{
	DWELL_TIME  dwellTime;
	bool        m30;
}RT_FUNCTION;//real time funciton

typedef union
{
	PATH_MOTION  pathMotion;
	RT_FUNCTION  rtFunction;
} PATH_MOTION_FUNCTION;

typedef struct
{
	int  blockNumber;//行號
	int  blockCommand;//行指令
	PATH_MOTION_FUNCTION  motionFunction; 
}PATH_BLOCK;

//**************************************************

//block type
#define F_DEC_TO_INTP_BLOCK 1
#define F_XXX_TO_XXX_BLOCK  2
typedef struct
{
	int wrCounter;
	int rdCounter;
	int wrIndex;
	int rdIndex;
	int blockLength;//block大小
	int blockType;//fifo的type

} FIFO_HEAD;

#define DEC_TO_INTP_FIFO_LNG 100
#define SYS_TO_INTP_FIFO_LNG 100

typedef struct
{
	FIFO_HEAD   head;
	PATH_BLOCK  block[DEC_TO_INTP_FIFO_LNG];
} DEC_TO_INTP_FIFO;

typedef struct
{
	FIFO_HEAD   head;
	PATH_BLOCK  block[SYS_TO_INTP_FIFO_LNG];
} SYS_TO_INTP_FIFO;


#define FULL  100
#define EMPTY 200

int initFifo( FIFO_HEAD *fifoPtr, int type, int length );//type and length init, reset counter and index to zero
int resetFifo( FIFO_HEAD *fifoPtr );//reset counter and indexto zero
int wrFifo( FIFO_HEAD *headPtr, char *blockPtr );
int rdFifo( FIFO_HEAD *headPtr, char *blockPtr );
int testFifoFull( FIFO_HEAD *fifoPtr );
int testFifoEmpty( FIFO_HEAD *fifoPtr );


#endif
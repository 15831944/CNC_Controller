#include "stdafx.h"
#include "..\INC\fifo.h"
#include "..\..\DEC\INC\dec.h"


//**********************************************

//**********************************************
int initFifo( FIFO_HEAD *headPtr, int type, int length )
{
	headPtr->rdCounter = 0;
	headPtr->rdIndex = 0;
	headPtr->wrCounter = 0;
	headPtr->wrIndex = 0;
	headPtr->blockLength = length;
	headPtr->blockType = type;
	return true;
}

//**********************************************

//**********************************************
int resetFifo( FIFO_HEAD *headPtr )
{
	headPtr->rdCounter = 0;
	headPtr->rdIndex = 0;
	headPtr->wrCounter = 0;
	headPtr->wrIndex = 0;
	return true;
}

//**********************************************

//**********************************************
int wrFifo( FIFO_HEAD *headPtr, char *blockPtr )
{
	if( headPtr->blockType = F_DEC_TO_INTP_BLOCK )
	{
		headPtr->blockLength = sizeof( *blockPtr );
		headPtr->wrIndex %= DEC_TO_INTP_FIFO_LNG;
		
		if( headPtr->wrCounter - headPtr->rdCounter < DEC_TO_INTP_FIFO_LNG )
		{  
			((DEC_TO_INTP_FIFO*) headPtr)->block[headPtr->wrIndex] = *((PATH_BLOCK*) blockPtr);
			headPtr->wrCounter++;
			headPtr->wrIndex++;
			return true;
		}
  
		else
		{
			return FULL;
		}
	}
}

//**********************************************

//**********************************************
int rdFifo( FIFO_HEAD *headPtr, char *blockPtr )
{
	if( headPtr->blockType = F_DEC_TO_INTP_BLOCK )
	{
		headPtr->blockLength = sizeof( *blockPtr );
		headPtr->rdIndex %= DEC_TO_INTP_FIFO_LNG;
		
		if( headPtr->wrCounter > headPtr->rdCounter )
		{  
			*((PATH_BLOCK*) blockPtr) = ((DEC_TO_INTP_FIFO*) headPtr)->block[headPtr->rdIndex];
			headPtr->rdCounter++;
			headPtr->rdIndex++;
			return true;
		}
  
		else
		{
			return EMPTY;
		}
	}
}

//**********************************************

//**********************************************
int testFifoFull( FIFO_HEAD *headPtr )
{
	if( headPtr->blockType = F_DEC_TO_INTP_BLOCK )
	{
		if( headPtr->wrCounter - headPtr->rdCounter == DEC_TO_INTP_FIFO_LNG )
		{
			return true;
		}
	}
}

//**********************************************

//**********************************************
int testFifoEmpty( FIFO_HEAD *headPtr )
{
	if( headPtr->wrCounter = headPtr->rdCounter )
	{
		return true;
	}
}

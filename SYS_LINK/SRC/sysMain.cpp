#include "stdafx.h"
#include "..\INC\sys.h"

SYS_DATA	sysData;
SYS_DATA	*sysDataPtr = &sysData;

//**********************************************

//**********************************************
int sysInit( SYS_DATA *sysDataPtr )
{
	sysDataPtr->sysState = SYS_IDLE;
	sysDataPtr->memState = MEM_START;
	sysDataPtr->jogState = JOG_START;
	sysDataPtr->mdiState = MDI_START;
	sysDataPtr->hwState  = HW_START;
	sysDataPtr->fileValid = false;
}

//**********************************************

//**********************************************
int sysReset( SYS_DATA *sysDataPtr )
{
	sysDataPtr->sysState = SYS_IDLE;
	sysDataPtr->fileValid = false;
}

//**********************************************

//**********************************************
int memStart( SYS_DATA *sysDataPtr )
{
	//if file input, save file name and set fileValid
	//if cycle start and file valid, change to sent nc program
	sysDataPtr->memState = MEM_SEND_NC_FILE;
}

//**********************************************

//**********************************************
int menSendNcFile( SYS_DATA *sysDataPtr )
{
	sysDataPtr->memState = MEM_NC_RUNNING;
}

//**********************************************

//**********************************************
int memNcRunning( SYS_DATA *sysDataPtr )
{
}

//**********************************************

//**********************************************
int sysMemMode( sysDataPtr )
{
	switch( sysDataPtr->sysState )
	{
	case MEM_START:
		memStart( sysDataPtr );
		break;

	case MEM_SEND_NC_FILE:
		memSendNcFile( sysDataPtr );
		break;

	case MEM_NC_RUNNING:
		memNcRunning( sysDataPtr );
		break;
	}
}


//**********************************************

//**********************************************
int sysMain( SYS_DATA *sysDataPtr )
{
	// getting info from MMI and other
	//change sys state according to inputs

	switch( sysDataPtr->sysState )
	{
	case SYS_IDLE:
		sysIdle( sysDataPtr );
		break;

	case SYS_MEM_MODE:
		sysMemMode( sysDataPtr );
		break;

	case SYS_JOG_MODE:
		sysJogMode( sysDataPtr );
		break;

	case SYS_MDI_MODE:
		sysMdiMode( sysDataPtr );
		break;

	case SYS_HW_MODE:
		sysHwMode( sysDataPtr );
		break;
	}
}

//**********************************************

//**********************************************
int sysClose( SYS_DATA *sysDataPtr )
{
}
#include "stdafx.h"
#include "..\INC\sysLink.h"

//extern SYS_LINK_DATA   *sysLinkDataPtr;

//**********************************************

//**********************************************
int sysLinkInit( SYS_LINK_DATA *sysLinkDataPtr )
{
	sysLinkDataPtr->sysToDecLinkData.fileValid = false;
	sysLinkDataPtr->cyclingTime = 0.033;

	sysLinkDataPtr->pannelInput.cycleStart = false;
	sysLinkDataPtr->pannelInput.feedHold = false;
	sysLinkDataPtr->pannelInput.emStop = false;
	sysLinkDataPtr->pannelInput.reset = false;

	sysLinkDataPtr->pannelOutput.m30 = false;

	sysLinkDataPtr->intpToSysData.newSettingValueUVW[0] = 90;
	sysLinkDataPtr->intpToSysData.newSettingValueUVW[1] = 180;
	sysLinkDataPtr->intpToSysData.newSettingValueUVW[2] = 100;
	sysLinkDataPtr->intpToSysData.newSettingValue[2] = 100;

	return true;
}

//**********************************************

//**********************************************
int sysLinkReset( SYS_LINK_DATA *sysLinkDataPtr )
{
	int i;

	sysLinkDataPtr->cyclingTime = 0.033;

	sysLinkDataPtr->pannelInput.cycleStart = false;
	sysLinkDataPtr->pannelInput.feedHold = false;
	sysLinkDataPtr->pannelInput.emStop = false;
	sysLinkDataPtr->pannelInput.reset = false;

	sysLinkDataPtr->pannelOutput.m30 = false;

	for( i = 0; i < 3; i++ )
	{
		sysLinkDataPtr->pannelInput.coordiPlus[i] = false;
		sysLinkDataPtr->pannelInput.coordiMinu[i] = false;
	}

	resetFifo( (FIFO_HEAD*) &sysLinkDataPtr->sysToIntpData.sysToIntpFifo );
	resetFifo( (FIFO_HEAD*) &sysLinkDataPtr->decToIntpData.decToIntpFifo );
	return true;
}
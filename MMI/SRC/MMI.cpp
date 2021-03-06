#include "stdafx.h"
#include "..\INC\MMI.h"
#include "..\..\SYS_LINK\INC\sysLink.h"

extern SYS_LINK_DATA   *sysLinkDataPtr;

int mmiInit( MMI_DATA* mmiDataPtr )
{
	mmiDataPtr->counter       = 0;
	mmiDataPtr->cycleStart    = false;
	mmiDataPtr->feedOverride  = 100;
	mmiDataPtr->handWheelGain = 0;
	mmiDataPtr->opMode        = MEM_MODE;
	mmiDataPtr->xyzMode       = true;
	mmiDataPtr->reset = false;
	mmiDataPtr->record = false;
	mmiDataPtr->teachIn = false;

	return true;
}

int mmiReset( MMI_DATA* mmiDataPtr )
{
	int i;

	mmiDataPtr->counter       = 0;
	mmiDataPtr->cycleStart    = false;
	mmiDataPtr->feedOverride  = 100;
	mmiDataPtr->handWheelGain = 0;
	mmiDataPtr->xyzMode       = true;
	mmiDataPtr->reset = false;
	mmiDataPtr->feedHold = false;

	for( i = 0; i < 3; i++ )
	{
		mmiDataPtr->coordiMinu[i] = false;
		mmiDataPtr->coordiPlus[i] = false;
	}

	return true;
}

int mmiMain( MMI_DATA* mmiDataPtr )
{
	if( mmiDataPtr->reset == true )
	{
		sysLinkReset( sysLinkDataPtr );
		sysLinkDataPtr->pannelInput.reset = true;
		mmiReset( mmiDataPtr );
	}

	if( mmiDataPtr->feedHold == true )
		sysLinkDataPtr->pannelInput.feedHold = true;
	else
		sysLinkDataPtr->pannelInput.feedHold = false;

	if( sysLinkDataPtr->pannelOutput.m30 == true )
	{
		mmiDataPtr->cycleStart = false;
	}

	if( mmiDataPtr->feedChange == true )
	{
		sysLinkDataPtr->sysToIntpData.feedChange = true;
		sysLinkDataPtr->sysToIntpData.feedOverride = mmiDataPtr->feedOverride;
		mmiDataPtr->feedChange = false;
	}

	switch( mmiDataPtr->opMode )
	{
	case MEM_MODE:
		if( mmiDataPtr->cycleStart == true )
		{
			sysLinkDataPtr->pannelInput.cycleStart = true;
		}

		break;

	case JOG_MODE:
		int i;

		sysLinkDataPtr->pannelInput.xyzMode = mmiDataPtr->xyzMode;

		for( i = 0; i < 3; i++ )
		{
			if( mmiDataPtr->coordiPlus[i] == true || mmiDataPtr->coordiMinu[i] == true )
			{
				sysLinkDataPtr->pannelInput.coordiPlus[i] = mmiDataPtr->coordiPlus[i];
				sysLinkDataPtr->pannelInput.coordiMinu[i] = mmiDataPtr->coordiMinu[i];
			}
			else
			{
				sysLinkDataPtr->pannelInput.coordiPlus[i] = false;
				sysLinkDataPtr->pannelInput.coordiMinu[i] = false;
			}
		}

		break;

	case MDI_MODE:
		if( mmiDataPtr->cycleStart == true )
		{
			sysLinkDataPtr->pannelInput.cycleStart = true;
		}
		break;

	case HOME_MODE:
		if( mmiDataPtr->cycleStart == true )
		{
			sysLinkDataPtr->pannelInput.cycleStart = true;
		}
		break;

	case WHEEL_MODE:

		if( sysLinkDataPtr->pannelOutput.m30 == true )
		{
			mmiDataPtr->handWheelGain = 0;
			sysLinkDataPtr->pannelOutput.m30 = false;
			break;
		}

		sysLinkDataPtr->pannelInput.xyzMode = mmiDataPtr->xyzMode;

		for( i = 0; i < 3; i++ )
		{
			if( mmiDataPtr->coordiPlus[i] == true || mmiDataPtr->coordiMinu[i] == true )
			{
				if( mmiDataPtr->handWheelGain != 0 )
				{
					sysLinkDataPtr->pannelInput.cycleStart = true;
					sysLinkDataPtr->pannelInput.handWheelGain = mmiDataPtr->handWheelGain;
				}
				sysLinkDataPtr->pannelInput.coordiPlus[i] = mmiDataPtr->coordiPlus[i];
				sysLinkDataPtr->pannelInput.coordiMinu[i] = mmiDataPtr->coordiMinu[i];
			}
			else
			{
				sysLinkDataPtr->pannelInput.coordiPlus[i] = false;
				sysLinkDataPtr->pannelInput.coordiMinu[i] = false;
			}
		}

		
		break;
	}

	return true;
}
//if( mmiDataPtr->cycleStart == true)
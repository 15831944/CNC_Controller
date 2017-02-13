#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "math.h" 
#include "..\INC\sys.h"
#include "..\..\SYS_LINK\INC\sysLink.h"
#include "..\..\MMI\INC\MMI.h"

extern SYS_LINK_DATA	*sysLinkDataPtr;
extern MMI_DATA			*mmiDataPtr;
//extern SYS_DATA			*sysDataPtr;

//**********************************************

//**********************************************
int sysInit( SYS_DATA *sysDataPtr )
{
	int i;

	sysDataPtr->sysState = SYS_IDLE;
	sysDataPtr->memState = MEM_START;
	sysDataPtr->jogState = JOG_START;
	sysDataPtr->mdiState = MDI_START;
	sysDataPtr->whState  = WH_START;
	sysDataPtr->hmState  = HM_START;
	sysDataPtr->fileValid = false;
	sysDataPtr->axisInitValue[0] = 90;
	sysDataPtr->axisInitValue[1] = 180;
	sysDataPtr->axisInitValue[2] = 100.0;

	
	for ( i = 0 ; i < 3 ; i++ )
	{
		sysDataPtr->axisData[i].mSetValue = sysDataPtr->axisInitValue[i];
		sysDataPtr->axisData[i].mActValue = sysDataPtr->axisInitValue[i];
	}
	sysDataPtr->axisData[0].resolution = 0.0018;// 360(degree) / 200000(increment)
	sysDataPtr->axisData[1].resolution = 0.0018;
	sysDataPtr->axisData[2].resolution = 0.0025;// 200(mm) / 80000(increment)
	

	return true;
}

//**********************************************

//**********************************************
int sysIdle( SYS_DATA *sysDataPtr )
{
	return true;
}

//**********************************************

//**********************************************
int sysReset( SYS_DATA *sysDataPtr )
{
	sysDataPtr->sysState = SYS_IDLE;
	sysDataPtr->memState = MEM_START;
	sysDataPtr->jogState = JOG_START;
	sysDataPtr->mdiState = MDI_START;
	sysDataPtr->whState  = WH_START;
	sysDataPtr->hmState  = HM_START;
	sysDataPtr->fileValid = false;
	return true;
}

//**********************************************

//**********************************************
int memStart( SYS_DATA *sysDataPtr )
{
	//if file input, save file name and set fileValid
	//if cycle start and file valid, change to sent nc program
	if ( sysLinkDataPtr->sysToDecLinkData.fileValid == false && sysLinkDataPtr->pannelInput.cycleStart == true )
	{
		strcpy( sysLinkDataPtr->sysToDecLinkData.fileName, sysDataPtr->fileName );
		sysLinkDataPtr->sysToDecLinkData.fileValid = true; //等到執行結束才改成false
		sysDataPtr->memState = MEM_SEND_NC_FILE;
	}
	
	return true;
}

//**********************************************

//**********************************************
int memSendNcFile( SYS_DATA *sysDataPtr )
{
	sysDataPtr->memState = MEM_NC_RUNNING;
	return true;
}

//**********************************************

//**********************************************
int memNcRunning( SYS_DATA *sysDataPtr )
{
	if( sysLinkDataPtr->intpToSysData.m30 == true )
	{
		sysDataPtr->memState = MEM_START;
		sysLinkDataPtr->pannelInput.cycleStart = false;
		sysLinkDataPtr->pannelOutput.m30 =true;
		sysLinkDataPtr->intpToSysData.m30 = false;
	}
	return true;
}

//**********************************************

//**********************************************
int sysMemMode( SYS_DATA *sysDataPtr )
{
	switch( sysDataPtr->memState )
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
	return true;
}

//**********************************************

//**********************************************
int jogStart( SYS_DATA *sysDataPtr )
{
	int i;
	for( i = 0; i < 3; i++ )
	{
		if( sysLinkDataPtr->pannelInput.coordiPlus[i] == true ||sysLinkDataPtr->pannelInput.coordiMinu[i] == true )
		{
			sysDataPtr->jogState = JOG_WRITE_FIFO;
		}
	}
		
	return true;
}

//**********************************************

//**********************************************
int jogWriteFifo( SYS_DATA *sysDataPtr )
{
	int i;

	PATH_MOTION* pathMotionPtr;
	pathMotionPtr = &sysDataPtr->sysToIntpBlock.motionFunction.pathMotion;

	sysDataPtr->sysToIntpBlock.blockCommand = G00_MOTION;
	pathMotionPtr->m00 = false;
	pathMotionPtr->m01 = false;
	pathMotionPtr->relative = false;
	
	if( sysLinkDataPtr->pannelInput.xyzMode == true )
	{
		pathMotionPtr->coordinate = XYZ_COORDINATE;

		if( sysLinkDataPtr->pannelInput.coordiPlus[0] == true )
		{
			if( sqrt( 150 * 150 - sysLinkDataPtr->intpToSysData.newSettingValue[1] * sysLinkDataPtr->intpToSysData.newSettingValue[1] ) != 0 )
			{
				pathMotionPtr->xyzSendValid[0] = true;
				pathMotionPtr->xyzCoordinate[0] = sqrt( 150 * 150 - sysLinkDataPtr->intpToSysData.newSettingValue[1] * sysLinkDataPtr->intpToSysData.newSettingValue[1] );
			}
			else
			{
				sysDataPtr->jogState = JOG_RUNNING;
				return true;
			}
		}
		else if( sysLinkDataPtr->pannelInput.coordiMinu[0] == true )
		{
			if( sqrt( 150 * 150 - sysLinkDataPtr->intpToSysData.newSettingValue[1] * sysLinkDataPtr->intpToSysData.newSettingValue[1] ) != 0 )
			{
				pathMotionPtr->xyzSendValid[0] = true;
				pathMotionPtr->xyzCoordinate[0] = -sqrt( 150 * 150 - sysLinkDataPtr->intpToSysData.newSettingValue[1] * sysLinkDataPtr->intpToSysData.newSettingValue[1] );
			}
			else
			{
				sysDataPtr->jogState = JOG_RUNNING;
				return true;
			}
		}
		else
			pathMotionPtr->xyzSendValid[0] = false;

		if( sysLinkDataPtr->pannelInput.coordiPlus[1] == true )
		{
			if( sqrt( 150 * 150 - sysLinkDataPtr->intpToSysData.newSettingValue[0] * sysLinkDataPtr->intpToSysData.newSettingValue[0] ) != 0 )
			{
				pathMotionPtr->xyzSendValid[1] = true;
				pathMotionPtr->xyzCoordinate[1] = sqrt( 150 * 150 - sysLinkDataPtr->intpToSysData.newSettingValue[0] * sysLinkDataPtr->intpToSysData.newSettingValue[0] );
			}
			else
			{
				sysDataPtr->jogState = JOG_RUNNING;
				return true;
			}
		}
		else if( sysLinkDataPtr->pannelInput.coordiMinu[1] == true )
		{
			if( sqrt( 150 * 150 - sysLinkDataPtr->intpToSysData.newSettingValue[0] * sysLinkDataPtr->intpToSysData.newSettingValue[0] ) != 0 )
			{
				pathMotionPtr->xyzSendValid[1] = true;
				pathMotionPtr->xyzCoordinate[1] = -sqrt( 150 * 150 - sysLinkDataPtr->intpToSysData.newSettingValue[0] * sysLinkDataPtr->intpToSysData.newSettingValue[0] );
			}
			else
			{
				sysDataPtr->jogState = JOG_RUNNING;
				return true;
			}
		}
		else
			pathMotionPtr->xyzSendValid[1] = false;

		if( sysLinkDataPtr->pannelInput.coordiPlus[2] == true )
		{
			if( sysDataPtr->axisData[2].mActValue != 200 )
			{
				pathMotionPtr->xyzSendValid[2] = true;
				pathMotionPtr->xyzCoordinate[2] = 200;
			}
			else
			{
				sysDataPtr->jogState = JOG_RUNNING;
				return true;
			}
		}
		else if( sysLinkDataPtr->pannelInput.coordiMinu[2] == true )
		{
			if(  sysDataPtr->axisData[2].mActValue != 0 )
			{
				pathMotionPtr->xyzSendValid[2] = true;
				pathMotionPtr->xyzCoordinate[2] = 0;
			}
			else
			{
				sysDataPtr->jogState = JOG_RUNNING;
				return true;
			}
		}
		else
			pathMotionPtr->xyzSendValid[2] = false;

	}
	else
	{
		pathMotionPtr->coordinate = UVW_COORDINATE;

		for( i = 0; i < 2; i++ )
		{
			if( sysLinkDataPtr->pannelInput.coordiPlus[i] == true )
			{
				pathMotionPtr->relative = true;
				pathMotionPtr->uvwSendValid[i] = true;
				pathMotionPtr->uvwCoordinate[i] = 360;
			}
			else if( sysLinkDataPtr->pannelInput.coordiMinu[i] == true )
			{
				pathMotionPtr->relative = false;
				pathMotionPtr->uvwSendValid[i] = true;
				pathMotionPtr->uvwCoordinate[i] = -360;
			}
			else
			{
				pathMotionPtr->uvwSendValid[i] = false;
			}
		}

		if( sysLinkDataPtr->pannelInput.coordiPlus[2] == true )
			{
				pathMotionPtr->uvwSendValid[2] = true;
				pathMotionPtr->uvwCoordinate[2] = 200;
			}
			else if( sysLinkDataPtr->pannelInput.coordiMinu[i] == true )
			{
				pathMotionPtr->uvwSendValid[2] = true;
				pathMotionPtr->uvwCoordinate[2] = 0;
			}
			else
			{
				pathMotionPtr->uvwSendValid[2] = false;
			}
	}

	if( wrFifo((FIFO_HEAD*) &sysLinkDataPtr->sysToIntpData.sysToIntpFifo,(char*) &sysDataPtr->sysToIntpBlock) == true )
	{
		sysDataPtr->jogState = JOG_RUNNING;
		return ( WRITE_SUCCESS );
	}
	else
	{
		return FIFO_FULL;
	}
}

//**********************************************

//**********************************************
int jogRunning( SYS_DATA *sysDataPtr )
{
	if( sysLinkDataPtr->pannelInput.feedHold == true )
		sysDataPtr->jogState = JOG_START;
	return true;
}

//**********************************************

//**********************************************
int sysJogMode( SYS_DATA *sysDataPtr )
{
	switch( sysDataPtr->jogState )
	{
	case JOG_START:
		jogStart( sysDataPtr );
		break;

	case JOG_WRITE_FIFO:
		jogWriteFifo( sysDataPtr );
		break;

	case JOG_RUNNING:
		jogRunning( sysDataPtr );
		break;
	}
	return true;
}

//**********************************************

//**********************************************
int mdiStart( SYS_DATA *sysDataPtr )
{
	//if file input, save file name and set fileValid
	//if cycle start and file valid, change to sent nc program
	if ( sysLinkDataPtr->sysToDecLinkData.fileValid == false && sysLinkDataPtr->pannelInput.cycleStart == true )
	{
		strcpy( sysLinkDataPtr->sysToDecLinkData.ncBuffer, sysDataPtr->ncBuffer );
		sysLinkDataPtr->sysToDecLinkData.fileValid = true; //等到執行結束才改成false
		sysDataPtr->mdiState = MDI_SEND_NC_FILE;
	}
	
	return true;
}

//**********************************************

//**********************************************
int mdiSendNcFile( SYS_DATA *sysDataPtr )
{
	sysDataPtr->mdiState = MDI_NC_RUNNING;
	return true;
}

//**********************************************

//**********************************************
int mdiNcRunning( SYS_DATA *sysDataPtr )
{
	if( sysLinkDataPtr->intpToSysData.m30 == true )
	{
		sysDataPtr->mdiState = MDI_START;
		sysLinkDataPtr->pannelInput.cycleStart = false;
		sysLinkDataPtr->pannelOutput.m30 =true;
		sysLinkDataPtr->intpToSysData.m30 = false;
	}
	return true;
}

//**********************************************

//**********************************************
int sysMdiMode( SYS_DATA *sysDataPtr )
{
	switch( sysDataPtr->mdiState )
	{
	case MDI_START:
		mdiStart( sysDataPtr );
		break;

	case MDI_SEND_NC_FILE:
		mdiSendNcFile( sysDataPtr );
		break;

	case MDI_NC_RUNNING:
		mdiNcRunning( sysDataPtr );
		break;
	}

	return true;
}

//**********************************************

//**********************************************
int whStart( SYS_DATA *sysDataPtr )
{
	int i;
	for( i = 0; i < 3; i++ )
	{
		if( ( sysLinkDataPtr->pannelInput.coordiPlus[i] == true ||sysLinkDataPtr->pannelInput.coordiMinu[i] == true ) && sysLinkDataPtr->pannelInput.handWheelGain != 0 )
		{
			sysDataPtr->whState = WH_WRITE_FIFO;
		}
	}
		
	return true;
}

//**********************************************

//**********************************************
int whWriteFifo( SYS_DATA *sysDataPtr )
{
	int i;

	PATH_MOTION* pathMotionPtr;
	pathMotionPtr = &sysDataPtr->sysToIntpBlock.motionFunction.pathMotion;

	sysDataPtr->sysToIntpBlock.blockCommand = G00_MOTION;
	pathMotionPtr->m00 = false;
	pathMotionPtr->m01 = false;
	pathMotionPtr->relative = true;
	
	if( sysLinkDataPtr->pannelInput.xyzMode == true )
	{
		pathMotionPtr->coordinate = XYZ_COORDINATE;

		for( i = 0; i < 3; i++ )
		{
			if( sysLinkDataPtr->pannelInput.coordiPlus[i] == true )
			{
				pathMotionPtr->xyzSendValid[i] = true;
				pathMotionPtr->xyzCoordinate[i] = sysLinkDataPtr->pannelInput.handWheelGain;
			}
			else if( sysLinkDataPtr->pannelInput.coordiMinu[i] == true )
			{
				pathMotionPtr->xyzSendValid[i] = true;
				pathMotionPtr->xyzCoordinate[i] = -sysLinkDataPtr->pannelInput.handWheelGain;
			}
			else
			{
				pathMotionPtr->xyzSendValid[i] = false;
			}
		}

	}
	else
	{
		pathMotionPtr->coordinate = UVW_COORDINATE;

		for( i = 0; i < 3; i++ )
		{
			if( sysLinkDataPtr->pannelInput.coordiPlus[i] == true )
			{
				pathMotionPtr->uvwSendValid[i] = true;
				pathMotionPtr->uvwCoordinate[i] = sysLinkDataPtr->pannelInput.handWheelGain;
			}
			else if( sysLinkDataPtr->pannelInput.coordiMinu[i] == true )
			{
				pathMotionPtr->uvwSendValid[i] = true;
				pathMotionPtr->uvwCoordinate[i] = -sysLinkDataPtr->pannelInput.handWheelGain;
			}
			else
			{
				pathMotionPtr->uvwSendValid[i] = false;
			}
		}

	}

	if( wrFifo((FIFO_HEAD*) &sysLinkDataPtr->sysToIntpData.sysToIntpFifo,(char*) &sysDataPtr->sysToIntpBlock) == true )
	{
		sysDataPtr->sysToIntpBlock.blockCommand = M30_PROGRAM_END;
		if( wrFifo((FIFO_HEAD*) &sysLinkDataPtr->sysToIntpData.sysToIntpFifo,(char*) &sysDataPtr->sysToIntpBlock) == true )
		{
			sysDataPtr->whState = WH_RUNNING;
			return ( WRITE_SUCCESS );
		}
	}
	else
	{
		return FIFO_FULL;
	}
}

//**********************************************

//**********************************************
int whRunning( SYS_DATA *sysDataPtr )
{
	if( sysLinkDataPtr->intpToSysData.m30 == true )
	{
		sysDataPtr->whState = WH_START;
		sysLinkDataPtr->pannelInput.cycleStart = false;
		sysLinkDataPtr->intpToSysData.m30 = false;
		sysLinkDataPtr->pannelInput.handWheelGain = 0;
		sysLinkDataPtr->pannelOutput.m30 = true;
		
	}

	return true;
}

//**********************************************

//**********************************************
int sysWhMode( SYS_DATA *sysDataPtr )
{
	switch( sysDataPtr->whState )
	{
	case WH_START:
		whStart( sysDataPtr );
		break;

	case WH_WRITE_FIFO:
		whWriteFifo( sysDataPtr );
		break;

	case WH_RUNNING:
		whRunning( sysDataPtr );
		break;
	}
	
	return true;
}

//**********************************************

//**********************************************
int hmStart( SYS_DATA *sysDataPtr )
{
	if( sysLinkDataPtr->pannelInput.cycleStart == true )
		sysDataPtr->hmState = HM_WRITE_FIFO;
	return true;
}

//**********************************************

//**********************************************
int hmWriteFifo( SYS_DATA *sysDataPtr )
{
	int i;

	PATH_MOTION* pathMotionPtr;
	pathMotionPtr = &sysDataPtr->sysToIntpBlock.motionFunction.pathMotion;

	sysDataPtr->sysToIntpBlock.blockCommand = G00_MOTION;
	pathMotionPtr->m00 = false;
	pathMotionPtr->m01 = false;
	pathMotionPtr->relative = false;
	pathMotionPtr->coordinate = UVW_COORDINATE;
	pathMotionPtr->uvwCoordinate[0] = 90;
	pathMotionPtr->uvwCoordinate[1] = 180;
	pathMotionPtr->uvwCoordinate[2] = 100;

	for( i = 0; i < 3; i++ )
	{
		pathMotionPtr->uvwSendValid[i] = true;
	}

	if( wrFifo((FIFO_HEAD*) &sysLinkDataPtr->sysToIntpData.sysToIntpFifo,(char*) &sysDataPtr->sysToIntpBlock) == true )
	{
		sysDataPtr->sysToIntpBlock.blockCommand = M30_PROGRAM_END;
		if( wrFifo((FIFO_HEAD*) &sysLinkDataPtr->sysToIntpData.sysToIntpFifo,(char*) &sysDataPtr->sysToIntpBlock) == true )
		{
			sysDataPtr->hmState = HM_CLOSE;
			return ( WRITE_SUCCESS );
		}
	}
	else
	{
		return FIFO_FULL;
	}
}

//**********************************************

//**********************************************
int hmClose( SYS_DATA *sysDataPtr )
{
	if( sysLinkDataPtr->intpToSysData.m30 == true )
	{
		sysDataPtr->hmState = HM_START;
		sysLinkDataPtr->pannelInput.cycleStart = false;
		sysLinkDataPtr->pannelOutput.m30 =true;
		sysLinkDataPtr->intpToSysData.m30 = false;
		
	}

	return true;
}

//**********************************************

//**********************************************
int sysHmMode( SYS_DATA *sysDataPtr )
{
	switch( sysDataPtr->hmState )
	{
	case HM_START:
		hmStart( sysDataPtr );
		break;

	case HM_WRITE_FIFO:
		hmWriteFifo( sysDataPtr );
		break;

	case HM_CLOSE:
		hmClose( sysDataPtr );
		break;
	}
	return true;
}

//**********************************************

//**********************************************
int sysMain( SYS_DATA *sysDataPtr )
{
	// getting info from MMI and other
	//change sys state according to inputs

	if( sysLinkDataPtr->pannelInput.reset == true )
		sysReset( sysDataPtr );

	sysDataPtr->sysState = mmiDataPtr->opMode;
	sysLinkDataPtr->opMode = sysDataPtr->sysState;

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

	case SYS_WHEEL_MODE:
		sysWhMode( sysDataPtr );
		break;

	case SYS_HOME_MODE:
		sysHmMode( sysDataPtr );
		break;
	}
	return true;
}

//**********************************************

//**********************************************
int sysClose( SYS_DATA *sysDataPtr )
{
	return true;
}

//**********************************************

//**********************************************
int realKnl( SYS_DATA *sysDataPtr )
{
	//******************************************
	// position control
	//******************************************
	int i;
	for( i = 0 ; i<3 ; ++i)
	{
		sysDataPtr->axisData[i].mSetValue = sysLinkDataPtr->intpToSysData.newSettingValueUVW[i];

		// relInc = (set - oldSet) / resolution
		double relDistance = sysDataPtr->axisData[i].mSetValue - sysDataPtr->axisData[i].mActValue;

		if (relDistance != 0)
		{
			if( i == 1 )
				sysDataPtr->axisData[i].relInc = (int)( relDistance / sysDataPtr->axisData[i].resolution ) + sysDataPtr->axisData[0].relInc;	
			else
				sysDataPtr->axisData[i].relInc = (int)( relDistance / sysDataPtr->axisData[i].resolution );		

		 
		// Safty Check
		   if( sysDataPtr->axisData[i].relInc < -200 )
		  	  sysDataPtr->axisData[i].relInc = -200;
		   else if( sysDataPtr->axisData[i].relInc > 200 )
			  sysDataPtr->axisData[i].relInc = 200;

		}
		else sysDataPtr->axisData[i].relInc = 0;

	}

	// output
	for (i = 0 ; i < 3 ; ++i)
	{
		//putAxisValue(i, sysDataPtr->axisData[i].relInc);
		if( i == 1 )
			sysDataPtr->axisData[i].mActValue += ( sysDataPtr->axisData[i].relInc - sysDataPtr->axisData[0].relInc ) * sysDataPtr->axisData[i].resolution;
		else
			sysDataPtr->axisData[i].mActValue += sysDataPtr->axisData[i].relInc * sysDataPtr->axisData[i].resolution;
        //sysDataPtr->axisData[i].mSetValue = sysDataPtr->axisData[i].mActValue;

	}

		return 0;
}

//**********************************************

//**********************************************
int record( SYS_DATA *sysDataPtr )
{
	int i;

	sysDataPtr->recordData[sysDataPtr->recordCounter].coordinate = sysLinkDataPtr->intpToSysData.coordinate;

	for( i = 0; i < 3; i++ )
	{
		sysDataPtr->recordData[sysDataPtr->recordCounter].xyzAxis[i] = sysLinkDataPtr->intpToSysData.newSettingValue[i];
		sysDataPtr->recordData[sysDataPtr->recordCounter].uvwAxis[i] = sysLinkDataPtr->intpToSysData.newSettingValueUVW[i];
	}

	sysDataPtr->recordCounter ++;

	return true;
}

//**********************************************

//**********************************************
int teachEnd( SYS_DATA *sysDataPtr )
{
	int i;

	sysDataPtr->saveFilePtr = fopen( sysDataPtr->savefileName, "w+" );
	
	for( i = 0; i < sysDataPtr->recordCounter; i++ )
	{
		if( i == 0 )
		{
			if( sysDataPtr->recordData[i].coordinate == XYZ_COORDINATE )
				fprintf( sysDataPtr->saveFilePtr, "N%i0 G00 G90 X%.4f Y%.4f Z%.4f\n", i, sysDataPtr->recordData[i].xyzAxis[0], sysDataPtr->recordData[i].xyzAxis[1], sysDataPtr->recordData[i].xyzAxis[2] );
			if( sysDataPtr->recordData[i].coordinate == UVW_COORDINATE )
				fprintf( sysDataPtr->saveFilePtr, "N%i0 G00 G90 U%.4f V%.4f W%.4f\n", i, sysDataPtr->recordData[i].uvwAxis[0], sysDataPtr->recordData[i].uvwAxis[1], sysDataPtr->recordData[i].uvwAxis[2] );
		}
		else
		{
			if( sysDataPtr->recordData[i].coordinate == XYZ_COORDINATE )
				fprintf( sysDataPtr->saveFilePtr, "N%i0 G01 G90 X%.4f Y%.4f Z%.4f F15\n", i, sysDataPtr->recordData[i].xyzAxis[0], sysDataPtr->recordData[i].xyzAxis[1], sysDataPtr->recordData[i].xyzAxis[2] );
			if( sysDataPtr->recordData[i].coordinate == UVW_COORDINATE )
				fprintf( sysDataPtr->saveFilePtr, "N%i0 G01 G90 U%.4f V%.4f W%.4f F15\n", i, sysDataPtr->recordData[i].uvwAxis[0], sysDataPtr->recordData[i].uvwAxis[1], sysDataPtr->recordData[i].uvwAxis[2] );
		}
		
	}
	fprintf( sysDataPtr->saveFilePtr, "M30\n");

	fclose( sysDataPtr->saveFilePtr );

	return true;
}
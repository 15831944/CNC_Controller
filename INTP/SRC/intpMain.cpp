#include "stdafx.h"
#include "..\INC\intp.h"
#include "..\..\DEC\INC\dec.h"
#include "..\..\FIFO\INC\fifo.h"
#include "..\..\SYS_LINK\INC\sysLink.h"
//#include "math.h"


//extern INTP_DATA	*intpDataPtr;

//extern DEC_TO_INTP_FIFO *decToIntpFifoPtr;
extern SYS_LINK_DATA   *sysLinkDataPtr;


//**********************************************

//**********************************************
double min( double a, double b, double c, double d )
{
	if( a < b && a < c && a < d )
		return a;
	if( b < a && b < c && b < d )
		return b;
	if( c < a && c < b && c < d )
		return c;
	if( d < a && d < b && d < c )
		return d;
}

//**********************************************

//**********************************************
double degToRad( double degree )
{
	double x,y,z;
	x = PI;
	y = degree * x;
	z = y / 180;

	return ( z );
}

//**********************************************

//**********************************************
double radToDeg( double radian )
{
	double x,y,z;
	x = PI;
	y = radian / x;
	z = y * 180;
	return ( z );
}

//**********************************************

//**********************************************
int xyzToUvw( double xyz[3], double uvw[3] )
{
	double planeLength, absoluteT, relativeT;
	double a,b,c,d,e,f,g,h;

	planeLength = sqrt( xyz[0] * xyz[0] + xyz[1] * xyz[1] );

	if( planeLength == 0 )
	{
		uvw[2] = xyz[2];
		return true;
	}

	absoluteT = radToDeg( acos( xyz[0] / planeLength ) );
	if( xyz[1] < 0 )
		absoluteT = -absoluteT;

	relativeT = radToDeg( acos( planeLength / 2.0 / 75.0 ) );

	a = pow( uvw[0] - ( absoluteT - relativeT ), 2 ) + pow( 2 * relativeT - uvw[1], 2 );
	b = pow( uvw[0] - ( absoluteT + relativeT ), 2 ) + pow( -2 * relativeT - uvw[1], 2 );
	c = pow( uvw[0] - ( absoluteT - relativeT ), 2 ) + pow( 2 * relativeT + uvw[1], 2 );
	d = pow( uvw[0] - ( absoluteT + relativeT ), 2 ) + pow( -2 * relativeT + uvw[1], 2 );
	e = pow( -uvw[0] - ( absoluteT - relativeT ), 2 ) + pow( 2 * relativeT - uvw[1], 2 );
	f = pow( -uvw[0] - ( absoluteT + relativeT ), 2 ) + pow( -2 * relativeT - uvw[1], 2 );
	g = 10000000;// pow( -uvw[0] - ( absoluteT - relativeT ), 2 ) + pow( absoluteT + relativeT + uvw[1], 2 );
	h = 10000000;//pow( -uvw[0] - ( absoluteT + relativeT ), 2 ) + pow( absoluteT - relativeT + uvw[1], 2 );

	a = min( a, c, e, g );
	b = min( b, d, f, h );

	if( a < b )
	{
		uvw[0] = absoluteT - relativeT;
		uvw[1] = 2 * relativeT;
		uvw[2] = xyz[2];
	}

	else// if( a > b && c > d && e > f && g > h )
	{
		uvw[0] = absoluteT + relativeT;
		uvw[1] = -2 * relativeT;
		uvw[2] = xyz[2];
	}

	return true;
}

//**********************************************

//**********************************************
void uvwToXyz( double xyz[3], double uvw[3] )
{
	double a,b,c,d;
	a = cos( degToRad( uvw[0] ) );
	b = cos( degToRad( uvw[0] + uvw[1] ) );
	c = sin( degToRad( uvw[0] ) );
	d = sin( degToRad( uvw[0] + uvw[1] ) );
	xyz[0] = 75.0 * ( a + b );
	xyz[1] = 75.0 * ( c + d );
	xyz[2] = uvw[2];
}

//**********************************************

//**********************************************
int slope( INTP_DATA *intpDataPtr )
{
	switch( intpDataPtr->speedState )
	{
		case SPEED_UP:
			intpDataPtr->nowSpeed += intpDataPtr->vStep * intpDataPtr->accelN / abs( intpDataPtr->accelN );

			if( intpDataPtr->intpCounter == abs( intpDataPtr->accelN ) )
			{	
				intpDataPtr->speedState = SPEED_CONST;
			}
			else
			{
				intpDataPtr->deceLength += intpDataPtr->nowSpeed * intpDataPtr->cyclingTime;//²¾¨ìpre
			}	
			break;

		case SPEED_CONST:
			intpDataPtr->nowSpeed = intpDataPtr->feedrate;

			if( intpDataPtr->intpCounter == abs( intpDataPtr->accelN ) + intpDataPtr->constN )
			{
				intpDataPtr->speedState = SPEED_DOWN;
			}
			break;

		case SPEED_DOWN:
			

			intpDataPtr->nowSpeed -= intpDataPtr->accel * intpDataPtr->cyclingTime;

			if( intpDataPtr->intpCounter == abs( intpDataPtr->accelN ) + intpDataPtr->constN + 1 )
			{
				intpDataPtr->nowSpeed = intpDataPtr->accelHold;
			}

			if( intpDataPtr->intpCounter == abs( intpDataPtr->accelN ) + intpDataPtr->constN + intpDataPtr->resN + 1 )
			{
				if( intpDataPtr->resN == 1 )
				{
					intpDataPtr->nowSpeed = intpDataPtr->accelHold;
				}
				else
				{
					intpDataPtr->nowSpeed = intpDataPtr->duceHold;
				}
			}

			if( intpDataPtr->intpCounter == abs( intpDataPtr->accelN ) + intpDataPtr->constN + intpDataPtr->resN )
			{
				intpDataPtr->duceHold = intpDataPtr->nowSpeed;
				intpDataPtr->nowSpeed = intpDataPtr->resHold;
			}

			if( intpDataPtr->nowSpeed <= 0 )
			{
				intpDataPtr->nowSpeed = 0;
			}
			break;
	}
	return GOOD;
}

//**********************************************

//**********************************************
int g04DwellTime( INTP_DATA *intpDataPtr )
{
	double value;
	value = intpDataPtr->pathBlock.motionFunction.rtFunction.dwellTime.value;
	intpDataPtr->dwellTimeCounter = ( int ) value / sysLinkDataPtr->cyclingTime;
	intpDataPtr->dwellTimeCounter--;
	intpDataPtr->intpState = DWELL_TIME_EXE;
	return GOOD;
}

//**********************************************

//**********************************************
int dwellTimeExe( INTP_DATA *intpDataPtr )
{
	intpDataPtr->dwellTimeCounter--;
	if( intpDataPtr->dwellTimeCounter == 0 )
	{
		intpDataPtr->intpState = INTP_IDLE;
	}
	else
	{
		intpDataPtr->intpState = DWELL_TIME_EXE;
	}
	return GOOD;
}

//**********************************************

//**********************************************
int gMotion( INTP_DATA *intpDataPtr )
{
	int i;

	PATH_MOTION* pathMotionPtr;
	pathMotionPtr = &intpDataPtr->pathBlock.motionFunction.pathMotion;

	intpDataPtr->coordinate = pathMotionPtr->coordinate;
	sysLinkDataPtr->intpToSysData.coordinate = pathMotionPtr->coordinate;

	if( intpDataPtr->pathBlock.blockCommand == G00_MOTION )
	{
		intpDataPtr->feedrate = intpDataPtr->g00Feed;
	}
	else
	{
		intpDataPtr->feedrate = pathMotionPtr->feedrate;
		if( intpDataPtr->feedrate > MAXRATE )
		{
			intpDataPtr->feedrate = MAXRATE;
		}
	}

	for( i = 0 ; i < 3 ; i++ )
	{
		if( intpDataPtr->xyzNew[i] == intpDataPtr->xyzEnd[i] )
		{
			intpDataPtr->xyzStart[i] = intpDataPtr->xyzNew[i];
			intpDataPtr->uvwStart[i] = intpDataPtr->uvwNew[i];
		}
		intpDataPtr->xyzOld[i] = intpDataPtr->xyzNew[i];
		intpDataPtr->xyzDelta[i] = 0;
		intpDataPtr->uvwOld[i] = intpDataPtr->uvwNew[i];
		intpDataPtr->uvwDelta[i] = 0;
	} // end for

	if( pathMotionPtr->relative == false )//G90
	{
		if( pathMotionPtr->coordinate == XYZ_COORDINATE )
		{
			for( i = 0; i < 3; i++ )
			{
				if( pathMotionPtr->xyzSendValid[i] == true )
				{
					intpDataPtr->xyzDelta[i] = pathMotionPtr->xyzCoordinate[i] - intpDataPtr->xyzNew[i];
					intpDataPtr->xyzEnd[i] = pathMotionPtr->xyzCoordinate[i];
				}
				else
				{
					intpDataPtr->xyzDelta[i] = 0;
				}
			}

			xyzToUvw( intpDataPtr->xyzEnd, intpDataPtr->uvwEnd );

			for( i = 0; i < 3; i++ )
				intpDataPtr->uvwDelta[i] = intpDataPtr->uvwEnd[i] - intpDataPtr->uvwNew[i];
		}
		else
		{
			for( i = 0; i < 3; i++ )
			{
				if( pathMotionPtr->uvwSendValid[i] == true )
				{
					intpDataPtr->uvwDelta[i] = pathMotionPtr->uvwCoordinate[i] - intpDataPtr->uvwNew[i];
					intpDataPtr->uvwEnd[i] = pathMotionPtr->uvwCoordinate[i];
				}
				else
				{
					intpDataPtr->uvwDelta[i] = 0;
				}
			}

			uvwToXyz( intpDataPtr->xyzEnd, intpDataPtr->uvwEnd );

			for( i = 0; i < 3; i++ )
				intpDataPtr->xyzDelta[i] = intpDataPtr->xyzEnd[i] - intpDataPtr->xyzNew[i];
		}
	} // end if
 
	else//G91
	{
		if( pathMotionPtr->coordinate == XYZ_COORDINATE )
		{
			for( i = 0; i < 3; i++ )
			{
				if( pathMotionPtr->xyzSendValid[i] == true )
				{
					intpDataPtr->xyzDelta[i] = pathMotionPtr->xyzCoordinate[i] - intpDataPtr->sumDeltaLength * intpDataPtr->linFactor[i];
					intpDataPtr->xyzEnd[i] = intpDataPtr->xyzStart[i] + pathMotionPtr->xyzCoordinate[i];
				}
			}

			intpDataPtr->sumDeltaLength = 0;

			xyzToUvw( intpDataPtr->xyzEnd, intpDataPtr->uvwEnd );

			for( i = 0; i < 3; i++ )
				intpDataPtr->uvwDelta[i] = intpDataPtr->uvwEnd[i] - intpDataPtr->uvwNew[i];
		}
		else
		{
			for( i = 0; i < 3; i++ )
			{
				if( pathMotionPtr->uvwSendValid[i] == true )
				{
					intpDataPtr->uvwDelta[i] = pathMotionPtr->uvwCoordinate[i] - intpDataPtr->sumDeltaLength * intpDataPtr->angleFactor[i];
					intpDataPtr->uvwEnd[i] = intpDataPtr->uvwStart[i] + pathMotionPtr->uvwCoordinate[i];
				}
			}

			intpDataPtr->sumDeltaAngle = 0;

			uvwToXyz( intpDataPtr->xyzEnd, intpDataPtr->uvwEnd );

			for( i = 0; i < 3; i++ )
				intpDataPtr->xyzDelta[i] = intpDataPtr->xyzEnd[i] - intpDataPtr->xyzNew[i];
		}
		
	}

	if( pathMotionPtr->coordinate == XYZ_COORDINATE )
	{
		intpDataPtr->pathLength = sqrt( intpDataPtr->xyzDelta[0] * intpDataPtr->xyzDelta[0] + intpDataPtr->xyzDelta[1] * intpDataPtr->xyzDelta[1] + intpDataPtr->xyzDelta[2] * intpDataPtr->xyzDelta[2] );

		if( intpDataPtr->pathLength == 0 )
		{
			m30ProgramEnd( intpDataPtr );
			return GOOD;
		} // end if

		else 
		{
			for( i = 0; i < 3; i++ )
			{
				intpDataPtr->linFactor[i] = intpDataPtr->xyzDelta[i] / intpDataPtr->pathLength;
			} // end for
		
			intpDataPtr->intpState = INTP_LIN_PRE;
		} // end else
	}
	else
	{
		if( intpDataPtr->pathBlock.blockCommand == G00_MOTION )
		{
			intpDataPtr->feedrate = intpDataPtr->g00AngFeed;
		}
		else
		{
			intpDataPtr->feedrate = pathMotionPtr->feedrate;
			if( intpDataPtr->feedrate > MAXRATE )
			{
				intpDataPtr->feedrate = MAXRATE;
			}
		}

		intpDataPtr->angleMean = sqrt( intpDataPtr->uvwDelta[0] * intpDataPtr->uvwDelta[0] + intpDataPtr->uvwDelta[1] * intpDataPtr->uvwDelta[1] +intpDataPtr->xyzDelta[2] * intpDataPtr->xyzDelta[2] );
		
		if( intpDataPtr->angleMean == 0 )
		{
			return GOOD;
		}
		else
		{
			for( i = 0; i < 3; i++ )
			{
				intpDataPtr->angleFactor[i] = intpDataPtr->uvwDelta[i] / intpDataPtr->angleMean;
			}
		}

		intpDataPtr->intpState = INTP_ROTATE_PRE;
	}
	
	if( intpDataPtr->pathBlock.blockCommand == G02_MOTION || intpDataPtr->pathBlock.blockCommand == G03_MOTION )
	{
		double a[3];
		double b[3];

		for( i = 0; i < 3; i++ )
		{
			if( pathMotionPtr->ijkSendValid[i] == true )
			{
				intpDataPtr->ijk[i] = pathMotionPtr->ijkCoordinate[i];
				intpDataPtr->center[i] = intpDataPtr->xyzNew[i] + intpDataPtr->ijk[i];
				a[i] = intpDataPtr->xyzNew[i] - intpDataPtr->center[i];
				b[i] = intpDataPtr->xyzEnd[i] - intpDataPtr->center[i];
			}
			else
			{
				intpDataPtr->center[i] = intpDataPtr->xyzNew[i];
				a[i] = 0;
				b[i] = 0;
			}
		}

		intpDataPtr->radius =  sqrt( a[0] * a[0] + a[1] * a[1] + a[2] * a[2] );

		if( intpDataPtr->radius != 0 )
		{
			if( pathMotionPtr->plane == XY_PLANE )
			{
				intpDataPtr->plane = XY_PLANE;
				if( a[1] > 0 )
					intpDataPtr->startAng = radToDeg( acos( a[0] / intpDataPtr->radius ) );
				else
					intpDataPtr->startAng = 360 - radToDeg( acos( a[0] / intpDataPtr->radius ) );
				if( b[1] > 0 )
					intpDataPtr->endAng = radToDeg( acos( b[0] / intpDataPtr->radius ) );
				else
					intpDataPtr->endAng = 360 - radToDeg( acos( b[0] / intpDataPtr->radius ) );
				
				if( intpDataPtr->pathBlock.blockCommand == G02_MOTION )//°f®É°w
				{
					intpDataPtr->moveAng = intpDataPtr->endAng - intpDataPtr->startAng;
					if( intpDataPtr->moveAng < 0 )
						intpDataPtr->moveAng += 360;
				}
				else
					intpDataPtr->moveAng = 360 - ( intpDataPtr->endAng - intpDataPtr->startAng );

				intpDataPtr->pathLength = 2 * PI * intpDataPtr->radius * intpDataPtr->moveAng / 360;
			}

			if( pathMotionPtr->plane == YZ_PLANE )
			{
				intpDataPtr->ijk[i] = pathMotionPtr->ijkCoordinate[i];
				a[i] = intpDataPtr->xyzStart[i] - intpDataPtr->ijk[i];
				b[i] = intpDataPtr->xyzEnd[i] - intpDataPtr->ijk[i];
			}

			if( pathMotionPtr->plane == ZX_PLANE )
			{
				intpDataPtr->ijk[i] = pathMotionPtr->ijkCoordinate[i];
				a[i] = intpDataPtr->xyzStart[i] - intpDataPtr->ijk[i];
				b[i] = intpDataPtr->xyzEnd[i] - intpDataPtr->ijk[i];
			}

			intpDataPtr->intpState = INTP_CIR_PRE;
		}

	}
	return GOOD;
}

//**********************************************

//**********************************************
int m30ProgramEnd( INTP_DATA *intpDataPtr )
{
	//m30 program end, info to sys
	//sysLinkDataPtr->intpToSysData.m30 = true;
	intpDataPtr->intpState = INTP_IDLE;
	sysLinkDataPtr->intpToSysData.m30 = true;
	return GOOD;
}

//**********************************************

//**********************************************
int newBlockProcessing( INTP_DATA *intpDataPtr )
{
	switch( intpDataPtr->pathBlock.blockCommand )
	{
	case G04_DWELL_TIME:
		g04DwellTime( intpDataPtr );
		break;

	case G00_MOTION:
	case G01_MOTION:
	case G02_MOTION:
	case G03_MOTION:
		gMotion( intpDataPtr );
		break;

	case M30_PROGRAM_END:
		m30ProgramEnd( intpDataPtr );
		break;
	}
	return GOOD;
}

//**********************************************

//**********************************************
int intpInit( INTP_DATA *intpDataPtr )
{
	intpDataPtr->intpState = INTP_IDLE;
	intpDataPtr->speedState = SPEED_UP;
	intpDataPtr->intpCounter = 0;
	intpDataPtr->cyclingTime = 0.033;
	intpDataPtr->g00Feed = ( 0.5 / intpDataPtr->cyclingTime );
	intpDataPtr->g00AngFeed = ( 0.36 / intpDataPtr->cyclingTime );
	intpDataPtr->accel = 200.0;
	intpDataPtr->vStep = intpDataPtr->accel * intpDataPtr->cyclingTime;
	intpDataPtr->uvwNew[0] = 90;
	intpDataPtr->uvwNew[1] = 180;
	intpDataPtr->uvwNew[2] = 100;
	intpDataPtr->xyzNew[2] = 100;

	return GOOD;
}

//**********************************************

//**********************************************
int intpIdle( INTP_DATA *intpDataPtr )
{
	//check if new block in decToIntp fifo available
	if( rdFifo( (FIFO_HEAD*) &sysLinkDataPtr->decToIntpData.decToIntpFifo,(char*) &intpDataPtr->pathBlock ) == true )
	{
		// new NC block comes, processing it
		newBlockProcessing( intpDataPtr );
	}
	else if( rdFifo( (FIFO_HEAD*) &sysLinkDataPtr->sysToIntpData.sysToIntpFifo,(char*) &intpDataPtr->pathBlock ) == true )
	{
		// new NC block comes, processing it
		newBlockProcessing( intpDataPtr );
	}
	return true;
}

//**********************************************

//**********************************************
int intpLinPre( INTP_DATA *intpDataPtr )
{
	int    i = 1;
	int    n = 0;
	double l = 0;
	double x = 0;

	intpDataPtr->accelN = intpDataPtr->feedrate / intpDataPtr->vStep;

	if( intpDataPtr->accelN == 0 )
	{
		intpDataPtr->nowSpeed = intpDataPtr->feedrate;
		intpDataPtr->speedState = SPEED_CONST;
		intpDataPtr->accelN = 0;
		intpDataPtr->duceN = 0;
		intpDataPtr->constN = intpDataPtr->pathLength / ( intpDataPtr->feedrate * intpDataPtr->cyclingTime );
		intpDataPtr->resN = 1;
		intpDataPtr->resLength = intpDataPtr->pathLength - intpDataPtr->newFeedrate * intpDataPtr->constN;
		intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;
		intpDataPtr->intpState = INTP_LIN_EXE;
	}
	else
	{
		intpDataPtr->duceN = intpDataPtr->accelN;

		for( i = 1; i < intpDataPtr->accelN + 1; i++ )
		{
			l += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
		}

		if( intpDataPtr->pathLength < 2 * l + intpDataPtr->feedrate * intpDataPtr->cyclingTime )
		{
			l = 0;
			for( i = 1; intpDataPtr->pathLength > 2 * l + intpDataPtr->vStep * intpDataPtr->cyclingTime * i; i++ )
			{
				l += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
				intpDataPtr->accelN = i - 1;
			}
			l -= intpDataPtr->vStep * intpDataPtr->cyclingTime * (i - 1);
			intpDataPtr->constN = 1;
			intpDataPtr->feedrate = intpDataPtr->vStep * (intpDataPtr->accelN + 1);
			intpDataPtr->duceN = intpDataPtr->accelN;
		}
		else
		{
			intpDataPtr->constN = (intpDataPtr->pathLength - 2 * l) / (intpDataPtr->feedrate * intpDataPtr->cyclingTime);		
		}

		intpDataPtr->accelHold = intpDataPtr->vStep * intpDataPtr->accelN;	
		intpDataPtr->resLength = intpDataPtr->pathLength - 2 * l - intpDataPtr->feedrate * intpDataPtr->cyclingTime * intpDataPtr->constN;
		intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;

		for( i = intpDataPtr->accelHold; i >= 0; i -= intpDataPtr->vStep )
		{
			n++;
			if( i < intpDataPtr->resHold && i +intpDataPtr->vStep > intpDataPtr->resHold )
			{
				intpDataPtr->resN = n;
			}
		}
		intpDataPtr->intpState = INTP_LIN_EXE;
	}

	intpDataPtr->oldFeedrate = intpDataPtr->feedrate;

	return true;
}


//**********************************************

//**********************************************
int linOverride( INTP_DATA *intpDataPtr )
{
	int    i = 1;
	int    n = 0;
	double l = 0;
	double k = 0;
	int    x = 0;

	intpDataPtr->newAccelN = ( intpDataPtr->newFeedrate - intpDataPtr->nowSpeed ) / intpDataPtr->vStep;
	intpDataPtr->overPathLength = intpDataPtr->pathLength - intpDataPtr->sumDeltaLength;

	if( intpDataPtr->newAccelN == 0 )
	{
		intpDataPtr->nowSpeed = intpDataPtr->newFeedrate;
		intpDataPtr->newDuceN = intpDataPtr->newFeedrate / intpDataPtr->vStep;

		if( intpDataPtr->newDuceN == 0 )
		{
			intpDataPtr->nowSpeed = intpDataPtr->newFeedrate;
			intpDataPtr->feedrate = intpDataPtr->newFeedrate;
			intpDataPtr->speedState = SPEED_CONST;
			intpDataPtr->accelN = 0;
			intpDataPtr->duceN = 0;
			intpDataPtr->constN = intpDataPtr->overPathLength / ( intpDataPtr->newFeedrate * intpDataPtr->cyclingTime);
			intpDataPtr->resN = 1;
			intpDataPtr->resLength = intpDataPtr->overPathLength - intpDataPtr->newFeedrate * intpDataPtr->constN;
			intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;

		}
		else
		{
			for( i = 1; i < intpDataPtr->newDuceN + 1; i++ )
			{
				k += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
			}

			if( intpDataPtr->overPathLength < k + intpDataPtr->newFeedrate * intpDataPtr->cyclingTime )
			{
				k = 0;
				for( i = 1; intpDataPtr->overPathLength > k + intpDataPtr->vStep * intpDataPtr->cyclingTime * i; i++ )
				{
					k += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
					intpDataPtr->newDuceN = i - 1;
				}
				k -= intpDataPtr->vStep * intpDataPtr->cyclingTime * ( i - 1 );
				intpDataPtr->accelN = 0;
				intpDataPtr->constN = ( intpDataPtr->overPathLength - k ) / intpDataPtr->newFeedrate;
				intpDataPtr->feedrate = intpDataPtr->vStep * ( intpDataPtr->newDuceN + 1 );
				intpDataPtr->duceN = intpDataPtr->newFeedrate;
				intpDataPtr->resLength = intpDataPtr->overPathLength - k - intpDataPtr->newFeedrate * intpDataPtr->cyclingTime * intpDataPtr->constN;
				intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;

				for( i = intpDataPtr->accelHold; i >= 0; i -= intpDataPtr->vStep )
				{
					n++;
					if( i < intpDataPtr->resHold && i +intpDataPtr->vStep > intpDataPtr->resHold )
					{
						intpDataPtr->resN = n;
					}
				}
				intpDataPtr->speedState = SPEED_CONST;
			}
		}
	}
	else
	{
		intpDataPtr->newDuceN = intpDataPtr->newFeedrate / intpDataPtr->vStep;

		for( i = 1; i < abs( intpDataPtr->newAccelN ) + 1; i++ )
		{
			l += ( intpDataPtr->vStep * i + intpDataPtr->nowSpeed ) * intpDataPtr->cyclingTime;
		}

		for( i = 1; i < intpDataPtr->newDuceN + 1; i++ )
		{
			k += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
		}

		if( intpDataPtr->overPathLength < l + k + intpDataPtr->newFeedrate * intpDataPtr->cyclingTime )
		{
			l = 0;

			for( i = 1; intpDataPtr->overPathLength > 2 * l + k + ( intpDataPtr->vStep * i * intpDataPtr->newAccelN / abs( intpDataPtr->newAccelN ) + intpDataPtr->nowSpeed ) * intpDataPtr->cyclingTime; i++ )
			{
				l += ( intpDataPtr->vStep * i * intpDataPtr->newAccelN / abs( intpDataPtr->newAccelN ) + intpDataPtr->nowSpeed ) * intpDataPtr->cyclingTime;
				n = ( intpDataPtr->vStep * i * intpDataPtr->newAccelN / abs( intpDataPtr->newAccelN ) + intpDataPtr->nowSpeed ) * intpDataPtr->cyclingTime / intpDataPtr->vStep;
				for( x = 1; x < n + 1; x++ )
				{
					k += ( intpDataPtr->vStep * i + intpDataPtr->nowSpeed ) - intpDataPtr->vStep * x;
				}
				intpDataPtr->newAccelN = ( i - 1 ) * intpDataPtr->newAccelN / abs( intpDataPtr->newAccelN ); 
			}
			l -= intpDataPtr->vStep * intpDataPtr->cyclingTime * (i - 1);
			intpDataPtr->constN = 1;
			intpDataPtr->feedrate = intpDataPtr->vStep * (intpDataPtr->accelN + 1) + intpDataPtr->nowSpeed;
			intpDataPtr->duceN = intpDataPtr->newDuceN;
			intpDataPtr->accelN = intpDataPtr->newAccelN;

		}
		else
		{
			intpDataPtr->feedrate = intpDataPtr->newFeedrate;
			intpDataPtr->constN = ( intpDataPtr->overPathLength - k - l ) / ( intpDataPtr->feedrate * intpDataPtr->cyclingTime );		
		}

		intpDataPtr->accelHold = intpDataPtr->feedrate - intpDataPtr->vStep;	
		intpDataPtr->resLength = intpDataPtr->overPathLength - ( k + l ) - intpDataPtr->newFeedrate * intpDataPtr->cyclingTime * intpDataPtr->constN;
		intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;
		intpDataPtr->duceN = intpDataPtr->newDuceN;
		intpDataPtr->accelN = intpDataPtr->newAccelN;

		for( i = intpDataPtr->accelHold; i >= 0; i -= intpDataPtr->vStep )
		{
			n++;
			if( i < intpDataPtr->resHold && i +intpDataPtr->vStep > intpDataPtr->resHold )
			{
				intpDataPtr->resN = n;
			}
		}
		if( intpDataPtr->newDuceN == 0 )
		{
			intpDataPtr->resN = 1;
		}

		intpDataPtr->speedState = SPEED_UP;
	}
	return true;
}

//**********************************************

//**********************************************
int intpLinExe( INTP_DATA *intpDataPtr )
{
	int i;

	

	intpDataPtr->intpCounter++;

	slope( intpDataPtr );// montFeed and intpEnd

	intpDataPtr->deltaLength = intpDataPtr->nowSpeed * intpDataPtr->cyclingTime;
	intpDataPtr->sumDeltaLength += intpDataPtr->deltaLength;

	//if( abs( intpDataPtr->pathLength - intpDataPtr->sumDeltaLength ) < intpDataPtr->deltaLength )
	if( intpDataPtr->intpCounter == intpDataPtr->accelN + intpDataPtr->constN + intpDataPtr->duceN + 2 )
	{
		for( i = 0; i < 3; i++ )
		{
			intpDataPtr->xyzOld[i] = intpDataPtr->xyzNew[i];
			intpDataPtr->xyzNew[i] = intpDataPtr->xyzEnd[i];	
		}

		intpDataPtr->intpEnd = true;
	}

	else
	{
		for( i = 0; i < 3; i++ )
		{
			intpDataPtr->xyzOld[i] = intpDataPtr->xyzNew[i];
			intpDataPtr->uvwOld[i] = intpDataPtr->uvwNew[i];
			intpDataPtr->xyzNew[i] = intpDataPtr->xyzStart[i] + intpDataPtr->sumDeltaLength * intpDataPtr->linFactor[i];	
		}

		intpDataPtr->intpEnd = false;
	}

	xyzToUvw( intpDataPtr->xyzNew, intpDataPtr->uvwNew );

	for( i = 0; i < 2; i++ )
	{
		if( abs( intpDataPtr->uvwNew[i] - intpDataPtr->uvwOld[i] > 178 && intpDataPtr->uvwNew[i] - intpDataPtr->uvwOld[i] < 182 ) )
			intpDataPtr->uvwNew[i] = 180 - intpDataPtr->uvwNew[i];
	}

	for( i = 0; i < 3; i++ )
	{
		sysLinkDataPtr->intpToSysData.newSettingValueUVW[i] = intpDataPtr->uvwNew[i];
		sysLinkDataPtr->intpToSysData.newSettingValue[i] = intpDataPtr->xyzNew[i];
	}

	if( sysLinkDataPtr->sysToIntpData.feedChange == true )
	{
		if( intpDataPtr->speedState == SPEED_DOWN )
		{
			sysLinkDataPtr->sysToIntpData.feedChange = false;
		}
		else
		{
			intpDataPtr->intpCounter = 0;
			intpDataPtr->newFeedrate = ( sysLinkDataPtr->sysToIntpData.feedOverride / 100. ) * intpDataPtr->oldFeedrate;
			if( intpDataPtr->newFeedrate == 0 )
			{
				intpDataPtr->feedrate = 0;
				intpDataPtr->speedState = SPEED_CONST;
			}
			else
			{
				linOverride( intpDataPtr );
				sysLinkDataPtr->sysToIntpData.feedChange = false;
			}
		}
	}
	
	if( intpDataPtr->intpEnd == true )
	{
		intpDataPtr->intpEnd = false;
		intpDataPtr->intpState = INTP_LIN_CLOSE;
	}

	return true;
}

//**********************************************

//**********************************************
int intpLinClose( INTP_DATA *intpDataPtr )
{
	//output end position
	//change intp state
	intpDataPtr->intpState = INTP_IDLE;
	intpDataPtr->speedState = SPEED_UP;
	intpDataPtr->intpCounter = 0;
	intpDataPtr->sumDeltaLength = 0;
	return true;
}

//**********************************************

//**********************************************
int intpCirPre( INTP_DATA *intpDataPtr )
{
	int    i = 1;
	int    n = 0;
	double l = 0;
	double x = 0;

	intpDataPtr->accelN = intpDataPtr->feedrate / intpDataPtr->vStep;

	if( intpDataPtr->accelN == 0 )
	{
		intpDataPtr->nowSpeed = intpDataPtr->feedrate;
		intpDataPtr->speedState = SPEED_CONST;
		intpDataPtr->accelN = 0;
		intpDataPtr->duceN = 0;
		intpDataPtr->constN = intpDataPtr->pathLength / ( intpDataPtr->feedrate * intpDataPtr->cyclingTime );
		intpDataPtr->resN = 1;
		intpDataPtr->resLength = intpDataPtr->pathLength - intpDataPtr->newFeedrate * intpDataPtr->constN;
		intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;
		intpDataPtr->intpState = INTP_CIR_CLOSE;
	}
	else
	{
		intpDataPtr->duceN = intpDataPtr->accelN;

		for( i = 1; i < intpDataPtr->accelN + 1; i++ )
		{
			l += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
		}

		if( intpDataPtr->pathLength < 2 * l + intpDataPtr->feedrate * intpDataPtr->cyclingTime )
		{
			l = 0;

			for( i = 1; intpDataPtr->pathLength > 2 * l + intpDataPtr->vStep * intpDataPtr->cyclingTime * i; i++ )
			{
				l += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
				intpDataPtr->accelN = i - 1;
			}

			l -= intpDataPtr->vStep * intpDataPtr->cyclingTime * (i - 1);
			intpDataPtr->constN = 1;
			intpDataPtr->feedrate = intpDataPtr->vStep * (intpDataPtr->accelN + 1);
			intpDataPtr->duceN = intpDataPtr->accelN;
		}
		else
		{
			intpDataPtr->constN = (intpDataPtr->pathLength - 2 * l) / (intpDataPtr->feedrate * intpDataPtr->cyclingTime);		
		}

		intpDataPtr->accelHold = intpDataPtr->vStep * intpDataPtr->accelN;	
		intpDataPtr->resLength = intpDataPtr->pathLength - 2 * l - intpDataPtr->feedrate * intpDataPtr->cyclingTime * intpDataPtr->constN;
		intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;

		for( i = intpDataPtr->accelHold; i >= 0; i -= intpDataPtr->vStep )
		{
			n++;
			if( i < intpDataPtr->resHold && i +intpDataPtr->vStep > intpDataPtr->resHold )
			{
				intpDataPtr->resN = n;
			}
		}
		intpDataPtr->intpState = INTP_CIR_EXE;
	}

	return true;
}

//**********************************************

//**********************************************
int intpCirExe( INTP_DATA *intpDataPtr )
{
	int i;
	intpDataPtr->intpCounter++;

	slope( intpDataPtr );// montFeed and intpEnd

	intpDataPtr->deltaLength = intpDataPtr->nowSpeed * intpDataPtr->cyclingTime;
	intpDataPtr->sumDeltaLength += intpDataPtr->deltaLength;
	intpDataPtr->sumDeltaAngle = intpDataPtr->sumDeltaLength / intpDataPtr->pathLength * intpDataPtr->moveAng;

	//if( abs( intpDataPtr->pathLength - intpDataPtr->sumDeltaLength ) < intpDataPtr->deltaLength )
	if( intpDataPtr->intpCounter == intpDataPtr->accelN + intpDataPtr->constN + intpDataPtr->duceN + 2 )
	{
		if( intpDataPtr->plane == XY_PLANE )
		{
			intpDataPtr->xyzNew[0] = intpDataPtr->xyzEnd[0];
			intpDataPtr->xyzNew[1] = intpDataPtr->xyzEnd[1];
		}
		
		intpDataPtr->intpEnd = true;
	}

	else
	{	
		if( intpDataPtr->plane == XY_PLANE )
		{
			intpDataPtr->xyzOld[0] = intpDataPtr->xyzNew[0];
			intpDataPtr->xyzOld[1] = intpDataPtr->xyzNew[1];
			intpDataPtr->xyzNew[0] = intpDataPtr->center[0] + intpDataPtr->radius * cos( degToRad( intpDataPtr->startAng + intpDataPtr->sumDeltaAngle ));
			intpDataPtr->xyzNew[1] = intpDataPtr->center[1] + intpDataPtr->radius * sin( degToRad( intpDataPtr->startAng + intpDataPtr->sumDeltaAngle ));
		}
	
		intpDataPtr->intpEnd = false;
	}

	xyzToUvw( intpDataPtr->xyzNew, intpDataPtr->uvwNew );
	
	for( i = 0; i < 3; i++ )
	{
		sysLinkDataPtr->intpToSysData.newSettingValueUVW[i] = intpDataPtr->uvwNew[i];
		sysLinkDataPtr->intpToSysData.newSettingValue[i] = intpDataPtr->xyzNew[i];
	}

	if( intpDataPtr->intpEnd == true )
	{
		intpDataPtr->intpEnd = false;
		intpDataPtr->intpState = INTP_CIR_CLOSE;
	}

	return true;
}

//**********************************************

//**********************************************
int intpCirClose( INTP_DATA *intpDataPtr )
{
	intpDataPtr->intpState = INTP_IDLE;
	intpDataPtr->speedState = SPEED_UP;
	intpDataPtr->intpCounter = 0;
	intpDataPtr->sumDeltaLength = 0;
	intpDataPtr->sumDeltaAngle = 0;

	return true;
}

//**********************************************

//**********************************************
int intpRotatePre( INTP_DATA *intpDataPtr )
{
	int    i = 1;
	int    n = 0;
	double l = 0;
	double x = 0;

	intpDataPtr->accelN = intpDataPtr->feedrate / intpDataPtr->vStep;

	if( intpDataPtr->accelN == 0 )
	{
		intpDataPtr->nowSpeed = intpDataPtr->feedrate;
		intpDataPtr->speedState = SPEED_CONST;
		intpDataPtr->accelN = 0;
		intpDataPtr->duceN = 0;
		intpDataPtr->constN = intpDataPtr->angleMean / ( intpDataPtr->feedrate * intpDataPtr->cyclingTime );
		intpDataPtr->resN = 1;
		intpDataPtr->resLength = intpDataPtr->angleMean - intpDataPtr->newFeedrate * intpDataPtr->constN;
		intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;
		intpDataPtr->intpState = INTP_ROTATE_EXE;
	}
	else
	{
		intpDataPtr->duceN = intpDataPtr->accelN;

		for( i = 1; i < intpDataPtr->accelN + 1; i++ )
		{
			l += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
		}

		if( intpDataPtr->angleMean < 2 * l + intpDataPtr->feedrate * intpDataPtr->cyclingTime )
		{
			l = 0;
			for( i = 1; intpDataPtr->angleMean > 2 * l + intpDataPtr->vStep * intpDataPtr->cyclingTime * i; i++ )
			{
				l += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
				intpDataPtr->accelN = i - 1;
			}
			l -= intpDataPtr->vStep * intpDataPtr->cyclingTime * (i - 1);
			intpDataPtr->constN = 1;
			intpDataPtr->feedrate = intpDataPtr->vStep * ( intpDataPtr->accelN + 1 );
			intpDataPtr->duceN = intpDataPtr->accelN;
		}
		else
		{
			intpDataPtr->constN = ( intpDataPtr->angleMean - 2 * l) / (intpDataPtr->feedrate * intpDataPtr->cyclingTime);		
		}

		intpDataPtr->accelHold = intpDataPtr->vStep * intpDataPtr->accelN;	
		intpDataPtr->resLength = intpDataPtr->angleMean - 2 * l - intpDataPtr->feedrate * intpDataPtr->cyclingTime * intpDataPtr->constN;
		intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;

		for( i = intpDataPtr->accelHold; i >= 0; i -= intpDataPtr->vStep )
		{
			n++;
			if( i < intpDataPtr->resHold && i +intpDataPtr->vStep > intpDataPtr->resHold )
			{
				intpDataPtr->resN = n;
			}
		}
		intpDataPtr->intpState = INTP_ROTATE_EXE;
	}

	intpDataPtr->oldFeedrate = intpDataPtr->feedrate;

	return true;
}

//**********************************************

//**********************************************
int rotOverride( INTP_DATA *intpDataPtr )
{
	int    i = 1;
	int    n = 0;
	double l = 0;
	double k = 0;
	int    x = 0;

	intpDataPtr->newAccelN = ( intpDataPtr->newFeedrate - intpDataPtr->nowSpeed ) / intpDataPtr->vStep;
	intpDataPtr->overPathLength = intpDataPtr->angleMean - intpDataPtr->sumDeltaLength;

	if( intpDataPtr->newAccelN == 0 )
	{
		intpDataPtr->nowSpeed = intpDataPtr->newFeedrate;
		intpDataPtr->newDuceN = intpDataPtr->newFeedrate / intpDataPtr->vStep;

		if( intpDataPtr->newDuceN == 0 )
		{
			intpDataPtr->nowSpeed = intpDataPtr->newFeedrate;
			intpDataPtr->feedrate = intpDataPtr->newFeedrate;
			intpDataPtr->speedState = SPEED_CONST;
			intpDataPtr->accelN = 0;
			intpDataPtr->duceN = 0;
			intpDataPtr->constN = intpDataPtr->overPathLength / ( intpDataPtr->newFeedrate * intpDataPtr->cyclingTime);
			intpDataPtr->resN = 1;
			intpDataPtr->resLength = intpDataPtr->overPathLength - intpDataPtr->newFeedrate * intpDataPtr->constN;
			intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;

		}
		else
		{
			for( i = 1; i < intpDataPtr->newDuceN + 1; i++ )
			{
				k += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
			}

			if( intpDataPtr->overPathLength < k + intpDataPtr->newFeedrate * intpDataPtr->cyclingTime )
			{
				k = 0;
				for( i = 1; intpDataPtr->overPathLength > k + intpDataPtr->vStep * intpDataPtr->cyclingTime * i; i++ )
				{
					k += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
					intpDataPtr->newDuceN = i - 1;
				}
				k -= intpDataPtr->vStep * intpDataPtr->cyclingTime * ( i - 1 );
				intpDataPtr->accelN = 0;
				intpDataPtr->constN = ( intpDataPtr->overPathLength - k ) / intpDataPtr->newFeedrate;
				intpDataPtr->feedrate = intpDataPtr->vStep * ( intpDataPtr->newDuceN + 1 );
				intpDataPtr->duceN = intpDataPtr->newFeedrate;
				intpDataPtr->resLength = intpDataPtr->overPathLength - k - intpDataPtr->newFeedrate * intpDataPtr->cyclingTime * intpDataPtr->constN;
				intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;

				for( i = intpDataPtr->accelHold; i >= 0; i -= intpDataPtr->vStep )
				{
					n++;
					if( i < intpDataPtr->resHold && i +intpDataPtr->vStep > intpDataPtr->resHold )
					{
						intpDataPtr->resN = n;
					}
				}
				intpDataPtr->speedState = SPEED_CONST;
			}
		}
	}
	else
	{
		intpDataPtr->newDuceN = intpDataPtr->newFeedrate / intpDataPtr->vStep;

		for( i = 1; i < abs( intpDataPtr->newAccelN ) + 1; i++ )
		{
			l += ( intpDataPtr->vStep * i + intpDataPtr->nowSpeed ) * intpDataPtr->cyclingTime;
		}

		for( i = 1; i < intpDataPtr->newDuceN + 1; i++ )
		{
			k += intpDataPtr->vStep * intpDataPtr->cyclingTime * i;
		}

		if( intpDataPtr->overPathLength < l + k + intpDataPtr->newFeedrate * intpDataPtr->cyclingTime )
		{
			l = 0;

			for( i = 1; intpDataPtr->overPathLength > 2 * l + k + ( intpDataPtr->vStep * i * intpDataPtr->newAccelN / abs( intpDataPtr->newAccelN ) + intpDataPtr->nowSpeed ) * intpDataPtr->cyclingTime; i++ )
			{
				l += ( intpDataPtr->vStep * i * intpDataPtr->newAccelN / abs( intpDataPtr->newAccelN ) + intpDataPtr->nowSpeed ) * intpDataPtr->cyclingTime;
				n = ( intpDataPtr->vStep * i * intpDataPtr->newAccelN / abs( intpDataPtr->newAccelN ) + intpDataPtr->nowSpeed ) * intpDataPtr->cyclingTime / intpDataPtr->vStep;
				for( x = 1; x < n + 1; x++ )
				{
					k += ( intpDataPtr->vStep * i + intpDataPtr->nowSpeed ) - intpDataPtr->vStep * x;
				}
				intpDataPtr->newAccelN = ( i - 1 ) * intpDataPtr->newAccelN / abs( intpDataPtr->newAccelN ); 
			}
			l -= intpDataPtr->vStep * intpDataPtr->cyclingTime * (i - 1);
			intpDataPtr->constN = 1;
			intpDataPtr->feedrate = intpDataPtr->vStep * (intpDataPtr->accelN + 1) + intpDataPtr->nowSpeed;
			intpDataPtr->duceN = intpDataPtr->newDuceN;
			intpDataPtr->accelN = intpDataPtr->newAccelN;

		}
		else
		{
			intpDataPtr->feedrate = intpDataPtr->newFeedrate;
			intpDataPtr->constN = ( intpDataPtr->overPathLength - k - l ) / ( intpDataPtr->feedrate * intpDataPtr->cyclingTime );		
		}

		intpDataPtr->accelHold = intpDataPtr->feedrate - intpDataPtr->vStep;	
		intpDataPtr->resLength = intpDataPtr->overPathLength - ( k + l ) - intpDataPtr->newFeedrate * intpDataPtr->cyclingTime * intpDataPtr->constN;
		intpDataPtr->resHold = intpDataPtr->resLength / intpDataPtr->cyclingTime;
		intpDataPtr->duceN = intpDataPtr->newDuceN;
		intpDataPtr->accelN = intpDataPtr->newAccelN;

		for( i = intpDataPtr->accelHold; i >= 0; i -= intpDataPtr->vStep )
		{
			n++;
			if( i < intpDataPtr->resHold && i +intpDataPtr->vStep > intpDataPtr->resHold )
			{
				intpDataPtr->resN = n;
			}
		}
		if( intpDataPtr->newDuceN == 0 )
		{
			intpDataPtr->resN = 1;
		}

		intpDataPtr->speedState = SPEED_UP;
	}
	return true;
}

//**********************************************

//**********************************************
int intpRotateExe( INTP_DATA *intpDataPtr )
{
	int i;
	intpDataPtr->intpCounter++;

	slope( intpDataPtr );// montFeed and intpEnd

	intpDataPtr->deltaLength = intpDataPtr->nowSpeed * intpDataPtr->cyclingTime;
	intpDataPtr->sumDeltaLength += intpDataPtr->deltaLength;

	//if( abs( intpDataPtr->pathLength - intpDataPtr->sumDeltaLength ) < intpDataPtr->deltaLength )
	if( intpDataPtr->intpCounter == intpDataPtr->accelN + intpDataPtr->constN + intpDataPtr->duceN + 2 )
	{
		for( i = 0; i < 3; i++ )
		{
			intpDataPtr->uvwOld[i] = intpDataPtr->uvwNew[i];
			intpDataPtr->uvwNew[i] = intpDataPtr->uvwEnd[i];	
		}

		intpDataPtr->intpEnd = true;
	}

	else
	{
		for( i = 0; i < 3; i++ )
		{
			intpDataPtr->uvwOld[i] = intpDataPtr->uvwNew[i];
			intpDataPtr->uvwNew[i] = intpDataPtr->uvwStart[i] + intpDataPtr->sumDeltaLength * intpDataPtr->angleFactor[i];	
		}

		intpDataPtr->intpEnd = false;
	}

	uvwToXyz( intpDataPtr->xyzNew, intpDataPtr->uvwNew );

	for( i = 0; i < 3; i++ )
	{
		sysLinkDataPtr->intpToSysData.newSettingValueUVW[i] = intpDataPtr->uvwNew[i];
		sysLinkDataPtr->intpToSysData.newSettingValue[i] = intpDataPtr->xyzNew[i];
	}
	
	if( sysLinkDataPtr->sysToIntpData.feedChange == true )
	{
		if( intpDataPtr->speedState == SPEED_DOWN )
		{
			sysLinkDataPtr->sysToIntpData.feedChange = false;
		}
		else
		{
			intpDataPtr->intpCounter = 0;
			intpDataPtr->newFeedrate = ( sysLinkDataPtr->sysToIntpData.feedOverride / 100. ) * intpDataPtr->oldFeedrate;
			if( intpDataPtr->newFeedrate == 0 )
			{
				intpDataPtr->feedrate = 0;
				intpDataPtr->speedState = SPEED_CONST;
			}
			else
			{
				rotOverride( intpDataPtr );
				sysLinkDataPtr->sysToIntpData.feedChange = false;
			}
		}
	}

	if( intpDataPtr->intpEnd == true )
	{
		intpDataPtr->intpEnd = false;
		intpDataPtr->intpState = INTP_ROTATE_CLOSE;
	}

	return true;
}

//**********************************************

//**********************************************
int intpRotateClose( INTP_DATA *intpDataPtr )
{
	//output end position
	//change intp state
	intpDataPtr->intpState = INTP_IDLE;
	intpDataPtr->speedState = SPEED_UP;
	intpDataPtr->intpCounter = 0;
	intpDataPtr->sumDeltaLength = 0;
	return true;
}

//**********************************************

//**********************************************
int intpHold( INTP_DATA *intpDataPtr )
{
	int i;

	if( sysLinkDataPtr->pannelInput.feedHold == false )
	{
		intpDataPtr->speedState = SPEED_UP;
		intpDataPtr->intpCounter = 0;
		
		if( sysLinkDataPtr->opMode == MEM_MODE || sysLinkDataPtr->opMode == MDI_MODE )
		{
			newBlockProcessing( intpDataPtr );
		}
		else
		{
			intpDataPtr->sumDeltaLength = 0;

			for( i = 0; i < 3; i++ )
			{
				intpDataPtr->xyzEnd[i] = intpDataPtr->xyzNew[i];
				intpDataPtr->uvwEnd[i] = intpDataPtr->uvwNew[i];
			}
			intpDataPtr->intpState = INTP_IDLE;
		}

		return true;
	}

	if( intpDataPtr->nowSpeed != 0 )
	{
		intpDataPtr->nowSpeed -= intpDataPtr->vStep;

		if( intpDataPtr->nowSpeed < 0 )
			intpDataPtr->nowSpeed = 0;

		intpDataPtr->deltaLength = intpDataPtr->nowSpeed * intpDataPtr->cyclingTime;
		intpDataPtr->sumDeltaLength += intpDataPtr->deltaLength;
		
		if( intpDataPtr->pathBlock.blockCommand == G00_MOTION || intpDataPtr->pathBlock.blockCommand == G01_MOTION )
		{
			for( i = 0; i<3; i++ )
			{
				if( intpDataPtr->intpState == INTP_LIN_EXE )
				{
					intpDataPtr->xyzOld[i] = intpDataPtr->xyzStart[i];
					intpDataPtr->xyzNew[i] = intpDataPtr->xyzStart[i] + intpDataPtr->sumDeltaLength * intpDataPtr->linFactor[i];
				}
				else if( intpDataPtr->intpState == INTP_ROTATE_EXE )
				{
					intpDataPtr->uvwOld[i] = intpDataPtr->uvwNew[i];
					intpDataPtr->uvwNew[i] = intpDataPtr->uvwStart[i] + intpDataPtr->sumDeltaLength * intpDataPtr->angleFactor[i];
				}
			}
		}

		else if( intpDataPtr->pathBlock.blockCommand == G02_MOTION || intpDataPtr->pathBlock.blockCommand == G03_MOTION )
		{
			intpDataPtr->sumDeltaAngle = intpDataPtr->sumDeltaLength / intpDataPtr->pathLength * intpDataPtr->moveAng;

			if( intpDataPtr->plane == XY_PLANE )
			{
				intpDataPtr->xyzNew[0] = intpDataPtr->ijk[0] + intpDataPtr->radius * cos( degToRad( intpDataPtr->startAng + intpDataPtr->sumDeltaAngle ));
				intpDataPtr->xyzNew[1] = intpDataPtr->ijk[1] + intpDataPtr->radius * sin( degToRad( intpDataPtr->startAng + intpDataPtr->sumDeltaAngle ));
			}
		}

		if( intpDataPtr->intpState == INTP_LIN_EXE )
		{
			xyzToUvw( intpDataPtr->xyzNew, intpDataPtr->uvwNew );
		}
		else if( intpDataPtr->intpState == INTP_ROTATE_EXE )
		{
			uvwToXyz( intpDataPtr->xyzNew, intpDataPtr->uvwNew );
		}

		for( i = 0; i < 3; i++ )
		{
			sysLinkDataPtr->intpToSysData.newSettingValueUVW[i] = intpDataPtr->uvwNew[i];
			sysLinkDataPtr->intpToSysData.newSettingValue[i] = intpDataPtr->xyzNew[i];
		}
	}
	else
	{
		return true;
	}

	return true;
}

//**********************************************

//**********************************************
int intpReset( INTP_DATA *intpDataPtr )
{
	int i;

	if( intpDataPtr->nowSpeed != 0 )
	{
		intpDataPtr->nowSpeed -= intpDataPtr->vStep;

		if( intpDataPtr->nowSpeed < 0 )
			intpDataPtr->nowSpeed = 0;

		intpDataPtr->deltaLength = intpDataPtr->nowSpeed * intpDataPtr->cyclingTime;
		intpDataPtr->sumDeltaLength += intpDataPtr->deltaLength;
		
		if( intpDataPtr->pathBlock.blockCommand == G00_MOTION || intpDataPtr->pathBlock.blockCommand == G01_MOTION )
		{
			for( i = 0; i<3; i++ )
			{
				if( intpDataPtr->intpState == INTP_LIN_EXE )
				{
					intpDataPtr->xyzOld[i] = intpDataPtr->xyzStart[i];
					intpDataPtr->xyzNew[i] = intpDataPtr->xyzStart[i] + intpDataPtr->sumDeltaLength * intpDataPtr->linFactor[i];
				}
				else if( intpDataPtr->intpState == INTP_ROTATE_EXE )
				{
					intpDataPtr->uvwOld[i] = intpDataPtr->uvwNew[i];
					intpDataPtr->uvwNew[i] = intpDataPtr->uvwStart[i] + intpDataPtr->sumDeltaLength * intpDataPtr->angleFactor[i];
				}
			}
		}

		else if( intpDataPtr->pathBlock.blockCommand == G02_MOTION || intpDataPtr->pathBlock.blockCommand == G03_MOTION )
		{
			intpDataPtr->sumDeltaAngle = intpDataPtr->sumDeltaLength / intpDataPtr->pathLength * intpDataPtr->moveAng;

			if( intpDataPtr->plane == XY_PLANE )
			{
				intpDataPtr->xyzNew[0] = intpDataPtr->ijk[0] + intpDataPtr->radius * cos( degToRad( intpDataPtr->startAng + intpDataPtr->sumDeltaAngle ));
				intpDataPtr->xyzNew[1] = intpDataPtr->ijk[1] + intpDataPtr->radius * sin( degToRad( intpDataPtr->startAng + intpDataPtr->sumDeltaAngle ));
			}
		}

		if( intpDataPtr->coordinate == XYZ_COORDINATE )
		{
			xyzToUvw( intpDataPtr->xyzNew, intpDataPtr->uvwNew );
		}
		else if( intpDataPtr->coordinate == UVW_COORDINATE )
		{
			uvwToXyz( intpDataPtr->xyzNew, intpDataPtr->uvwNew );
		}

		for( i = 0; i < 3; i++ )
		{
			sysLinkDataPtr->intpToSysData.newSettingValueUVW[i] = intpDataPtr->uvwNew[i];
			sysLinkDataPtr->intpToSysData.newSettingValue[i] = intpDataPtr->xyzNew[i];
		}
	}
	else
	{
		intpDataPtr->intpState = INTP_IDLE;
		intpDataPtr->speedState = SPEED_UP;
		intpDataPtr->intpCounter = 0;
		intpDataPtr->cyclingTime = 0.033;
		intpDataPtr->g00Feed = ( 0.5 / intpDataPtr->cyclingTime );
		intpDataPtr->g00AngFeed = ( 0.36 / intpDataPtr->cyclingTime );
		intpDataPtr->accel = 200.0;
		intpDataPtr->vStep = intpDataPtr->accel * intpDataPtr->cyclingTime;
		intpDataPtr->absoluteT = 0;
		intpDataPtr->accelN = 0;
		intpDataPtr->accelHold = 0;
		intpDataPtr->angleMean = 0;
		intpDataPtr->block = 0;
		intpDataPtr->constN = 0;
		intpDataPtr->deceLength = 0;
		intpDataPtr->deltaLength = 0;
		intpDataPtr->duceHold = 0;
		intpDataPtr->duceN = 0;
		intpDataPtr->dwellTimeCounter = 0;
		intpDataPtr->endAng = 0;
		intpDataPtr->feedrate = 0;
		intpDataPtr->intpEnd = false;
		intpDataPtr->linIntpCounter = 0;
		intpDataPtr->moveAng = 0;
		intpDataPtr->nowSpeed = 0;
		intpDataPtr->pathLength = 0;
		intpDataPtr->planeLength = 0;
		intpDataPtr->radius = 0;
		intpDataPtr->relativeT = 0;
		intpDataPtr->resHold = 0;
		intpDataPtr->resLength = 0;
		intpDataPtr->resN = 0;
		intpDataPtr->startAng = 0;
		intpDataPtr->sumDeltaAngle = 0;
		intpDataPtr->sumDeltaLength = 0;	

		PATH_MOTION* pathMotionPtr;
		pathMotionPtr = &intpDataPtr->pathBlock.motionFunction.pathMotion;	

		pathMotionPtr->coordinate = NULL_COORDINATE;
		pathMotionPtr->feedrate = 0;
		pathMotionPtr->g60 = false;
		pathMotionPtr->m00 = false;
		pathMotionPtr->m01 = false;
		pathMotionPtr->relative = false;

		for( i = 0; i < 3; i++ )
		{
			intpDataPtr->xyzEnd[i] = intpDataPtr->xyzNew[i];
			intpDataPtr->uvwEnd[i] = intpDataPtr->uvwNew[i];
			pathMotionPtr->ijkCoordinate[i] = 0;
			pathMotionPtr->uvwCoordinate[i] = 0;
			pathMotionPtr->xyzCoordinate[i] = 0;
			pathMotionPtr->ijkSendValid[i] = false;
			pathMotionPtr->uvwSendValid[i] = false;
			pathMotionPtr->xyzSendValid[i] = false;
		}

		sysLinkDataPtr->pannelInput.reset = false;
	}

	return GOOD;
}


//**********************************************

//**********************************************
int intpEmStop( INTP_DATA *intpDataPtr )
{
	int i;

	if( intpDataPtr->nowSpeed != 0 )
	{
		intpDataPtr->nowSpeed -= intpDataPtr->vStep;

		if( intpDataPtr->nowSpeed < 0 )
			intpDataPtr->nowSpeed = 0;

		intpDataPtr->deltaLength = intpDataPtr->nowSpeed * intpDataPtr->cyclingTime;
		intpDataPtr->sumDeltaLength += intpDataPtr->deltaLength;
		
		if( intpDataPtr->pathBlock.blockCommand == G00_MOTION || intpDataPtr->pathBlock.blockCommand == G01_MOTION )
		{
			for( i = 0; i<3; i++ )
			{
				if( intpDataPtr->intpState == INTP_LIN_EXE )
				{
					intpDataPtr->xyzOld[i] = intpDataPtr->xyzStart[i];
					intpDataPtr->xyzNew[i] = intpDataPtr->xyzStart[i] + intpDataPtr->sumDeltaLength * intpDataPtr->linFactor[i];
				}
				else if( intpDataPtr->intpState == INTP_ROTATE_EXE )
				{
					intpDataPtr->uvwOld[i] = intpDataPtr->uvwNew[i];
					intpDataPtr->uvwNew[i] = intpDataPtr->uvwStart[i] + intpDataPtr->sumDeltaLength * intpDataPtr->angleFactor[i];
				}
			}
		}

		else if( intpDataPtr->pathBlock.blockCommand == G02_MOTION || intpDataPtr->pathBlock.blockCommand == G03_MOTION )
		{
			intpDataPtr->sumDeltaAngle = intpDataPtr->sumDeltaLength / intpDataPtr->pathLength * intpDataPtr->moveAng;

			if( intpDataPtr->plane == XY_PLANE )
			{
				intpDataPtr->xyzNew[0] = intpDataPtr->ijk[0] + intpDataPtr->radius * cos( degToRad( intpDataPtr->startAng + intpDataPtr->sumDeltaAngle ));
				intpDataPtr->xyzNew[1] = intpDataPtr->ijk[1] + intpDataPtr->radius * sin( degToRad( intpDataPtr->startAng + intpDataPtr->sumDeltaAngle ));
			}
		}

		if( intpDataPtr->intpState == INTP_LIN_EXE )
		{
			xyzToUvw( intpDataPtr->xyzNew, intpDataPtr->uvwNew );
		}
		else if( intpDataPtr->intpState == INTP_ROTATE_EXE )
		{
			uvwToXyz( intpDataPtr->xyzNew, intpDataPtr->uvwNew );
		}

		for( i = 0; i < 3; i++ )
		{
			sysLinkDataPtr->intpToSysData.newSettingValueUVW[i] = intpDataPtr->uvwNew[i];
			sysLinkDataPtr->intpToSysData.newSettingValue[i] = intpDataPtr->xyzNew[i];
		}
	}
	else
	{
		sysLinkDataPtr->emStop = false;
	}

	return true;
}

//**********************************************

//**********************************************
int intpMain( INTP_DATA *intpDataPtr )
{
	if( sysLinkDataPtr->emStop == true )
	{
		intpDataPtr->intpState = INTP_EM_STOP;
	}

	if( sysLinkDataPtr->pannelInput.reset == true )
	{
		intpDataPtr->intpState = INTP_RESET;
	}

	if( sysLinkDataPtr->pannelInput.feedHold == true )
	{
		if( intpDataPtr->intpState != INTP_HOLD)
			intpDataPtr->holdState = intpDataPtr->intpState;
		intpDataPtr->intpState = INTP_HOLD;
	}

	switch( intpDataPtr->intpState )
	{
	case INTP_IDLE:
		intpIdle( intpDataPtr );
		break;

	case INTP_LIN_PRE:
		intpLinPre( intpDataPtr );
		break;

	case INTP_LIN_EXE:
		intpLinExe( intpDataPtr );
		break;

	case INTP_LIN_CLOSE:
		intpLinClose( intpDataPtr );
		break;

	case INTP_CIR_PRE:
		intpCirPre( intpDataPtr );
		break;

	case INTP_CIR_EXE:
		intpCirExe( intpDataPtr );
		break;

	case INTP_CIR_CLOSE:
		intpCirClose( intpDataPtr );
		break;

	case INTP_ROTATE_PRE:
		intpRotatePre( intpDataPtr );
		break;

	case INTP_ROTATE_EXE:
		intpRotateExe( intpDataPtr );
		break;

	case INTP_ROTATE_CLOSE:
		intpRotateClose( intpDataPtr );
		break;

	case DWELL_TIME_EXE:
		dwellTimeExe( intpDataPtr );
		break;

	case INTP_HOLD:
		intpHold( intpDataPtr );
		break;

	case INTP_EM_STOP:
		intpEmStop( intpDataPtr );
		break;

	case INTP_RESET:
		intpReset( intpDataPtr );
		break;

	case INTP_CLOSE:
		intpClose( intpDataPtr );
		break;
	}
	return true;
}

//**********************************************

//**********************************************
int intpClose( INTP_DATA *intpDataPtr )
{
	return true;
}
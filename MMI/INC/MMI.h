#ifndef _MMI_H
#define _MMI_H

#define HOME_MODE  1
#define MEM_MODE   2
#define JOG_MODE   3
#define MDI_MODE   4
#define WHEEL_MODE 5


typedef struct
{
	int	  counter;
	int   handWheelGain;
	int   feedOverride;
	bool  cycleStart;
	int   opMode;
	bool  feedHold;
	bool  reset;
	bool  coordiPlus[3];
	bool  coordiMinu[3];
	bool  xyzMode;
	bool  teachIn;
	bool  record;
	bool  feedChange;

} MMI_DATA;

int mmiInit( MMI_DATA* mmiDataPtr );
int mmiMain( MMI_DATA* mmiDataPtr );

#endif
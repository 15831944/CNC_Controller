#include "..\..\FIFO\INC\fifo.h"
#include "math.h"

#define HOME_MODE  1
#define MEM_MODE   2
#define JOG_MODE   3
#define MDI_MODE   4
#define WHEEL_MODE 5
#define TEACH_MODE 6

#define INTP_IDLE  0
#define INTP_EXE   1
#define INTP_CLOSE 2
#define INTP_HOLD  3
#define INTP_EM_STOP  4
#define INTP_RESET  5

#define GOOD 100

#define PI 4.*atan(1.)

#define SPEED_UP       200
#define SPEED_CONST    201
#define SPEED_DOWN     202

#define DWELL_TIME_EXE 1000
#define INTP_LIN_PRE   1001
#define INTP_LIN_EXE   1002
#define INTP_LIN_CLOSE 1003
#define INTP_CIR_PRE   1004
#define INTP_CIR_EXE   1005
#define INTP_CIR_CLOSE 1006
#define INTP_ROTATE_PRE   1007
#define INTP_ROTATE_EXE   1008
#define INTP_ROTATE_CLOSE 1009

#define MAXRATE        60

typedef struct
{
	int    intpState;
	int    speedState;
	int    holdState;
	int    intpCounter;

	double x;
	double y;
	double z;

	int    dwellTimeCounter;

	double xyzStart[3];
	double xyzEnd[3];
	double xyzNew[3];
	double xyzOld[3];
	double xyzDelta[3];
	double uvwStart[3];
	double uvwEnd[3];
	double uvwNew[3];
	double uvwOld[3];
	double uvwDelta[3];
	double ijk[3];
	double center[3];

	char   block;
	double plane;
	int    coordinate;
	double feedrate;
	double oldFeedrate;
	double newFeedrate;
	double g00Feed;
	double g00AngFeed;
	double nowSpeed;
	double radius;

	double pathLength;
	double overPathLength;
	double angleMean;
	double deltaLength;
	double planeLength;
	double resLength;
	double deceLength;
	double sumDeltaLength;
	double sumDeltaAngle;

	int    linIntpCounter;
	double linFactor[3];
	double angleFactor[3];
	double absoluteT;
	double relativeT;
	double cyclingTime;
	bool   intpEnd;

	double startAng;
	double endAng;
	double moveAng;

	int    accelN;
	int    constN;
	int    duceN;
	int    newAccelN;
	int    newDuceN;
	int    resN;
	double accelHold;
	double duceHold;
	double resHold;
	double accel;
	double vStep;

	PATH_BLOCK pathBlock;

} INTP_DATA;

int intpInit( INTP_DATA* intpDataPtr );
int intpMain( INTP_DATA* intpDataPtr );
int intpClose( INTP_DATA* intpDataPtr );
int intpReset( INTP_DATA* intpDataPtr );

int intpIdle( INTP_DATA* intpDataPtr );
int intpExe( INTP_DATA* intpDataPtr );

int g04DwellTime( INTP_DATA *intpDataPtr );
int dwellTimeExe( INTP_DATA *intpDataPtr );
int gMotion( INTP_DATA *intpDataPtr );
int m30ProgramEnd( INTP_DATA *intpDataPtr );
int newBlockProcessing( INTP_DATA *intpDataPtr );
int intpLinExe( INTP_DATA *intpDataPtr );
int intLinClose( INTP_DATA *intpDataPtr );
int intCirExe( INTP_DATA *intpDataPtr );
int intCirClose( INTP_DATA *intpDataPtr );
int intEmStop( INTP_DATA *intpDataPtr );

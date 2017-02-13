//#include "..\..\DRV\INC\DRV.h"
#include "stdio.h"
#include "..\..\FIFO\INC\fifo.h"
#include "..\..\DEC\INC\dec.h"

#define SYS_IDLE       0
#define SYS_HOME_MODE  1
#define SYS_MEM_MODE   2
#define SYS_JOG_MODE   3
#define SYS_MDI_MODE   4
#define SYS_WHEEL_MODE 5

#define MEM_START         0// memory/auto mode state
#define MEM_SEND_NC_FILE  1
#define MEM_NC_RUNNING    2

#define JOG_START         0// 
#define JOG_WRITE_FIFO    1
#define JOG_RUNNING       2

#define MDI_START         0//
#define MDI_SEND_NC_FILE  1
#define MDI_NC_RUNNING    2

#define WH_START          0//
#define WH_WRITE_FIFO     1
#define WH_RUNNING        2

#define HM_START          0// 
#define HM_WRITE_FIFO     1
#define HM_CLOSE          2



#define WRITE_SUCCESS 9998


typedef struct
{
	double	mSetValue;			// setting value in mm	(or degree)
	double	mActValue;			// actual value in mm	(or degree)
	double	resolution;			// resolution, mm/inc	(or degree/inc)
	int		relInc;				// (set - oldSet) / resolution

} AXIS_DATA;

typedef struct
{
	double	xyzAxis[3];
	double	uvwAxis[3];
	int     coordinate;

} RECORD_DATA;

typedef struct
{
	int    sysState;
	int    memState;
	int    jogState;
	int    mdiState;
	int    whState;
	int    hmState;
	char   fileName[100];
	bool   fileValid;
	char   ncBuffer[100000];
	double x;
	double y;
	double z;

	char   block;
	PATH_BLOCK  sysToIntpBlock;

	
	AXIS_DATA	axisData[3];
	double      axisInitValue[3];

	RECORD_DATA recordData[100];
	int         recordCounter;
	FILE        *saveFilePtr;
	char        savefileName[100];

} SYS_DATA;

int sysInit( SYS_DATA *sysDataPtr );
int sysIdle( SYS_DATA *sysDataPtr );
int sysMain( SYS_DATA* sysDataPtr );
int sysMemMode( SYS_DATA *sysDataPtr );
int sysJogMode( SYS_DATA *sysDataPtr );
int sysMdiMode( SYS_DATA *sysDataPtr );
int sysHwMode( SYS_DATA *sysDataPtr );
int sysClose( SYS_DATA* sysDataPtr );
int sysReset( SYS_DATA* sysDataPtr );

int memStart( SYS_DATA *sysDataPtr );
int memSendNcFile( SYS_DATA *sysDataPtr );
int memNcRunning( SYS_DATA *sysDataPtr );

int record( SYS_DATA *sysDataPtr );
int teachEnd( SYS_DATA *sysDataPtr );

int realKnl( SYS_DATA *sysDataPtr );

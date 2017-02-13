#include "..\..\FIFO\INC\fifo.h"

#define HOME_MODE  1
#define MEM_MODE   2
#define JOG_MODE   3
#define MDI_MODE   4
#define WHEEL_MODE 5

typedef struct
{
	char fileName[2000];
	bool fileValid;
	char ncBuffer[100000];
} SYS_TO_DEC_LINK_DATA;

typedef struct
{
	DEC_TO_INTP_FIFO      decToIntpFifo;
} DEC_TO_INTP_LINK_DATA;

typedef struct
{
	SYS_TO_INTP_FIFO      sysToIntpFifo;
	double                feedOverride;
	bool                  feedChange;
	
} SYS_TO_INTP_LINK_DATA;

typedef struct
{
	double newSettingValue[3];
	double newSettingValueUVW[3];
	int    coordinate;
	bool   m30;
} INTP_TO_SYS_LINK_DATA;

typedef struct
{
	bool	cycleStart;
	bool	feedHold;
	bool    reset;
	bool    emStop;
	bool	coordiPlus[3];
	bool	coordiMinu[3];
	bool    xyzMode;
	int		handWheelGain;
	bool    record;

} PANNEL_INPUT;

typedef struct
{
	bool    m30;
} PANNEL_OUTPUT;

typedef struct
{
	SYS_TO_DEC_LINK_DATA  sysToDecLinkData;
	SYS_TO_INTP_LINK_DATA sysToIntpData;
	DEC_TO_INTP_LINK_DATA decToIntpData;
	INTP_TO_SYS_LINK_DATA intpToSysData;
	PANNEL_INPUT          pannelInput;
	PANNEL_OUTPUT         pannelOutput;
	double                cyclingTime;
	bool                  emStop;
	int                   opMode;
} SYS_LINK_DATA;

int sysLinkInit( SYS_LINK_DATA *sysLinkDataPtr );
int sysLinkReset( SYS_LINK_DATA *sysLinkDataPtr );
#define SYS_IDLE       0
#define SYS_MEM_MODE   1
#define SYS_JOG_MODE   2
#define SYS_MDI_MODE   3
#define SYS_HW_MODE    4

#define MEM_START // memory/auto mode state
#define MEM_SEND_NC_FILE
#define MEM_NC_RUNNING
#define JOG_START // 
#define MDI_START //
#define HW_START  //

typedef struct
{
	int    sysState;
	int    memState;
	int    jogState;
	int    mdiState;
	int    hwState;
	char   fileName[100];
	bool   fileValid;
	double x;
	double y;
	double z;

	char   block;

} SYS_DATA;

int sysInit( SYS_DATA* );
int sysMain( SYS_DATA* );
int sysClose( SYS_DATA* );
int sysReste( SYS_DATA* );
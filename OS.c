
#include "OS.h"

static uint8 Resolution=0;  			  /* g_variable for saving resolution */
static uint8 Timer_used=0;  			  /* g_variable for saving timer to use */
static uint8 End_of_active_consumers=0;   /* g_variable for defining end of active  */
static uint16 Period_Flags_Arr[NumOfTasks];      /* g_array for incrementing time of active functions in it instead of one global for all fns  */
OS_Buffer_t Tasks_arr_t[NumOfTasks];    /*Buffer for tasks required*/



/* sortTasks Function
 * it used for sorting the tasks regarding priority and whatever create first.
 * the sorting is done first thing in scheduler before entering super loop .
 *
 */

static void sortTasks(void)
{
	OS_Buffer_t tempStr;
	uint8 i=0,j=0;
	for(i=0;i<End_of_active_consumers-1;i++)
	{
		for (j=0;j<End_of_active_consumers-1-i;j++)
		{
			if(	Tasks_arr_t[j].PERIORITY >Tasks_arr_t[j+1].PERIORITY)
			{
				tempStr=Tasks_arr_t[j];
				Tasks_arr_t[j]=Tasks_arr_t[j+1];
				Tasks_arr_t[j+1]=tempStr;
			}

		}

	}
}


/*
 * Time increase function
 * it aims to increase each flag related to each task instead of depending on one flag to mitigate errors and overrun as possible
 * returns error code
 *
 * */


static void  Time_Increase(void)
{static uint32 counter=0;
counter++;
if(counter%(4*Resolution) == 0)
{uint8 Flag_Count;
for(Flag_Count=0;Flag_Count<End_of_active_consumers;Flag_Count++)
{
	Period_Flags_Arr[Flag_Count]++;
}
}
}



/*
 * OS Initialization Function
 * address of structure is passed to it which includes time_id and resolution
 * returns error code
 *
 *
 * */

EnumOSError_t OS_Init(OS_Conf_t *OS_Config_STR)
{Timer_setCallBack(Time_Increase);
EnumOSError_t error =NO_ERROR;
if(OS_Config_STR != NULL)
{
	Resolution= OS_Config_STR ->TICK;
	Timer_used=OS_Config_STR->Timer_ID;
	Timer_Init(Timer_used);
	Timer_Start(Timer_used);
}
else
{
	error=OS_INIT_INVALID_ARGUMENT;
}
return error;
}

/*
 * OS Create Task
 * it aims to put task's information in the buffer
 * returns error code
 *
 * */
EnumOSError_t Create_Task(uint16 period_val, CONSUMER_PTR FuncName,uint8 periority)
{
	EnumOSError_t error = NO_ERROR;
	if(FuncName!=NULL)
	{
		if(End_of_active_consumers< NumOfTasks)
		{
			Tasks_arr_t[End_of_active_consumers].FUNC=FuncName;
			Tasks_arr_t[End_of_active_consumers].PERIOD=period_val;
			Tasks_arr_t[End_of_active_consumers].PERIORITY=periority;
			Tasks_arr_t[End_of_active_consumers].STATUS=INIT;
			End_of_active_consumers++;
		}
		else
		{
			error = OS_START_FULL_BUFFER;
		}
	}
	else
	{
		error = OS_START_INVALID_ARGUMENT;

	}

	return  error;
}



/*
 * OS Delete Task
 * it aims to delete task's information from the buffer
 * returns error code
 *
 * */

EnumOSError_t Task_Delete(CONSUMER_PTR Func_name)
{EnumOSError_t error = NO_ERROR;
uint8 Count ;

if(Func_name!=NULL)
{
	for( Count=0;Count<End_of_active_consumers;Count++)
	{
		if(Tasks_arr_t[Count].FUNC == Func_name)
		{
			Tasks_arr_t[Count].FUNC =NULL;
			Tasks_arr_t[Count].STATUS=DELETED;
			while (Count<End_of_active_consumers-1)

			{
				Tasks_arr_t[Count]=Tasks_arr_t[Count+1];
				Count++;
			}
			End_of_active_consumers--;
		}
		else
		{
			error=OS_STOP_INVALID_ARGUMENT;
		}
	}
}
else
{
	error=OS_STOP_INVALID_ARGUMENT;
}
return error;
}

/*
 * SOS Run
 * it aims to execute each task every certain period according to priority
 * returns none
 *
 * */

void SOS_Run(void)
{
	static uint8 Schedular_Count;
	sortTasks();
	while(1)
	{
		for(Schedular_Count =0 ; Schedular_Count<End_of_active_consumers;Schedular_Count++)
		{

			switch (Tasks_arr_t[Schedular_Count].STATUS)
			{
			case INIT:
				if( (Period_Flags_Arr[Schedular_Count] ==(Tasks_arr_t[Schedular_Count].PERIOD) ))
				{
					Tasks_arr_t[Schedular_Count].STATUS=READY;

				}
				break;
			case WAITING:
				if( (Period_Flags_Arr[Schedular_Count] ==(Tasks_arr_t[Schedular_Count].PERIOD) ))
				{
					Tasks_arr_t[Schedular_Count].STATUS=READY;
				}
				break;
			case READY:
				(*Tasks_arr_t[Schedular_Count].FUNC)();
				Period_Flags_Arr[Schedular_Count]=0;
				Tasks_arr_t[Schedular_Count].STATUS=WAITING;

				break;

			case DELETED:
				break;
			}
		}
		cpuSleep();
	}
}





#ifndef OS_H_
#define OS_H_

#include "TIMER.h"
#include <avr/interrupt.h>
#include "OS_pconfg.h"
#include "OS_preconfg.h"

typedef void(*CONSUMER_PTR)(void);

//typedef enum {INVALID_ARGUMENT=-1,FULL_BUFFER=-2,NO_ERROR=1}error_code;
//typedef enum {OS_INIT=-100,TIMER_START=-200,OS_STOP=300,OS_SChedular=400}service_id;
typedef enum {OS_INIT_INVALID_ARGUMENT,TIMER_START_FULL_BUFFER,OS_START_INVALID_ARGUMENT,OS_STOP_INVALID_ARGUMENT,OS_START_FULL_BUFFER,NO_ERROR}EnumOSError_t;

typedef enum {
	STATE0,STATE1,
}Enum_STATUS_CHECK_t;



typedef enum{INIT=1,READY,WAITING,DELETED}Enum_OS_STATUS_t;


typedef struct{
	uint8 Timer_ID;
	uint8 TICK;
}OS_Conf_t;

extern OS_Conf_t OS_Config_STR_t;

typedef struct
{
	volatile uint16 PERIOD;
	CONSUMER_PTR FUNC;
	uint8 PERIORITY;
	Enum_OS_STATUS_t STATUS;

}OS_Buffer_t;

extern OS_Buffer_t OS_Buffer_arr[NumOfTasks];

EnumOSError_t OS_Init(OS_Conf_t *OS_Config_STR);

EnumOSError_t Create_Task(uint16 period_val, CONSUMER_PTR FuncName,uint8 periority);
EnumOSError_t Task_Delete(CONSUMER_PTR Func_name);
void SOS_Run();



#endif

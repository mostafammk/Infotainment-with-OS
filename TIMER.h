/*
 * TIMER.h
 *
 *  Created on: Sep 22, 2019
 *      Author: Rafaat
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "registers.h"
#include "stdtypes.h"
#include "TIMER_cnfg.h"
typedef void(*g_ptrFn)(void);

//typedef enum{NOK,OK}status;

status Timer_Init(uint8 Timer);
void Timer_Start(uint8 Timer);
status Timer_SetPrescaler(uint8 Timer);
void Timer_Stop(uint8 Timer);
void Timer_setCallBack(g_ptrFn a_ptr);
void cpuSleep(void);

//void delay(uint32 delay,uint8 Timer,void (*ptr)(void));


#endif /* TIMER_H_ */

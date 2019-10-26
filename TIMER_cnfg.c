/*
 * TIMER_cnfg.c
 *
 *  Created on: Sep 22, 2019
 *      Author: Rafaat
 */


#include "TIMER_cnfg.h"




Timer_Config Timer_arr[NUM_OF_TIMERS] ={
		{TIMER_0,NORMAL,CLK_DIV_8,ISR_EN}
};

extern Timer_Config Timer_arr[NUM_OF_TIMERS];

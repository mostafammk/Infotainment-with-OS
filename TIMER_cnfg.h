/*
 * TIMER_cnfg.h
 *
 *  Created on: Sep 22, 2019
 *      Author: Rafaat
 */

#ifndef TIMER_CNFG_H_
#define TIMER_CNFG_H_


#include "stdtypes.h"
typedef	enum{timer0,NUM_OF_TIMERS}timers;

#define INITI 1


#define TIMER_0		0
#define TIMER_1		1
#define TIMER_2		2


/* TCCR0 Bits*/
#define CS00	0
#define CS01	1
#define CS02	2
#define WGM01	3
#define	COM00	4
#define	COM01	5
#define WGM00	6
#define	FOC0	7

/* TIMSK Bits*/
#define TOIE0	0
#define OCIE0	1
#define TOIE1	2
#define OCIE1B	3
#define	OCIE1A	4
#define	TICIE1	5
#define TOIE2	6
#define	OCIE2	7


/* TIFR Bits*/
#define TOV0	0
#define OCF0	1
#define TOV1	2
#define OCF1B	3
#define	OCF1A	4
#define	ICF1	5
#define TOV2	6
#define	OCF2	7


typedef	enum{NORMAL,CTC}Mode;
typedef	enum{NO_CLK,CLK_DIV_1,CLK_DIV_8,CLK_DIV_64,CLK_DIV_256,CLK_DIV_1024,CLK_RISING,CLK_FALING}Prescaler;
typedef	enum{ISR_EN,ISR_DS}ISR;
typedef	struct{
	uint8 Timer;
	uint8 Mode;
	uint8 Prescaler;
	uint8 ISR;
}Timer_Config;

Timer_Config Timer_arr[NUM_OF_TIMERS];
#endif /* TIMER_CNFG_H_ */

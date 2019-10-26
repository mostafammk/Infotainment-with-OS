/*
 * DIO_cnfg.h
 *
 * Created: 23 , 9 , 2019
 *  Author: Ya3koob
 */


#ifndef DIO_CNFG_H_
#define DIO_CNFG_H_

#define NUM_OF_PINS 11

#include "stdtypes.h"

typedef struct
{
	uint8 PORT;
	uint8 PIN;
	uint8 DIR;
	uint8 OUT;
	uint8 RES;
}DIO_cnfg_pin;

DIO_cnfg_pin DIO_cnfg_arr[NUM_OF_PINS];

#endif /* DIO_CNFG_H_ */

/*
 * LCD_confg.h
 *
 *  Created on: Oct 24, 2019
 *      Author: Mostafa-Khalil
 */

#ifndef LCD_POSTBUILDCONFG_H_
#define LCD_POSTBUILDCONFG_H_

#include "stdtypes.h"

#define FOUR_BIT_MODE 0
#define EIGHT_BIT_MODE 1

typedef struct
{
	uint8 mode;
	uint8 CTRL_port;
	uint8 RS_pin;
	uint8 RW_pin;
	uint8 En_pin;
	uint8 DATA_port;
	uint8 DATA_startPin;
}LCD_STconfig;

extern LCD_STconfig *LCD_ptrConfig;

#endif /* LCD_POSTBUILDCONFG_H_ */

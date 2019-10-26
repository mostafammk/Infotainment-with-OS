/*
 * LCD_confg.c
 *
 *  Created on: Oct 24, 2019
 *      Author: Mostafa-Khalil
 */

#include "DIO.h"
#include "LCD_PostBuildconfg.h"

LCD_STconfig LCD_config =
{
		FOUR_BIT_MODE,
		PORT_A,
		PIN1,
		PIN2,
		PIN3,
		PORT_A,
		PIN4
		};

LCD_STconfig *LCD_ptrConfig = &LCD_config;

/*
 * LCD.c
 *
 *  Created on: Oct 24, 2019
 *      Author: Mostafa-Khalil
 */

#include "LCD.h"
#include "DIO.h"
#include <util/delay.h>

#include <registers.h>

#define  delay 1000

static uint8 LCD_sendCommand(uint8 LOC_Command)
{
	static uint8 LCD_state = SENDING_UPPER_FOUR_BITS;
	uint8 LOC_sendCommandFuncStatus;
	uint8 indx;
	uint8 bitValue=0;

	switch(LCD_state)
	{
	case SENDING_UPPER_FOUR_BITS:

		DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->RS_pin,LOW);
		DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->RW_pin,LOW);

		if(LCD_ptrConfig->mode == FOUR_BIT_MODE)
		{
			for(indx = 4 ; indx<8 ; indx++)
			{
				bitValue = (LOC_Command>>indx)&(1u);
				DIO_write_pin_value(LCD_ptrConfig->DATA_port,(LCD_ptrConfig->DATA_startPin+indx-4),bitValue);
			}
			DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->En_pin,HIGH);
			DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->En_pin,LOW);
		}
		else if(LCD_ptrConfig->mode == EIGHT_BIT_MODE)
		{

		}
		else
		{
			LOC_sendCommandFuncStatus = LCD_wrongmode;
		}

		LCD_state = SENDING_LOWER_FOUR_BITS;
		LOC_sendCommandFuncStatus = LCD_state;
		break;

	case SENDING_LOWER_FOUR_BITS:
		if(LCD_ptrConfig->mode == FOUR_BIT_MODE)
		{
			for(indx = 0 ; indx<4 ; indx++)
			{
				bitValue = (LOC_Command>>indx)&(1u);
				DIO_write_pin_value(LCD_ptrConfig->DATA_port,(LCD_ptrConfig->DATA_startPin+indx),bitValue);
			}
			DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->En_pin,HIGH);
			DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->En_pin,LOW);
		}
		else if(LCD_ptrConfig->mode == EIGHT_BIT_MODE)
		{

		}
		else
		{
			LOC_sendCommandFuncStatus = LCD_wrongmode;
		}
		LCD_state = LCD_WAITING;
		LOC_sendCommandFuncStatus = LCD_state;

		break;
	case LCD_WAITING:
		LCD_state = SENDING_UPPER_FOUR_BITS;
		LOC_sendCommandFuncStatus = LCD_DONE;

		break;
	}



	/*	else if(LCD_ptrConfig->mode == EIGHT_BIT_MODE)
	{
		DIO_write_port_value(LCD_ptrConfig->DATA_port,LOC_Command);

		_delay_us(1000);

		DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->En_pin,LOW);

		_delay_us(1000);
	}*/


	return LOC_sendCommandFuncStatus;
}


uint8 LCD_init(LCD_STconfig *COPY_LCD_ptrStrConfig)
{
	uint8 LOC_initFuncStatus = LCD_WAITING;
	static uint8 LCD_init_status = INIT_FIRST_FOURBIT_COMM;
	static uint8 commandStatus = LCD_WAITING;

	if(COPY_LCD_ptrStrConfig->mode == FOUR_BIT_MODE)
	{
		switch(LCD_init_status)
		{
		case INIT_FIRST_FOURBIT_COMM:

			commandStatus = LCD_sendCommand(FOUR_BIT_COMMAND);
			if(commandStatus == LCD_DONE)
			{
				LCD_init_status = INIT_SECOND_FOURBIT_COMM;
			}
			break;
		case INIT_SECOND_FOURBIT_COMM:

			commandStatus = LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
			if(commandStatus == LCD_DONE)
			{
				LCD_init_status = INIT_CURSOR_OFF_COMMAND;
			}
			break;
		}

	}
	else if(COPY_LCD_ptrStrConfig->mode == EIGHT_BIT_MODE)
	{
		//LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);
	}
	else
	{
		LOC_initFuncStatus = LCD_wrongmode;
	}

	if(LCD_init_status == INIT_CURSOR_OFF_COMMAND)
	{
		commandStatus = LCD_sendCommand(CURSOR_OFF);
		if(commandStatus == LCD_DONE)
		{
			LOC_initFuncStatus = INIT_CLEAR_COMM;
			LCD_init_status = INIT_CLEAR_COMM;
		}
	}
	else if(LCD_init_status == INIT_CLEAR_COMM)
	{
		commandStatus = LCD_sendCommand(CLEAR_COMMAND);
		if(commandStatus == LCD_DONE)
		{
			LOC_initFuncStatus = LCD_DONE;
			LCD_init_status = INIT_FIRST_FOURBIT_COMM;
		}
	}

	return LOC_initFuncStatus;
}



uint8 LCD_displayChar (uint8 LOC_Data)
{
	uint8 LOC_dispCharFuncStatus;
	static uint8 LCD_state = SENDING_UPPER_FOUR_BITS;
	uint8 indx;
	uint8 bitValue=0;

	switch(LCD_state)
	{
	case SENDING_UPPER_FOUR_BITS:

		DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->RS_pin,HIGH);
		DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->RW_pin,LOW);

		if(LCD_ptrConfig->mode == FOUR_BIT_MODE)
		{
			for(indx = 4 ; indx<8 ; indx++)
			{
				bitValue = (LOC_Data>>indx)&(1u);
				DIO_write_pin_value(LCD_ptrConfig->DATA_port,(LCD_ptrConfig->DATA_startPin+indx-4),bitValue);
			}

			DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->En_pin,HIGH);
		}
		else if(LCD_ptrConfig->mode == EIGHT_BIT_MODE)
		{

		}
		else
		{
			LOC_dispCharFuncStatus = LCD_wrongmode;
		}


		LCD_state = SENDING_LOWER_FOUR_BITS;
		LOC_dispCharFuncStatus = LCD_state;
		break;
	case SENDING_LOWER_FOUR_BITS:

		if(LCD_ptrConfig->mode == FOUR_BIT_MODE)
		{
			DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->En_pin,LOW);
			for(indx = 0 ; indx<4 ; indx++)
			{
				bitValue = (LOC_Data>>indx)&(1u);
				DIO_write_pin_value(LCD_ptrConfig->DATA_port,(LCD_ptrConfig->DATA_startPin+indx),bitValue);
			}
			DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->En_pin,HIGH);
			DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->En_pin,LOW);
		}
		else if(LCD_ptrConfig->mode == EIGHT_BIT_MODE)
		{

		}
		else
		{
			LOC_dispCharFuncStatus = LCD_wrongmode;
		}

		LCD_state = LCD_WAITING;
		LOC_dispCharFuncStatus = LCD_state;
		break;
	case LCD_WAITING:
		LCD_state = SENDING_UPPER_FOUR_BITS;
		LOC_dispCharFuncStatus = LCD_DONE;
		break;
	}

	//_delay_us(1000);



	//_delay_us(1000);


	/*	else if(LCD_ptrConfig->mode == EIGHT_BIT_MODE)
	{
		DIO_write_port_value(LCD_ptrConfig->DATA_port,LOC_Data);

		_delay_us(1);

		DIO_write_pin_value(LCD_ptrConfig->CTRL_port,LCD_ptrConfig->En_pin,LOW);

		_delay_us(1);
	}*/


	return LOC_dispCharFuncStatus;
}

uint8 LCD_displayString (const uint8 *LOC_ptrString)
{
	uint8 LOC_dispStr_FuncStatus= LCD_STR_NOT_COMPELET;
	uint8 Check_Char_Is_Done= LCD_WAITING;
	static uint8 l_Str_Counter=0;
	static uint8 Check_Shift_Is_Done = LCD_WAITING;

	if(LOC_ptrString[l_Str_Counter]!='\0'){
		if((l_Str_Counter == 16) && (Check_Shift_Is_Done != LCD_DONE))
		{
			Check_Shift_Is_Done = LCD_gotoRowColumn(1,0);
		}
		else
		{
			Check_Char_Is_Done=LCD_displayChar(LOC_ptrString[l_Str_Counter]);
			if(Check_Char_Is_Done==LCD_DONE){
				l_Str_Counter++;
				Check_Shift_Is_Done = LCD_WAITING;
			}
		}
	}
	else if(LOC_ptrString[l_Str_Counter]=='\0'){
		LOC_dispStr_FuncStatus=LCD_STR_COMPELET;
		l_Str_Counter = 0;
	}
	return LOC_dispStr_FuncStatus;
}


uint8 LCD_displayStringRowColumn (uint8 LOC_row, uint8 LOC_col,const uint8 *LOC_ptrString)
{
	uint8 LOC_dispStrRowColFuncStatus;


	return LOC_dispStrRowColFuncStatus;
}

uint8 LCD_clear()
{
	uint8 LOC_clearFuncStatus;
	uint8 commStatus;

	commStatus = LCD_sendCommand(CLEAR_COMMAND);

	if(commStatus == LCD_DONE)
	{
		LOC_clearFuncStatus = LCD_DONE;
	}
	else
	{
		LOC_clearFuncStatus = LCD_WAITING;
	}

	return LOC_clearFuncStatus;
}

uint8 LCD_gotoRowColumn(uint8 LOC_row, uint8 LOC_col)
{
	uint8 LOC_goToRowColFuncStatus;
	uint8 Address;
	uint8 commStatus;
	switch(LOC_row)
	{
	case 0:
		Address=LOC_col;
		break;
	case 1:
		Address=LOC_col+0x40;
		break;
	}
	commStatus = LCD_sendCommand(Address|SET_CURSOR_LOCATION);
	if(commStatus == LCD_DONE)
	{
		LOC_goToRowColFuncStatus = LCD_DONE;
	}
	else
	{
		LOC_goToRowColFuncStatus = LCD_WAITING;
	}
	return LOC_goToRowColFuncStatus;
}


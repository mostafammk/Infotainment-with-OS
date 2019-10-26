
#include "keypad.h"



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
uint8 KeyPad_getPressedKey(uint8* Pressed_Key)
{
	uint8 retVal=0;
	uint8 keyFound = 0;
	uint8 result=0;
	static uint8 prevResult = NO_KEY_PRESSED;
	uint8 col,row,gotKey=1;
	*Pressed_Key = NO_KEY_PRESSED;
	for(col=0;col<N_col;col++) /* loop for columns */
	{

		DIO_set_port_direction( PORT_C,(0b00100000<<col));

		DIO_write_port_value(PORT_C,(~(0b00100000<<col)));

		for(row=0;row<N_row;row++) /* loop for rows */
		{DIO_read_pin_value(PORT_C,(row+2),&gotKey);
		if(gotKey==0) /* if the switch is press in this row */
		{
			result = (row*N_col)+col+1;
			//*Pressed_Key = result;
			keyFound = 1;
		}
		}
	}


	if(keyFound == 1)
	{
		if(result == prevResult)
		{
			*Pressed_Key = result;
			retVal = KEYPAD_DONE;

		}
		else if((result != prevResult))
		{
			prevResult = result;
			retVal = NO_KEY_PRESSED;
		}

		keyFound = 0;
	}
	else
	{
		prevResult = NO_KEY_PRESSED;
		retVal = NO_KEY_PRESSED;
	}

	return retVal;

}


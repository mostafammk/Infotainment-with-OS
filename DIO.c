/*
 * DIO.c
 *
 *  Created on: 9 ,24, 2019
 *      Author: Ya3koob
 */
#include "DIO.h"

/************************************
  * Function Name:DIO_INIT
  * Use:to initialize all required pins (check configuration files)
  * Input:void
  * Return:status(OK,NOK)
 ************************************
  */

uint8 DIO_init (void)
{
	uint8 retval = OK;
	uint8 loop_index = 0;

	if (NUM_OF_PINS>MAX_NUM_OF_PINS) return retval=NOK; //check number of pins



	for(loop_index = 0;loop_index<NUM_OF_PINS;loop_index++)
	{

	if( !(DIO_cnfg_arr[loop_index].PIN>=PIN0 && DIO_cnfg_arr[loop_index].PIN<=PIN7) )
			return retval=NOK;                  //check pin entered

	if(DIO_cnfg_arr[loop_index].DIR == OUTPUT) // check direction

	{
		switch(DIO_cnfg_arr[loop_index].PORT)  // if output check port

		{
		case PORT_A:
			set_bit(REG_DDRA,DIO_cnfg_arr[loop_index].PIN); // set direction as o/p
			break;

		case PORT_B:
			set_bit(REG_DDRB,DIO_cnfg_arr[loop_index].PIN);
			break;

		case PORT_C:
			set_bit(REG_DDRC,DIO_cnfg_arr[loop_index].PIN);
			break;

		case PORT_D:
			set_bit(REG_DDRD,DIO_cnfg_arr[loop_index].PIN);
			break;
		default :
			retval =NOK; // not PORTA,B,C,D
		}

	}
	else if (DIO_cnfg_arr[loop_index].DIR == INPUT)

	{



		switch(DIO_cnfg_arr[loop_index].PORT)

		{
		case PORT_A:

			clr_bit(REG_DDRA,DIO_cnfg_arr[loop_index].PIN); //set direction as i/p

			if (DIO_cnfg_arr[loop_index].RES == PULLUP)  // set res type (pull up or ext)
				set_bit(REG_PORTA,DIO_cnfg_arr[loop_index].PIN);
			else if (DIO_cnfg_arr[loop_index].RES == EXTRES)
				clr_bit(REG_PORTA,DIO_cnfg_arr[loop_index].PIN);
			else {
					return retval=NOK;                 // not pull up or external
			}


			break;

		case PORT_B:

			clr_bit(REG_DDRB,DIO_cnfg_arr[loop_index].PIN);

			if (DIO_cnfg_arr[loop_index].RES == PULLUP)
				set_bit(REG_PORTB,DIO_cnfg_arr[loop_index].PIN);
			else if (DIO_cnfg_arr[loop_index].RES == EXTRES)
				clr_bit(REG_PORTB,DIO_cnfg_arr[loop_index].PIN);
			else {

				return retval=NOK;
			}			break;

		case PORT_C:

			clr_bit(REG_DDRC,DIO_cnfg_arr[loop_index].PIN);

			if (DIO_cnfg_arr[loop_index].RES == PULLUP)
				set_bit(REG_PORTC,DIO_cnfg_arr[loop_index].PIN);
			else if (DIO_cnfg_arr[loop_index].RES == EXTRES)
				clr_bit(REG_PORTC,DIO_cnfg_arr[loop_index].PIN);
			else {

				return retval=NOK;
			}			break;

		case PORT_D:

			clr_bit(REG_DDRD,DIO_cnfg_arr[loop_index].PIN);

			if (DIO_cnfg_arr[loop_index].RES == PULLUP)
				set_bit(REG_PORTD,DIO_cnfg_arr[loop_index].PIN);
			else if (DIO_cnfg_arr[loop_index].RES == EXTRES)
				clr_bit(REG_PORTD,DIO_cnfg_arr[loop_index].PIN);
			else {

				return retval=NOK;
			}			break;
		default :
			retval =NOK;


		}
	}
	else // not input or output
	{
		retval =NOK;

	}



	if(DIO_cnfg_arr[loop_index].OUT == HIGH)
	{switch(DIO_cnfg_arr[loop_index].PORT)

	{
	case PORT_A:
		set_bit(REG_PORTA,DIO_cnfg_arr[loop_index].PIN);
		break;

	case PORT_B:
		set_bit(REG_PORTB,DIO_cnfg_arr[loop_index].PIN);
		break;

	case PORT_C:
		set_bit(REG_PORTC,DIO_cnfg_arr[loop_index].PIN);
		break;

	case PORT_D:
		set_bit(REG_PORTD,DIO_cnfg_arr[loop_index].PIN);
		break;
	default :
		retval =NOK;


	}

	}
	else if (DIO_cnfg_arr[loop_index].OUT==LOW)
	{
		switch(DIO_cnfg_arr[loop_index].PORT)

		{
		case PORT_A:
			clr_bit(REG_PORTA,DIO_cnfg_arr[loop_index].PIN);


			break;

		case PORT_B:
			clr_bit(REG_PORTB,DIO_cnfg_arr[loop_index].PIN);

			break;

		case PORT_C:
			clr_bit(REG_PORTC,DIO_cnfg_arr[loop_index].PIN);


			break;

		case PORT_D:
			clr_bit(REG_PORTD,DIO_cnfg_arr[loop_index].PIN);


			break;
		default :
			retval =NOK;

		}
	}
	else
	{
		retval =NOK;

	}
	}
	return retval;
}


/************************************
  * Function Name:DIO_set_pin_direction
  * use:to set certain direction of a pin (i.e Output/Input)
  * Input:port_id,pin_number,value
  * Return:status(OK,NOK)
 ************************************
  */

uint8 DIO_set_pin_direction(uint8 port_id,uint8 pin_number,uint8 direction)
{

	uint8 retval = OK;

	if( !(pin_number>=PIN0 && pin_number<=PIN7) )

		return retval=NOK;

	if(direction==OUTPUT)
	{

		switch (port_id)
		{
		case PORT_A:
			set_bit(REG_DDRA,pin_number);
			break;

		case PORT_B:
			set_bit(REG_DDRB,pin_number);
			break;

		case PORT_C:
			set_bit(REG_DDRC,pin_number);
			break;

		case PORT_D:
			set_bit(REG_DDRD,pin_number);
			break;
		default :
			retval =NOK;

		}

	}
	else if (direction ==INPUT)
	{
		switch (port_id)
		{
		case PORT_A:
			clr_bit(REG_DDRA,pin_number);
			break;

		case PORT_B:
			clr_bit(REG_DDRB,pin_number);
			break;

		case PORT_C:
			clr_bit(REG_DDRC,pin_number);
			break;

		case PORT_D:
			clr_bit(REG_DDRD,pin_number);
			break;
		default :
			retval =NOK;

		}

	}
	else
	{
		retval =NOK;
	}
	return retval;

}

/************************************
  * Function Name:DIO_write_pin_value
  * use:to write digital value(0,1) on certain pin
  * Input:port_id,pin_number,value
  * Return:status(OK,NOK)
 ************************************
  */

uint8 DIO_write_pin_value(uint8 port_id,uint8 pin_number,uint8 value)
{

	uint8 retval = OK;

	if( !(pin_number>=PIN0 && pin_number<=PIN7) )

		return retval=NOK;


	if( value==HIGH )
	{

		switch (port_id)
		{
		case PORT_A:

			set_bit(REG_PORTA,pin_number);


			break;

		case PORT_B:
			set_bit(REG_PORTB,pin_number);
			break;

		case PORT_C:
			set_bit(REG_PORTC,pin_number);
			break;

		case PORT_D:
			set_bit(REG_PORTD,pin_number);
			break;
		default :
			retval =NOK;

		}
	}


	else if (value==LOW)
	{

		switch (port_id)
		{
		case PORT_A:
			clr_bit(REG_PORTA,pin_number);
			break;

		case PORT_B:
			clr_bit(REG_PORTB,pin_number);
			break;

		case PORT_C:
			clr_bit(REG_PORTC,pin_number);
			break;

		case PORT_D:
			clr_bit(REG_PORTD,pin_number);
			break;
		default :
			retval =NOK;

		}

	}
	else
	{
		retval =NOK;

	}
	return retval;
}
/************************************
  * Function Name:DIO_read_pin_value
  * use:to read a digital value(0,1) from certain pin
  * Input:port_id,pin_number,pointer to put got value in.
  * Return:status(OK,NOK)
 ************************************
  */
uint8  DIO_read_pin_value(uint8 port_id,uint8 pin_number,uint8* got)
{
	uint8 retval = OK;

	if(! (pin_number>=PIN0 && pin_number<=PIN7) )

		return retval=NOK;



	switch (port_id)
	{
	case PORT_A:
		*got=get_bit(REG_PINA,pin_number);
		break;

	case PORT_B:
		*got=get_bit(REG_PINB,pin_number);
		break;

	case PORT_C:
		*got=get_bit(REG_PINC,pin_number);
		break;

	case PORT_D:
		*got=get_bit(REG_PIND,pin_number);
		break;
	default :
		retval=NOK;
	}
	return retval;

}

/************************************
  * Function Name:DIO_set_port_direction
  * use:to set certain direction of a pin (i.e Output/Input )
  * Input:port_id,value that express direction (i.e 0x0f)
  * Return:status(OK,NOK)
 ************************************
  */
uint8 DIO_set_port_direction(uint8 port_id,uint8 value)
{
	uint8 retval = OK;


	if(! (value>=0 && value<=255) )

		return retval=NOK;

	switch (port_id)
	{
	case PORT_A:
		REG_DDRA=value;
		break;

	case PORT_B:
		REG_DDRB=value;
		break;

	case PORT_C:
		REG_DDRC=value;
		break;

	case PORT_D:
		REG_DDRD=value;
		break;
	default:
		retval=NOK;
	}
	return retval;

}
/************************************
  * Function Name:DIO_write_pin_value
  * use:to write digital value(0,1) on the port (i.e 0xff all output)
  * Input:port_id,pin_number,value
  * Return:status(OK,NOK)
 ************************************
  */
uint8 DIO_write_port_value(uint8 port_id,uint8 value)
{
	uint8 retval = OK;


	if(! (value>=0 && value<=255) )

		return retval=NOK;

	switch (port_id)
	{
	case PORT_A:
		REG_PORTA=value;
		break;

	case PORT_B:
		REG_PORTB=value;
		break;

	case PORT_C:
		REG_PORTC=value;
		break;

	case PORT_D:
		REG_PORTD=value;
		break;
	default:
		retval=NOK;
	}
	return retval;
}
/************************************
  * Function Name:DIO_read_port_value
  * use:to read a digital value(0,1) from certain pin
  * Input:port_id,,pointer to put got value in.
  * Return:status(OK,NOK)
 ************************************
  */
uint8 DIO_read_port_value(uint8 port_id,uint8* got)

{
	uint8 retval = OK;

	switch (port_id)
	{
	case PORT_A:
		*got=REG_PINA;
		break;

	case PORT_B:
		*got=REG_PINB;
		break;

	case PORT_C:
		*got=REG_PINC;
		break;

	case PORT_D:
		*got=REG_PIND;
		break;
	default:
		retval=NOK;
	}

	return retval;


}


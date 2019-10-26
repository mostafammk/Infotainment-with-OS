/*
 * DIO.h
 *
 * Created: 23  , 9 , 2019
 *  Author: Ya3koob
 */


#ifndef DIO_H_
#define DIO_H_

#include "DIO_cnfg.h"
#include "registers.h"
#include "macros.h"




#define MAX_NUM_OF_PINS	(uint8)32

#define OK 1
#define NOK 0


#define PORT_A		0
#define PORT_B		1
#define PORT_C		2
#define PORT_D		3

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7

#define OUTPUT		1
#define INPUT		0

#define HIGH		1
#define LOW			0

#define PULLUP		1
#define EXTRES		0

#define INITIALIZED			1
#define NOT_INITIALIZED		0

#define NA 0xff



uint8 DIO_init (void);
uint8 DIO_set_pin_direction(uint8 port_id,uint8 pin_number,uint8 direction);
uint8 DIO_write_pin_value(uint8 port_id,uint8 pin_number,uint8 value);
uint8 DIO_read_pin_value(uint8 port_id,uint8 pin_number,uint8* got);
uint8 DIO_set_port_direction(uint8 port_id,uint8 value);
uint8 DIO_write_port_value(uint8 port_id,uint8 value);
uint8 DIO_read_port_value(uint8 port_id,uint8* got);




#endif /* DIO_H_ */

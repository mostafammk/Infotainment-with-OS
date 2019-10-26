/*
 * LCD.h
 *
 *  Created on: Oct 24, 2019
 *      Author: Mostafa-Khalil
 */

#ifndef LCD_H_
#define LCD_H_

#include "LCD_PostBuildconfg.h"

#define FOUR_BIT_COMMAND 0x02
#define CLEAR_COMMAND 0x01
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80
#define CURSOR_OFF 0x0C

#define SENDING_UPPER_FOUR_BITS 1
#define SENDING_LOWER_FOUR_BITS 2
#define LCD_DONE 3
#define LCD_WAITING 4
#define LCD_wrongmode 5
#define INIT_FIRST_FOURBIT_COMM 6
#define INIT_SECOND_FOURBIT_COMM 7
#define INIT_EIGHTBIT_COMM 8
#define INIT_CLEAR_COMM 9
#define INIT_CURSOR_OFF_COMMAND 10
#define LCD_STR_NOT_COMPELET 11
#define LCD_STR_COMPELET 12

/*typedef enum
{
	LCD_OK, LCD_NOK, LCD_wrongmode
}LCD_retError;*/

extern uint8 LCD_init(LCD_STconfig *COPY_LCD_ptrStrConfig);
extern uint8 LCD_displayChar (uint8 LOC_Data);
extern uint8 LCD_displayString (const uint8 *LOC_ptrString);
extern uint8 LCD_displayStringRowColumn (uint8 LOC_row, uint8 LOC_col,const uint8 *LOC_ptrString);
extern uint8 LCD_clear();
extern uint8 LCD_gotoRowColumn(uint8 LOC_row, uint8 LOC_col);


#endif /* LCD_H_ */

/*
 * registers.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Mina Raouf
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "stdtypes.h"

// SREG & Interrupts Masks and their corresponding Bits
#define INT0_BIT 	6
#define INT1_BIT  	7
#define INT2_BIT  	5
#define I_BIT 		7

#define REG_TWBR 	*((volatile uint8 *) 0x20)  // Two wire serial Interface Bit Rate Reg.
#define REG_TWSR 	*((volatile uint8 *) 0x21)
#define REG_TWAR 	*((volatile uint8 *) 0x22)
#define REG_TWDR 	*((volatile uint8 *) 0x23)  // Two wire serial Interface Data Reg.
#define REG_ADCL 	*((volatile uint8 *) 0x24)  // ADC Data Reg. Low Byte
#define REG_ADCH 	*((volatile uint8 *) 0x25)  // ADC Data Reg. High Byte
#define REG_ADCSRA	*((volatile uint8 *) 0x26)
#define REG_ADMUX	*((volatile uint8 *) 0x27)
#define REG_ACSR	*((volatile uint8 *) 0x28)
#define REG_UBRRL	*((volatile uint8 *) 0x29)  // USART Baud Rate Reg. Low Byte

#define REG_UCSRB	*((volatile uint8 *) 0x2A)
#define REG_UCSRA	*((volatile uint8 *) 0x2B)
#define REG_UDR		*((volatile uint8 *) 0x2C)  // USART I/O Data Reg.
#define REG_SPCR	*((volatile uint8 *) 0x2D)
#define REG_SPSR	*((volatile uint8 *) 0x2E)
#define REG_SPDR	*((volatile uint8 *) 0x2F)  // SPI Data Reg.

#define REG_PIND 	*((volatile uint8 *) 0x30) // PIN D for input
#define REG_DDRD 	*((volatile uint8 *) 0x31) // Direction Register
#define REG_PORTD 	*((volatile uint8 *) 0x32) // Port for output
#define REG_PINC 	*((volatile uint8 *) 0x33) // PIN C for input
#define REG_DDRC 	*((volatile uint8 *) 0x34) // Direction Register C
#define REG_PORTC 	*((volatile uint8 *) 0x35) // Port C for output
#define REG_PINB 	*((volatile uint8 *) 0x36) // PIN B for input
#define REG_DDRB 	*((volatile uint8 *) 0x37) // Direction Register
#define REG_PORTB 	*((volatile uint8 *) 0x38) // Port B for output
#define REG_PINA 	*((volatile uint8 *) 0x39) // PIN A for input
#define REG_DDRA 	*((volatile uint8 *) 0x3A) // Direction A Register
#define REG_PORTA 	*((volatile uint8 *) 0x3B) // Port C for output

#define REG_EECR 	*((volatile uint8 *) 0x3C)
#define REG_EEDR 	*((volatile uint8 *) 0x3D)  // EEPROM Data Reg.
#define REG_EEARL 	*((volatile uint8 *) 0x3E)  // EEPROM Address Reg. Low Byte
#define REG_EEARH 	*((volatile uint8 *) 0x3F)

#define REG_UCSRC 	*((volatile uint8 *) 0x40)  // REFER TO UART DESC. TO ACCESS THEM
#define REG_UBRRH 	*((volatile uint8 *) 0x40)  // REFER TO UART DESC. TO ACCESS THEM
#define REG_WDTCR 	*((volatile uint8 *) 0x41)
#define REG_ASSR 	*((volatile uint8 *) 0x42)
#define REG_OCR2 	*((volatile uint8 *) 0x43)  // Timer / Counter2 Output Compare Reg.
#define REG_TCNT2 	*((volatile uint8 *) 0x44)  // Timer / Counter2 (8 Bits)
#define REG_TCCR2 	*((volatile uint8 *) 0x45)  // Timer 2 Control Register
#define REG_ICR1L 	*((volatile uint8 *) 0x46)  // Timer / Counter1 Input Capture Reg. Low Byte
#define REG_ICR1H 	*((volatile uint8 *) 0x47)  // Timer / Counter1 Input Capture Reg. High Byte
#define REG_OCR1BL 	*((volatile uint8 *) 0x48)  // Timer / Counter1 Output Compare Reg.B Low Byte
#define REG_OCR1BH 	*((volatile uint8 *) 0x49)  // Timer / Counter1 Output Compare Reg.B High Byte

#define REG_OCR1AL 	*((volatile uint8 *) 0x4A)  // Timer / Counter1 Output Compare Reg.A Low Byte
#define REG_OCR1AH 	*((volatile uint8 *) 0x4B)  // Timer / Counter1 Output Compare Reg.A High Byte
#define REG_TCNT1L 	*((volatile uint8 *) 0x4C)  // Timer / Counter1 Counter Reg. Low Byte
#define REG_TCNT1H 	*((volatile uint8 *) 0x4D)  // Timer / Counter1 Counter Reg. High Byte
#define REG_TCCR1B 	*((volatile uint8 *) 0x4E)
#define REG_TCCR1A 	*((volatile uint8 *) 0x4F)

#define REG_SFIOR 	*((volatile uint8 *) 0x50)
#define REG_OCDR 	*((volatile uint8 *) 0x51)  // On Chip Debug Reg.
#define REG_OSCCAL 	*((volatile uint8 *) 0x51)  // Oscillator Calibration Reg.
// Refer To Debugger Document To see how to access The Two Reg. in 0X51
#define REG_TCNT0 	*((volatile uint8 *) 0x52)  // Timer / Counter0 (8 Bits)
#define REG_TCCR0 	*((volatile uint8 *) 0x53)
#define REG_MCUCSR 	*((volatile uint8 *) 0x54)
#define REG_MCUCR 	*((volatile uint8 *) 0x55)
#define REG_TWCR 	*((volatile uint8 *) 0x56)
#define REG_SPMCR 	*((volatile uint8 *) 0x57)
#define REG_TIFR 	*((volatile uint8 *) 0x58)
#define REG_TIMSK 	*((volatile uint8 *) 0x59)

#define REG_GIFR 	*((volatile uint8 *) 0x5A)
#define REG_GICR 	*((volatile uint8 *) 0x5B)
#define REG_OCR0 	*((volatile uint8 *) 0x5C)  // Timer / Counter0 Output Compare Reg.
#define REG_SPL 	*((volatile uint8 *) 0x5D)
#define REG_SPH 	*((volatile uint8 *) 0x5E)
#define REG_SREG 	*((volatile uint8 *) 0x5F)




#endif /* REGISTERS_H_ */

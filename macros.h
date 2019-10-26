/*
 * macros.h
 *
 *  Created on: 9 , 24, 2019
 *      Author: Ya3koob
 */

#ifndef MACROS_H_
#define MACROS_H_
#define get_bit(var,bit) ((var&(1u<<bit))>>bit)
#define set_bit(var,bit) (var|=(1u<<bit))
#define clr_bit(var,bit) (var&=(~(1u<<bit)))
#define toggle_bit(var,bit) (var^=(1u<<bit))
#endif /* MACROS_H_ */

/*
 *	IR communication library
 */
 
// voorkom meerdere keren includen
#ifndef IR_H
#define IR_H

/* includes */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
 
/* function prototypes */
void IR_prepare_timer_send(void);
void IR_prepare_timer_receive(void);
void IR_send(uint8_t);
uint8_t IR_receive(void);
 
#ifdef __cplusplus
}
#endif
 
#endif // IR_H
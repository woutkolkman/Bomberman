/*
 *	IR communication library
 */

// voorkom meerdere keren includen
#ifndef IR_H
#define IR_H

/* includes */
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

/* function prototypes */
void IR_prepare_timer_send(void);
void IR_prepare_timer_receive(void);
void IR_send(uint8_t waarde);
uint8_t IR_receive(void);

#endif // IR_H
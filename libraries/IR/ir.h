/*
 *	IR communication library
 */

// voorkom meerdere keren includen
#ifndef IR_H
#define IR_H

/* includes */
//#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include "ir.cpp" // snelle fix voor linking error

/* function prototypes */
void IR_prepare(void);
void IR_send(uint8_t waarde);
uint8_t IR_receive(void);

#endif // IR_H

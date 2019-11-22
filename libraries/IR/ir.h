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
#include "ir.cpp" // snelle fix voor linking error

/* function prototypes */
void IR_prepare_send(void);
void IR_prepare_receive(void);
void IR_send(uint8_t waarde);
uint8_t IR_receive(void); // functie weghalen?
uint8_t getInput(void);

#endif // IR_H

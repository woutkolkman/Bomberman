/*
 *	IR communication library
 */


// voorkom meerdere keren includen
#ifndef IR_H
#define IR_H


/* defines */
// ...


/* includes */
//#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include <usart.h>


class ir
{
private:
//	volatile uint8_t prevcounter;
//	volatile unsigned int diffcounter;
//	volatile AANTAL_BITS_TYPE input;
//	volatile AANTAL_BITS_TYPE raw_input;
//	volatile uint8_t timer2_ovfs;
//	volatile int aantal_bits;
//	volatile uint8_t nieuwe_input;

protected:
//	void schakel_IR_LED(uint8_t/* aan*/);
//	void var_delay_ms(int/* ms*/);
//	void prepare_send(void);
//	void prepare_receive(void);

public:
//	void IR_prepare(void);
//	void IR_send(uint8_t/* waarde*/);
//	uint8_t IR_receive(void);
//	uint8_t IR_nieuwe_input(void);
};


/* function prototypes - gebruikt door functies in ir.cpp */
void schakel_IR_LED(uint8_t aan);
void var_delay_ms(int ms);
void prepare_send(void);
void prepare_receive(void);


/* function prototypes - te gebruiken voor main.cpp */
void IR_prepare(uint8_t frequentie); // frequentie kan alleen 38 of 56 zijn
void IR_send(uint8_t waarde);
uint8_t IR_receive(void);
uint8_t IR_nieuwe_input(void);


#endif // IR_H

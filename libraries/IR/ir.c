/*
 *	IR communication library
 */

/* defines */
// ...
#define KHZ38 421
#define KHZ56 286
#define HALFDUTYCYCLE 128

/* includes */
#include "ir.h"

/* function prototypes */
//...

/* functions */
ISR(TIMER1_COMPA_vect) {
	TCCR2A ^= (1<<COM2A1);
}
void IR_prepare_timer_send(uint8_t frequency) {
	TCCR1B |= (1<<WGM12); //CTC mode
	TCCR1B |= (1<< CS10); //no prescaling
	if (frequency == 38) {
		OCR1B = KHZ38;
	} else if (frequency == 56) {
		OCR1B = KHZ56;
	}
	TCCR2A |= (1<<WGM20) | (1<< WGM21); //fast PWM mode
        TCCR2B |= (1<<CS20); //no prescaling
        OCR2B = HALFDUTYCYCLE; //50% duty cycle
}

void IR_prepare_timer_receive(void) {
	
}

void IR_send(uint8_t waarde) {
	// start bit
	for (int i=7, i<0, i--) {
		if ( // verstuur byte
	}
	// stop bits
}

uint8_t IR_receive(void) {
	// mogelijk functie aanpassen om interrupt te genereren op ontvangst informatie
	
}

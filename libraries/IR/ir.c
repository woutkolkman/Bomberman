/*
 *	IR communication library
 */

/* defines */
// ...
//#define KHZ38 421 timer1 prescale 1
#define KHZ38 52 //timer2 prescale 8
#define DUTYCYCLE38 26 //duty cycle 50% 38KHz
//#define KHZ56 286 timer1 prescale 1
#define KHZ56 36 //timer2 prescale 8
#define DUTYCYCLE56 18 //duty cycle 50% 56KHz
#define CLEAR 0; //clear value for OCR2B
#define STARTBITVALUE //INVULLEN, kleiner of gelijk aan 65535 (wat veel te groot is)

/* includes */
#include "ir.h"

/* function prototypes */
//...

/* functions */

void IR_prepare_timer_send(uint8_t frequency) {
	TCCR2A |= (1<<WGM20) | (1<<WGM21);
	TCCR2B |= (1<<WGM22) //CTC, fast PWM
	TCCR2A |= (1<<COM2B1); //set above value, clear on bottom
	if (frequency == 38) {
		OCR2A = KHZ38;
		OCR2B = DUTYCYCLE38;
	} else if (frequency == 56) {
		OCR2A = KHZ56;
		OCR2B = DUTYCYCLE56;
	}
/*	TCCR0A |= (1<<WGM01); //CTC mode
*	TCCR0B |= (1<<CS01); //prescale 8
*	TCCR1B |= (1<<WGM12); //CTC mode
*	TCCR1B |= (1<< CS10); //no prescaling
*	if (frequency == 38) {
*		OCR0A = KHZ38;
*	} else if (frequency == 56) {
*		OCR0A = KHZ56;
*	}
*	TCCR2A |= (1<<WGM20) | (1<< WGM21); //fast PWM mode
*        TCCR2B |= (1<<CS20); //no prescaling
*        OCR2B = HALFDUTYCYCLE; //50% duty cycle
*/
}

void IR_prepare_timer_receive(void) {
	
}

void IR_send(uint8_t waarde) {
	// start bit
	while(TCNT1 < STARTBITVALUE)
		
	for (int i=7, i<0, i--) {
		if (waarde & (1<<i) { //is bit i 1?
			
		} else { //bit i is 0

		}
	}
	// stop bits
}

uint8_t IR_receive(void) {
	// mogelijk functie aanpassen om interrupt te genereren op ontvangst informatie
	
}

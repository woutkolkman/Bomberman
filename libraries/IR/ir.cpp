/*
 *	IR communication library
 */


/* defines */
//#define KHZ38 421 timer1 prescale 1
#define KHZ38 52 //timer2 prescale 8
#define DUTYCYCLE38 26 //duty cycle 50% 38KHz
//#define KHZ56 286 timer1 prescale 1
#define KHZ56 36 //timer2 prescale 8
#define DUTYCYCLE56 18 //duty cycle 50% 56KHz
#define STARTBITVALUE //INVULLEN, kleiner of gelijk aan 65535 (wat veel te groot is)

#define MARK 0
#define SPACE 1
#define BITS 32
#define HDR_MARK 9000
#define HDR_SPACE 4500
#define BIT_MARK 560
#define ONE_SPACE 1690
#define ZERO_SPACE 560
#define RPT_SPACE 2250


/* includes */
#include "ir.h"


/* function prototypes */
//...


/* ISR */
ISR (TIMER2_COMPB_vect) {
	#if FREQUENCY == 38 // aangeroepen elke 1,05ms
	
	#elif FREQUENCY == 56 // aangeroepen elke 0,71ms
	
	#else
	// exception error, geen khz gekozen
	#endif
}


/* functions */
void IR_prepare_timer_send(void) {
	TCCR2A |= (1<<WGM20) | (1<<WGM21); // Fast PWM
	TCCR2B |= (1<<WGM22); // CTC, fast PWM
	TCCR2A |= (1<<COM2B1); // set above value, clear on bottom
	#if FREQUENCY == 38
	OCR2A = KHZ38;
	OCR2B = DUTYCYCLE38;
	#elif FREQUENCY == 56
	OCR2A = KHZ56;
	OCR2B = DUTYCYCLE56;
	#else
	// exception error, geen khz gekozen
	#endif
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

//======================================================================


/*
 *	IR communication library
 */


/* defines */

#define KHZ38 52 //timer2 prescale 8
#define DUTYCYCLE38 26 //duty cycle 50% 38KHz
#define TOTALBIT38 1040 //40 keer knipperen
#define STARTBITVALUE38 //INVULLEN, kleiner of gelijk aan 1039 (wat veel te groot is)
#define BITIS1F38 //INVULLEN, kleiner of gelijk aan 1039
#define BITIS0F38 //INVULLEN, kleiner of gelijk aan 1039
#define STOPBITVALUE //INVULLEN, kleiner of gelijk aan 1039

#define KHZ56 36 //timer2 prescale 8
#define DUTYCYCLE56 18 //duty cycle 50% 56KHz
#define TOTALBIT56 720 //40 keer knipperen
#define STARTBITVALUE56 //INVULLEN, kleiner of gelijk aan of 719 (wat veel te groot is)
#define BITIS1F56 //INVULLEN, kleiner of gelijk aan 719
#define BITIS0F56 //INVULLEN, kleiner of gelijk aan 719
#define STOPBITVALUE //INVULLEN, kleiner of gelijk aan 719


/* includes */
#include "ir.h"


/* function prototypes */
uint16_t curcounter;
uint16_t prevcounter;
uint8_t freq;


/* ISR */
ISR (TIMER1_COMPB_vect) { // 
	TCCR2A ^= (1<<WGM20); //switch counter2 off/CTC
	TCCR2A ^= (1<<WGM21); //switch counter2 off/CTC
	TCCR2B ^= (1<<WGM22); //switch counter2 off/CTC fastPWM
}

ISR (TIMER2_COMPB_vect) {
	#if FREQUENCY == 38 // aangeroepen elke 1,05ms
	
	#elif FREQUENCY == 56 // aangeroepen elke 0,71ms
	
	#else
	// exception error, geen khz gekozen
	#endif
}


/* functions */
void IR_prepare_timer_send(uint8_t frequency) {
	TCCR2A |= (1<<WGM20) | (1<<WGM21); //CTC, fast PWM
	TCCR2B |= (1<<WGM22) //CTC, fast PWM
	TCCR2A |= (1<<COM2B1); //clear on compare

	#if FREQUENCY == 38
	OCR2A = KHZ38; //maximum 1 knipper 38 KHz
	OCR2B = DUTYCYCLE38;
	OCR1A = TOTALBIT38; //totaal 1 bit 38 KHz
	freq = 0;
	#elif FREQUENCY == 56
	OCR2A = KHZ56; //maximum 1 knipper 56 KHz
	OCR2B = DUTYCYCLE56;
	OCR1A = TOTALBIT56; //totaal 1 bit 56 KHz
	freq = 1;
	#else
	// exception error, geen khz gekozen
	#endif

	TCCR1A |= (1<<WGM10) | (1<<WGM11); //fast PWM CTC
	TCCR1B |= (1<<WGM12) | (1<<WGM13); //fast PWM CTC
	TCCR1B |= (1<<CS11); //prescaler 8
}


void IR_prepare_timer_receive(void) {
	
}


void IR_send(uint8_t waarde) {
	// start bit
	#ifdef FREQUENCY == 56
		OCR1B = STARTBITVALUE56;
		for (int i=7, i>=0, i--) {
			if (waarde & (1<<i) { //is bit i 1?
				OCR1B = BITIS1F56;
			} else { //bit i is 0
				OCR1B = BITIS0F56;
			}
		}
	OCR1B = STOPBITVALUE56;
	#elif FREQUENCY == 38
		OCR1B = STARTBITVALUE38;
		for (int i=7; i>=0; i--) {
			if (waarde & (1<<i) {
				OCR1B = BITIS1F38
			} else {
				OCR1B = BITIS0F38
			}
		}
	#else
	// exception error, geen khz gekozen
	#endif
	OCR1B = STOPBITVALUE38;
}


uint8_t IR_receive(void) {
	// mogelijk functie aanpassen om interrupt te genereren op ontvangst informatie
	
}

//======================================================================


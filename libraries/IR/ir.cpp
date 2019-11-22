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
#define STOPBITVALUE38 //INVULLEN, kleiner of gelijk aan 1039

#define KHZ56 36 //timer2 prescale 8
#define DUTYCYCLE56 18 //duty cycle 50% 56KHz
#define TOTALBIT56 720 //40 keer knipperen
#define STARTBITVALUE56 //INVULLEN, kleiner of gelijk aan of 719 (wat veel te groot is)
#define BITIS1F56 //INVULLEN, kleiner of gelijk aan 719
#define BITIS0F56 //INVULLEN, kleiner of gelijk aan 719
#define STOPBITVALUE56 //INVULLEN, kleiner of gelijk aan 719

// test
#define BITIS1 100
#define BITIS0 200
// test


/* includes */
#include "ir.h"


/* global variables */
volatile uint8_t prevcounter;
volatile uint8_t diffcounter;
volatile uint8_t input = 0x00; // bevat de gestuurde byte


/* function prototypes */
uint8_t ontcijfer_input(uint8_t input);

/* ISR */
ISR (TIMER1_COMPB_vect) { // aangeroepen op frequentie defined door FREQUENCY
	TCCR2A ^= (1<<WGM20); //switch counter2 off/CTC
	TCCR2A ^= (1<<WGM21); //switch counter2 off/CTC
	TCCR2B ^= (1<<WGM22); //switch counter2 off/CTC fastPWM
}

ISR (PCINT2_vect) { // wordt aangeroepen bij logische 1 naar 0 of 0 naar 1 van ontvanger
	/*
	 * sla stand van hardware counter op (timer2)
	 * vergelijk huidige stand met vorige stand
	 * meet de tijd tussen deze interrupts, dus een 0 of 1
	 */

	if (DDRD & (1<<PD2)) { // opgaande flank (0 -> 1)
		// bepaal verschil huidige counterstand en vorige counterstand
		diffcounter = OCR2A - prevcounter;
		input = (input>>1); // shift input 1 naar rechts, nieuwe bit komt links

		if (diffcounter <= BITIS1 /*waarde en vergelijking nakijken*/ ) { // bit is een 1
			input |= (1<<7); // zet MSB op 1
		} else { // bit is een 0
			input &= ~(1<<7); // zet MSB op 0 (mag weggelaten worden)
		}
	} else { // neergaande flank (1 -> 0)
		prevcounter = OCR2A; // onthoud counterstand
	}
}


/* functions */
void IR_prepare_send(void) {
	/* TIMER2 - Standaard LED frequentie */
	TCCR2A |= (1<<WGM20) | (1<<WGM21); //CTC, fast PWM
	TCCR2B |= (1<<WGM22) //CTC, fast PWM
	TCCR2A |= (1<<COM2B1); //clear on compare
	TCCR2B |= /*(1<<CS22) | (1<<CS21) |*/ (1<<CS20); // timer2 no prescaling (prescaler 1)

	#if FREQUENCY == 38
	OCR2A = KHZ38; //maximum 1 knipper 38 KHz
	OCR2B = DUTYCYCLE38;
	OCR1A = TOTALBIT38; //totaal 1 bit 38 KHz
	#elif FREQUENCY == 56
	OCR2A = KHZ56; //maximum 1 knipper 56 KHz
	OCR2B = DUTYCYCLE56;
	OCR1A = TOTALBIT56; //totaal 1 bit 56 KHz
	#else
	// exception error, geen (geldige) khz gekozen
	#endif

	/* TIMER1 - Bepaald informatie in signaal */
	TCCR1A |= (1<<WGM10) | (1<<WGM11); //fast PWM CTC
	TCCR1B |= (1<<WGM12) | (1<<WGM13); //fast PWM CTC
	TCCR1B |= (1<<CS11); //prescaler 8
}


void IR_prepare_receive(void) {
	// zie pagina 8 technisch ontwerp
	PCICR |= (1<<PCIE2); // pin change interrupt enable 2 (PCINT[23:16])
	PCMSK2 |= (1<<PCINT18); // pin PD2 interrupts doorlaten

	// intstellen timer2, technisch ontwerp pagina 9
	// zelfde instellingen als IR_prepare_send, roep ook deze functie aan?
	// anders globale functie aanmaken voor init timer1 & init timer2?
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
	#else
	// exception error, geen (geldige) khz gekozen
	#endif
}


// weghalen? (ook uit .h)
uint8_t IR_receive(void) {
	// mogelijk functie aanpassen om interrupt te genereren op ontvangst informatie
	
}

//======================================================================


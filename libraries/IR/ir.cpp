/*
 *	IR communication library
 */


/* defines */
#define KHZ38 52 //timer2 prescale 8
#define DUTYCYCLE38 26 //duty cycle 50% 38KHz
#define TOTALBIT38 1040 //40 keer knipperen
#define KHZ56 36 //timer2 prescale 8
#define DUTYCYCLE56 18 //duty cycle 50% 56KHz
#define TOTALBIT56 720 //40 keer knipperen
#define BITIS1 100 // INVULLEN, kleiner of gelijk aan 719
#define BITIS0 200 // INVULLEN, kleiner of gelijk aan 719
#define STARTBITVALUE 400 // INVULLEN, kleiner of gelijk aan 719 (wat veel te groot is)
#define STOPBITVALUE 400 // INVULLEN, kleiner of gelijk aan 719
#define OFFSET 5 // offset waarde voor kleine afwijking

/* includes */
#include "ir.h"


/* global variables */
volatile uint8_t prevcounter;
volatile uint8_t diffcounter;
volatile uint8_t input = 0x00; // bevat de gestuurde byte
//volatile uint8_t values[];

/* function prototypes */
uint8_t ontcijfer_input(uint8_t input);

/* ISR */
//ISR (TIMER1_COMPB_vect) { // aangeroepen op frequentie defined door FREQUENCY
//	TCCR2A ^= (1<<WGM20); //switch counter2 off/CTC
//	TCCR2A ^= (1<<WGM21); //switch counter2 off/CTC
//	TCCR2B ^= (1<<WGM22); //switch counter2 off/CTC fastPWM
//}

ISR (PCINT2_vect) { // wordt aangeroepen bij logische 1 naar 0 of 0 naar 1 van ontvanger
	/*
	 * sla stand van hardware counter op (timer2)
	 * vergelijk huidige stand met vorige stand
	 * meet de tijd tussen deze interrupts, dus een 0 of 1
	 */

	// nog manier vinden om startbit/stopbit van elkaar te onderscheiden

	if (DDRD & (1<<PD2)) { // opgaande flank (0 -> 1)
		// bepaal verschil huidige counterstand en vorige counterstand
		diffcounter = TCNT2 - prevcounter; //OCR2A - prevcounter;

		if (diffcounter >= (STARTBITVALUE - OFFSET) && diffcounter <= (STARTBITVALUE + OFFSET)) { // startbit
			
		} else if (diffcounter >= (STOPBITVALUE - OFFSET) && diffcounter <= (STOPBITVALUE + OFFSET)) { // stopbit
			
		} else { // byte informatie
			input = (input>>1); // shift input 1 naar rechts, nieuwe bit komt links
			if (diffcounter >= (BITIS1 - OFFSET) && diffcounter <= (BITIS1 + OFFSET)) { // bit is een 1
				input |= (1<<7); // zet MSB op 1
			} else if (diffcounter >= (BITIS0 - OFFSET) && diffcounter <= (BITIS0 + OFFSET)) { // bit is een 0
				input &= ~(1<<7); // zet MSB op 0 (mag weggelaten worden)
			}
		}
	} else { // neergaande flank
		prevcounter = TCNT2; // onthoud counterstand, als het goed is 0, anders dicht in de buurt van 0.
	}
}


/* functions */
void IR_prepare_send(void) {
	/* TIMER2 - Standaard LED frequentie */
	TCCR2A |= (1<<WGM21) | (1<<WGM20); //CTC, fast PWM
	TCCR2B |= (1<<WGM22); //CTC, fast PWM
	TCCR2A |= (1<<COM2B1); // clear on compare, non-inverting-mode
	TCCR2B |= /*(1<<CS22) |*/ (1<<CS21) /*| (1<<CS20)*/; // timer2 no prescaling (prescaler 1), Prescaler 1 maakt 38 en 56 KHz nagenoeg onmogelijk om te realiseren

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
	#pragma GCC error "geen geldige frequentie gekozen"
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
	OCR1B = STARTBITVALUE; // start bit
	for (int i=7; i>=0; i--) {
		if (waarde & (1<<i)) { //is bit i 1?
			OCR1B = BITIS1;
		} else { //bit i is 0
			OCR1B = BITIS0;
		}
	}
	OCR1B = STOPBITVALUE; // start bit
}


// weghalen? (ook uit .h)
uint8_t IR_receive(void) {
	// mogelijk functie aanpassen om interrupt te genereren op ontvangst informatie
	return 0x00;
}

uint8_t getInput(void) {
	return input;
}

//======================================================================

uint8_t ontcijfer_input(uint8_t input) { // van tijden naar byte
	return input;
}

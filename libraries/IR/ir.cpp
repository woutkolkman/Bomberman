/*
 *	IR communication library
 */


/* defines */
#define KHZ38 52 // timer2 prescale 8
#define DUTYCYCLE38 26 // duty cycle 50% 38KHz
//#define TOTALBIT38 20800 // 400 keer knipperen
#define KHZ56 36 // timer2 prescale 8
#define DUTYCYCLE56 18 // duty cycle 50% 56KHz
//#define TOTALBIT56 14400 // 400 keer knipperen
#define BITIS1 0x0035 // INVULLEN, kleiner of gelijk aan 719
#define BITIS0 0x00FF // INVULLEN, kleiner of gelijk aan 719
#define STARTBITVALUE 0x0FFF // INVULLEN, kleiner of gelijk aan 719 (wat veel te groot is)
#define STOPBITVALUE 0x0AFF // INVULLEN, kleiner of gelijk aan 719
#define OFFSET 0x05 // offset waarde voor kleine afwijking (ontvangen)
#define TIJD1 0x0020 // tijd waarop led tussen een 1/0 aan is, niet belangrijk voor de informatie
//#define USART_SEND // als defined, print bits in serial console


/* includes */
#include "ir.h"


/* global variables */
volatile uint8_t prevcounter;
volatile uint8_t diffcounter;
volatile uint8_t input; // bevat de gestuurde byte
volatile uint8_t raw_input; // wordt overgezet naar "input" bij stopbit

volatile uint8_t output = 0x00; // gegevens om te verzenden
volatile uint8_t aan_het_verzenden = 0; // staat op 1 als er iets verzonden wordt (/ moet worden)
volatile uint8_t state = 0;
volatile uint8_t aantal_bits_verzonden = 0x00;


/* function prototypes */
uint8_t getInput(void);


/* ISR */
ISR (TIMER1_COMPA_vect/*TIMER1_OVF_vect*/) { // ISR toggled output van timer2 voor verzenden bits
	// misschien nog toepassen dat berichten even lang duren door aan-tijd dynamisch aan te passen

	if (aan_het_verzenden == 1) {
//		TCNT1 = 0x00; // zet register op 0 (wordt al automatisch gedaan?)
		if (TCCR2A & (1<<COM2B1)) { // als PWM poort aan staat
			TCCR2A ^= (1<<COM2B1); // schakel PWM poort (uit)
			OCR1A = TIJD1; // ..totdat timer1 deze waarde heeft behaald

			if (state == 3) { // afsluiten bericht
				state = 0;
				aan_het_verzenden = 0;
			}
		} else { // als PWM poort uit staat
			TCCR2A ^= (1<<COM2B1); // schakel PWM poort (aan), tijd wordt opgeslagen door ontvanger
			if (state == 0) { // startbit verzenden
				OCR1A = STARTBITVALUE;
				state++;
			} else if (state == 1) { // informatie verzenden
				if (output & (1<<0)) {
					OCR1A = BITIS1; // verzend 1
					#ifdef USART_SEND
					USART_Transmit(0x31);
					#endif
				} else {
					OCR1A = BITIS0; // verzend 0
					#ifdef USART_SEND
					USART_Transmit(0x30);
					#endif
				}
				output = (output>>1); // volgende bit (van rechts naar links)
				aantal_bits_verzonden++;
				if (aantal_bits_verzonden >= 8) {
					state++;
				}
			} else if (state == 2) { // stopbit verzenden
				aantal_bits_verzonden = 0;
				OCR1A = STOPBITVALUE;
				state++;
			}
		}
	}
}


ISR (PCINT2_vect) { // wordt aangeroepen bij logische 1 naar 0 of 0 naar 1 van ontvanger
	/*
	 * sla stand van hardware counter op (timer2)
	 * vergelijk huidige stand met vorige stand
	 * meet de tijd tussen deze interrupts, dus een 0 of 1
	 */

	if (DDRD & (1<<DDD2)) { // opgaande flank (0 -> 1)
		// bepaal verschil huidige counterstand en vorige counterstand
		diffcounter = TCNT1 - prevcounter; // TCNT1 - prevcounter;
		if (diffcounter >= (STARTBITVALUE - OFFSET) && diffcounter <= (STARTBITVALUE + OFFSET)) { // startbit
			
		} else if (diffcounter >= (STOPBITVALUE - OFFSET) && diffcounter <= (STOPBITVALUE + OFFSET)) { // stopbit
			input = raw_input; // input teruggeven aan programma wanneer alles binnen is
		} else { // byte informatie
			raw_input = (raw_input>>1); // shift input 1 naar rechts, nieuwe bit komt links
			if (diffcounter >= (BITIS1 - OFFSET) && diffcounter <= (BITIS1 + OFFSET)) { // bit is een 1
				raw_input |= (1<<7); // zet MSB op 1
			} else if (diffcounter >= (BITIS0 - OFFSET) && diffcounter <= (BITIS0 + OFFSET)) { // bit is een 0
				raw_input &= ~(1<<7); // zet MSB op 0 (mag weggelaten worden)
			}
		}
	} else { // neergaande flank
		prevcounter = TCNT1; // onthoud counterstand, als het goed is 0, anders dicht in de buurt van 0.
	}
}


/* functions */
void IR_prepare(void) {
	/* TIMER2 - Standaard LED frequentie */
	DDRD |= (1<<PD3); //pin 3 output
	TCCR2A |= (1<<WGM21) | (1<<WGM20); // fast PWM
	TCCR2B |= (1<<WGM22); // fast PWM
//	TCCR2A |= (1<<COM2B1); // clear on compare, non-inverting-mode
	TCCR2B |= (1<<CS21); // timer2 prescaling 8, (Prescaler 1 maakt 38 en 56 KHz nagenoeg onmogelijk (zeer ingewikkeld om te realiseren)

	#if FREQUENCY == 38
	OCR2A = KHZ38; //maximum 1 knipper 38 KHz
	OCR2B = DUTYCYCLE38;
//	OCR1A = TOTALBIT38; //totaal 1 bit 38 KHz
	#elif FREQUENCY == 56
	OCR2A = KHZ56; //maximum 1 knipper 56 KHz
	OCR2B = DUTYCYCLE56;
//	OCR1A = TOTALBIT56; //totaal 1 bit 56 KHz
	#else
	// exception error, geen (geldige) khz gekozen
	#pragma GCC error "geen geldige frequentie gekozen"
	#endif

	/* TIMER1 - Bepaald informatie in signaal */
//	TCCR1A |= (1<<WGM10) | (1<<WGM11); //fast PWM CTC
//	TCCR1B |= (1<<WGM12) | (1<<WGM13); //fast PWM CTC
//	TCCR1B |= (1<<CS11); //prescaler 8
	TCCR1A |= (1<<WGM12); // CTC / clear timer on compare match, top OCR1A
	TCCR1B |= /*(1<<CS12) |*/ (1<<CS11) | (1<<CS10); // prescaler 1
	TIMSK1 |= (1<<OCIE1A); // output compare a match interrupt enable
//	TIMSK1 |= (1<<TOIE1); // overflow interrupt

	// zie pagina 8 technisch ontwerp
	DDRD &= ~(1<<DDD2); //pin 2 input
	PORTD |= (1<<PORTD2); //pull-up resistor pin 2
	PCICR |= (1<<PCIE2); // pin change interrupt enable 2 (PCINT[23:16])
	PCMSK2 |= (1<<PCINT18); // pin 2 interrupts doorlaten

	// intstellen timer2, technisch ontwerp pagina 9
}


void IR_send(uint8_t waarde) {
	/*// test voor laten aanpassen ontvanger
	TCCR2A ^= (1<<COM2B1);
	_delay_ms(400);
	TCCR2A ^= (1<<COM2B1);
	_delay_ms(100);
	// test*/

	output = waarde; // instellen output
	aan_het_verzenden = 1; // activeren verzenden
}


// weghalen? (ook uit .h)
uint8_t IR_receive(void) {
	// mogelijk functie aanpassen om interrupt te genereren op ontvangst informatie
	return getInput();
}


uint8_t getInput(void) {
//	IR_prepare();
	return input;
}

//======================================================================


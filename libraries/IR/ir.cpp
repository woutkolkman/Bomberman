/*
 *	IR communication library - half-duplex
 */


/* defines */
/*
 * #define MS_PER_TICK (1/(16000000/1024)) // prescaler 1024 timer2 TIJDENS ONTVANGEN, 0,064ms
 * sommige defines moeten handmatig uitgerekend en ingevoerd worden tegen het afronden van de compiler
 * waarden van de counter lopen niet lineair op, waarschijnlijk door het gebruik van delays
 */

//#define BITIS1_MS 30 				// ms waarop LED aanstaat voor 1
#define BITIS1 50 /*(BITIS1_MS / MS_PER_TICK)*/
#define BITIS1_S 300				// zelfde als BITIS1, alleen voor verzenden
//#define BITIS0_MS 20 				// ms waarop LED aanstaat voor 0
#define BITIS0 575 /*(BITIS0_MS / MS_PER_TICK)*/
#define BITIS0_S 200				// zelfde als BITIS0, alleen voor verzenden
//#define STARTBIT_MS 400 			// ms waarop LED aanstaat voor startbit
#define STARTBIT 6490 /*(STARTBIT_MS / MS_PER_TICK)*/
#define STARTBIT_S 400				// zelfde als STARTBIT, alleen voor verzenden
//#define STOPBIT_MS 200 			// ms waarop LED aanstaat voor stopbit
#define STOPBIT 3370 /*(STOPBIT_MS / MS_PER_TICK)*/
#define STOPBIT_S 200				// zelfde als STOPBIT, alleen voor verzenden
#define OFFSET 20 /*(4 / MS_PER_TICK)*/ 	// offset waarde voor kleine afwijking (ontvangen)
//#define TIJD0_MS 20 				// tijd waarop LED tussen bits uit is
#define TIJD0_S 20				// tijd waarop LED tussen bits uit is

#define KHZ_1 0x35/*53*//*52*/ 			// timer2 OVF count 38KHZ
#define KHZ_2 0x24/*36*/ 			// timer2 OVF count 56KHZ
#define DUTYCYCLE_1 (KHZ_1 / 2) 		// dutycycle 50% 38KHZ
#define DUTYCYCLE_2 (KHZ_2 / 2) 		// dutycycle 50% 56KHZ
#define FREQUENCY_1_SETNAME 38 			// KHZ
#define FREQUENCY_2_SETNAME 56 			// KHZ
#define DEFAULT_FREQUENCY_SETNAME FREQUENCY_1_SETNAME // als er geen geldige frequentie meegegeven is, is dit de standaard frequentie
#define DYNAMIC_TIJD0 				// als defined, pas TIJD0 dynamisch aan aan de tijdsduur van de gestuurde bit
#ifdef DYNAMIC_TIJD0
#define MAXTIJD_PER_BIT 60 			// tijd van bit + TIJD0, moet groter zijn dan BITIS1_MS & BITIS0_MS
#endif
#define AANTAL_BITS 8 				// geeft direct aantal bits aan, pas ook type aan
#define AANTAL_BITS_TYPE uint8_t 		// pas dit aan als aantal bits wordt aangepast
#define PRINT_ONTVANGST 			// debug, print via USART


/* includes */
#include "ir.h"


/* global variables */
volatile uint8_t khz = KHZ_1; // huidige frequentie voor IR_send, standaard frequentie 1
volatile uint8_t dutycycle = DUTYCYCLE_1; // huidige dutycycle voor IR_send, standaard dutycycle 1
volatile uint8_t prevcounter;
volatile unsigned int diffcounter; // 0-65535 / 0-4294967295
volatile AANTAL_BITS_TYPE input; // bevat de gestuurde byte
volatile AANTAL_BITS_TYPE raw_input; // wordt overgezet naar "input" bij stopbit
volatile uint8_t timer2_ovfs = 0; // telt aantal overflows bij ontvangen data
volatile int aantal_bits = 0; // telt aantal bits of dit geldig is
volatile uint8_t nieuwe_input = 0; // wordt op 1 gezet bij nieuwe input en gereset bij uitlezen
volatile uint8_t aan_het_ontvangen = 0; // wordt op 1 gezet bij het ontvangen van informatie, zodat zender ondertussen niet aangaat

volatile uint8_t aan_het_verzenden = 0; // staat op 1 als er informatie verzonden mag worden
volatile uint8_t output = 0; // gegevens om te verzenden
volatile uint8_t state = 0;
volatile uint8_t aantal_bits_verzonden = 0;
volatile uint8_t verzend_na_ontvangen = 0;
volatile unsigned int send_goal = 0;
volatile unsigned int send_count = 0;


///* function prototypes */
// ...


/* ISR */
ISR (PCINT2_vect) { // wordt aangeroepen bij logische 1 naar 0 of 0 naar 1 van ontvanger
	/*
	 * sla stand van hardware counter op (timer2)
	 * vergelijk huidige stand met vorige stand
	 * meet de tijd tussen deze interrupts, dus een 0 of 1
	 *
	 * er is gekozen om alles in de ISR te laten omdat al deze stappen toch al
	 * uitgevoerd moeten worden voordat nieuwe bits verwerkt kunnen worden
	 */

	if (PIND & (1<<PD2)) { // opgaande flank (0 -> 1)

		// bepaal verschil huidige counterstand en vorige counterstand
		if (TCNT2 < prevcounter) { // als huidige counterstand lager is dan opgeslagen, tel rond
			diffcounter = (OCR2A - prevcounter) + TCNT2;
			if (timer2_ovfs != 0) { // voorkomt diffcounter += ORC2A * -1
				diffcounter += (OCR2A * (timer2_ovfs - 1)); // aantal overflows bijop tellen
			}
		} else {
			diffcounter = TCNT2 - prevcounter;
			diffcounter += (OCR2A * timer2_ovfs); // aantal overflows bijop tellen
		}

		// bepaal welke bit ontvangen is
		if (diffcounter >= (STARTBIT - OFFSET) && diffcounter <= (STARTBIT + OFFSET)) { // startbit
			aantal_bits = 0; // aantal bits check resetten
			aan_het_ontvangen = 1;

			#ifdef PRINT_ONTVANGST
			USART_Transmit(0x41); // test
			#endif
		} else if (diffcounter >= (STOPBIT - OFFSET) && diffcounter <= (STOPBIT + OFFSET)) { // stopbit
			if (AANTAL_BITS == aantal_bits) { // aantal bits checken op geldigheid
				input = raw_input; // input teruggeven aan programma wanneer alles binnen is
				aantal_bits = 0; // aantal bits check resetten
				nieuwe_input = 1; // geef aan dat er nieuwe input is

				// softwarematige interrupt genereren met PCINT?
			}
			aan_het_ontvangen = 0; // aangeven dat er niks meer wordt ontvangen

			#ifdef PRINT_ONTVANGST
			USART_Transmit(0x4F); // test
			#endif

			if (verzend_na_ontvangen) { // als er informatie verzonden kan worden
				verzend_na_ontvangen = 0; // resetten variabele
				IR_send(output); // verzend die informatie
			}
		} else { // byte informatie
			raw_input = (raw_input>>1); // shift input 1 naar rechts, nieuwe bit komt links
			if (diffcounter >= (BITIS1 - OFFSET) && diffcounter <= (BITIS1 + OFFSET)) { // bit is een 1
				raw_input |= (1<<7); // zet MSB op 1
				aantal_bits++;

				#ifdef PRINT_ONTVANGST
				USART_Transmit(0x31); // test
				#endif
			} else if (diffcounter >= (BITIS0 - OFFSET) && diffcounter <= (BITIS0 + OFFSET)) { // bit is een 0
				raw_input &= ~(1<<7); // zet MSB op 0 (mag weggelaten worden)
				aantal_bits++;

				#ifdef PRINT_ONTVANGST
				USART_Transmit(0x30); // test
				#endif
			} else {
				#ifdef PRINT_ONTVANGST
				USART_Transmit(0x21); // test
				#endif
//				informatie_aan_het_ontvangen = 0;
			}
		}

		TIMSK2 &= ~(1<<OCIE2A); // OCR2A compare match interrupt uitschakelen, weer aanzetten bij neergaande flank
	} else { // neergaande flank (1 -> 0)
		prevcounter = TCNT2; // onthoud counterstand, als het goed is 0, anders dicht in de buurt van 0.
		TIMSK2 |= (1<<OCIE2A); // OCR2A compare match interrupt, tel aantal overflows in TIMER2_COMPA_vect ISR
		timer2_ovfs = 0;
	}
}


ISR (TIMER2_COMPA_vect) { // wordt aangeroepen bij timer2 overflows, wanneer data wordt ontvangen om tijd te meten
	/* code voor ontvangen */
	// aangeroepen om de 16,384 ms met prescaler 1024
	timer2_ovfs++; // wordt niks mee gedaan tijdens verzenden, wordt gereset bij ontvangen

	/* code voor verzenden */
	if (aan_het_verzenden == 1 // als er output is om te verzenden, en ...
	&& aan_het_ontvangen == 0) { // als er niks ontvangen wordt, verzendt
		send_count++; // counter iets ophogen om doel te bereiken
		if (send_count >= send_goal) { // doel bereikt?
			if (TCCR2A & (1<<COM2B1)) { // als PWM poort aan staat
				TCCR2A ^= (1<<COM2B1); // schakel PWM poort (uit)
				send_goal = TIJD0_S; // tijd waarop LED uit is
				// TODO, implementeren dat tijd dynamisch aangepast wordt gebaseerd op het type bit dat wordt verstuurd?

				if (state == 3) { // afsluiten bericht nadat stopbit is verzonden
					state = 0;
					aan_het_verzenden = 0;

					// interrupts uitzetten
					TIMSK2 &= ~(1<<OCIE2A); // OCR2A compare match interrupt uit

					// luisteren naar nieuwe input ontvanger
					prepare_receive();
				}
			} else { // als PWM poort uit staat
				TCCR2A ^= (1<<COM2B1); // schakel PWM poort (aan)

				// bereken volgende doel
				if (state == 0) { // startbit
					send_goal = STARTBIT_S;
					state++;
				} else if (state == 1) { // informatie
					if (output & (1<<0)) { // verzend 1
						send_goal = BITIS1_S;
					} else { // verzend 0
						send_goal = BITIS0_S;
					}
					output = (output>>1); // volgende bit (van rechts naar links)
					aantal_bits_verzonden++; // houd bij hoeveel bits er zijn verzonden
					if (aantal_bits_verzonden >= AANTAL_BITS) {
						state++;
					}
				} else if (state == 2) { // stopbit
					aantal_bits_verzonden = 0; // resetten variabele
					send_goal = STOPBIT_S;
					state++;
				}
			}
			send_count = 0; // resetten count
		}
	}
}


/* functions */
void IR_prepare(uint8_t frequentie) {
	DDRD |= (1<<PD3); // pin 3 output (IR LED)

	/* PCINT - Voor IR ontvanger */
	DDRD &= ~(1<<DDD2); //pin 2 input
	PORTD |= (1<<PORTD2); //pull-up resistor pin 2
	PCICR |= (1<<PCIE2); // pin change interrupt enable 2 (PCINT[23:16])
	/*
	 * PCMSK2 |= (1<<PCINT18); // pin 2 interrupts doorlaten
	 * dit wordt toegepast in functie prepare_receive() zodat dit getoggled kan worden
	 */

	if ((frequentie != FREQUENCY_1_SETNAME) && (frequentie != FREQUENCY_2_SETNAME)) {
		frequentie = DEFAULT_FREQUENCY_SETNAME;
	}

	if (frequentie == FREQUENCY_1_SETNAME) { // wordt in variabelen ingesteld zodat main.cpp dit aan kan passen
		khz = KHZ_1;
		dutycycle = DUTYCYCLE_1;
	} else if (frequentie == FREQUENCY_2_SETNAME) {
		khz = KHZ_2;
		dutycycle = DUTYCYCLE_2;
	}

	prepare_receive(); // standaard voor luisteren/meten input
//	sei();
}


void IR_send(uint8_t waarde) {
	// functie zet waardes in variabelen, om in ISR te gebruiken
	output = waarde;

	if (aan_het_ontvangen) { // als er nog informatie ontvangen wordt
		// verzend pas nadat informatie ontvangen is (half-duplex)
		verzend_na_ontvangen = 1;
		// gaat niet goed als er geen stopbit(s) worden gelezen
	} else {
		// voorbereiding
		prepare_send();

		// laatste regel zodat ISR niet vroegtijdig begint
		aan_het_verzenden = 1; // zet verzenden via timer aan
	}

//===============================================================================
//	// wacht tot informatie is ontvangen
//	while (informatie_aan_het_ontvangen);
//	// gaat niet goed als er geen stopbit wordt gelezen
//
//	// voorbereiding
//	prepare_send();
//
//	// variabelen
//	int vorige_bit_ms = 0;
//
//	// startbit
//	schakel_IR_LED(1);
//	_delay_ms(STARTBIT_MS);
//	schakel_IR_LED(0);
//	_delay_ms(TIJD0_MS);
//
//	// byte
//	for (int i=1; i<=AANTAL_BITS; i++) {
//		schakel_IR_LED(1);
//		if (waarde & (1<<0)) { // LSB is 1
//			_delay_ms(BITIS1_MS);
//
//			#ifdef DYNAMIC_TIJD0
//			vorige_bit_ms = BITIS1_MS;
//			#endif
//		} else { // LSB is 0
//			_delay_ms(BITIS0_MS);
//
//			#ifdef DYNAMIC_TIJD0
//			vorige_bit_ms = BITIS0_MS;
//			#endif
//		}
//		schakel_IR_LED(0);
//		#ifndef DYNAMIC_TIJD0 // default
//		_delay_ms(TIJD0_MS);
//
//		#else // dynamisch aanpassen TIJD0
//		var_delay_ms(MAXTIJD_PER_BIT - vorige_bit_ms);
//		#endif
//
//		waarde = (waarde>>1); // volgende bit (van rechts naar links)
//	}
//
//	// stopbit
//	schakel_IR_LED(1);
//	_delay_ms(STOPBIT_MS);
//	schakel_IR_LED(0);
//
//	// luisteren naar nieuwe input ontvanger
//	prepare_receive();
//===========================================================================
}


// returned 1 als er nieuwe input is dat nog niet is uitgelezen
uint8_t IR_nieuwe_input(void) {
	return nieuwe_input;
}


uint8_t IR_receive(void) {
	// mogelijk functie aanpassen om interrupt te genereren op ontvangst informatie
	nieuwe_input = 0;
	return input;
}


// ===========================================================================


//// voor aan- en uitschakelen IR LED
//void schakel_IR_LED(uint8_t aan) {
//	if (aan) { // LED aan
//		TCCR2A |= (1<<COM2B1);
//	} else { // LED uit
//		TCCR2A &= ~(1<<COM2B1);
//	}
//}


// variabele delays, gebruik alleen voor kleine delays
void var_delay_ms(int ms) {
	while (0 < ms) {
		_delay_ms(1);
		ms--;
	}
}


void prepare_send(void) {
	PCMSK2 &= ~(1<<PCINT18); // tijdelijk geen interrupts van ontvanger doorlaten

	/* TIMER2 - Standaard LED frequentie */
	TCCR2A = 0; // resetten timer
	TCCR2B = 0; // resetten timer
	GTCCR |= (1<<PSRASY); // reset prescaler timer2
	TCCR2A |= (1<<WGM21) | (1<<WGM20); // fast PWM
	TCCR2B |= (1<<WGM22); // fast PWM
	TCCR2B |= /*(1<<CS22) | */(1<<CS21)/* | (1<<CS20)*/; // prescaler 8, (Prescaler 1 maakt 38 en 56 KHz nagenoeg onmogelijk (zeer ingewikkeld om te realiseren)
//	TCCR2B &= ~(1<<CS22) & (1<<CS20); // uitzetten settings receive
	/*
	 * TCCR2A |= (1<<COM2B1); // clear on compare, non-inverting-mode
	 * deze regel wordt gebruikt om IR LED aan/uit te zetten,
	 * het wordt aangeroepen in IR_send()
	 */
	TIMSK2 |= (1<<OCIE2A); // OCR2A compare match interrupt, ga naar TIMER2_COMPA_vect ISR
	// compare match interrupt wordt uitgezet nadat informatie is verzonden

	OCR2A = khz;
	OCR2B = dutycycle;
}


void prepare_receive(void) {
	/* TIMER2 - Voor tellen delays */
	TCCR2A = 0; // resetten timer
	TCCR2B = 0; // resetten timer
	GTCCR |= (1<<PSRASY); // reset prescaler timer2
	TCCR2A |= (1<<WGM21); // CTC, OCRA top
	TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20); // prescaler 1024
	OCR2A = 0xFF/*255*/; // max 2^8 = 255 (256-1)
	OCR2B = 0; // uitzetten settings send
	/*
	 * TIMSK2 |= (1<<OCIE2A); // OCR2A compare match interrupt, ga naar TIMER2_COMPA_vect ISR
	 * deze regel wordt in de ISR aangeroepen zodat alleen interrupts worden gegenereerd wanneer nodig
	 */

	PCMSK2 |= (1<<PCINT18); // interrupts van ontvanger doorlaten
}

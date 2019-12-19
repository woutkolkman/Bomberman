/*
 *	IR communication library - half-duplex
 *
 *	Byte gelijk aan RESEND_BITS is in gebruik, roep dit niet aan om loop te voorkomen
 */


/* defines */
/*
 * #define MS_PER_TICK (1/(16000000/1024)) // prescaler 1024 timer2 TIJDENS ONTVANGEN, 0,064ms
 * sommige defines moeten handmatig uitgerekend en ingevoerd worden tegen het afronden van de compiler
 * waarden van de counter lopen niet lineair op, waarschijnlijk door het gebruik van delays
 */

#define BITIS1 55 /*(BITIS1_MS / MS_PER_TICK)*/
#define BITIS1_S_56 200				// zelfde als BITIS1, alleen voor verzenden
#define BITIS1_S_38 140
#define BITIS0 40 /*(BITIS0_MS / MS_PER_TICK)*/
#define BITIS0_S_56 100				// zelfde als BITIS0, alleen voor verzenden
#define BITIS0_S_38 68
#define STARTBIT 114 /*(STARTBIT_MS / MS_PER_TICK)*/
#define STARTBIT_S_56 400				// zelfde als STARTBIT, alleen voor verzenden
#define STARTBIT_S_38 271
#define STOPBIT 100 /*(STOPBIT_MS / MS_PER_TICK)*/
#define STOPBIT_S_56 300				// zelfde als STOPBIT, alleen voor verzenden
#define STOPBIT_S_38 204
#define OFFSET 20 /*(4 / MS_PER_TICK)*/ 	// offset waarde voor kleine afwijking (ontvangen)
#define TIJD0_S_56 15				// tijd waarop LED tussen bits uit is
#define TIJD0_S_38 10				// tijd waarop LED tussen bits uit is
// TODO, defines automatisch uitrekenen, lage prioriteit

#define SEND_RECEIVE_QUEUE_SIZE 10		// grootte wachtrij verzenden/ontvangen
#define KHZ_1 0x35/*53*//*52*/ 			// timer2 OVF count 38KHZ
#define KHZ_2 0x24/*36*/ 			// timer2 OVF count 56KHZ
#define DUTYCYCLE_1 (KHZ_1 / 2) 		// dutycycle 50% 38KHZ
#define DUTYCYCLE_2 (KHZ_2 / 2) 		// dutycycle 50% 56KHZ
#define FREQUENCY_1_SETNAME 38 			// KHZ
#define FREQUENCY_2_SETNAME 56 			// KHZ
#define DEFAULT_FREQUENCY_SETNAME FREQUENCY_1_SETNAME // als er geen geldige frequentie meegegeven is, is dit de standaard frequentie
//#define DYNAMIC_TIJD0 				// als defined, pas TIJD0 dynamisch aan aan de tijdsduur van de gestuurde bit
//#ifdef DYNAMIC_TIJD0
//#define MAXTIJD_PER_BIT 60 			// tijd van bit + TIJD0, moet groter zijn dan BITIS1_MS & BITIS0_MS
//#endif
#define RESEND_BITS 0xFF 			// als input gelijk is aan dit, stuur laatste byte opnieuw
#define RESEND_TRIES 5				// maximaal aantal keer informatie opnieuw proberen op te halen
#define AANTAL_BITS 16 				// geeft direct aantal bits aan, pas ook type aan, minimaal 8, of pas RESEND_BITS aan
#define AANTAL_BITS_TYPE uint16_t 		// pas dit aan als aantal bits wordt aangepast
#define AANTAL_BITS_TYPE_BITS 16 		// aantal bits mogelijk bij dit type data
//#define PRINT_ONTVANGST 			// debug, print via USART, nog wel USART_Init() aanroepen


/* includes */
#include "ir.h"


/* global variables */
volatile uint8_t khz = KHZ_1; // huidige frequentie voor IR_send, standaard frequentie 1
volatile uint8_t dutycycle = DUTYCYCLE_1; // huidige dutycycle voor IR_send, standaard dutycycle 1
volatile uint8_t prevcounter;
volatile uint8_t currcounter;
volatile unsigned int diffcounter; // 0-65535 / 0-4294967295
volatile AANTAL_BITS_TYPE raw_input; // wordt overgezet naar "input" bij stopbit
volatile uint8_t timer2_ovfs = 0; // telt aantal overflows bij ontvangen data
volatile int aantal_bits = 0; // telt aantal bits of dit geldig is
volatile uint8_t nieuwe_input = 0; // wordt op 1 gezet bij nieuwe input en gereset bij uitlezen
volatile uint8_t aan_het_ontvangen = 0; // wordt op 1 gezet bij het ontvangen van informatie, zodat zender ondertussen niet aangaat

volatile int bitis1_s; // verschilt bij 38/56 khz
volatile int bitis0_s; // verschilt bij 38/56 khz
volatile int startbit_s; // verschilt bij 38/56 khz
volatile int stopbit_s; // verschilt bij 38/56 khz
volatile int tijd0_s; // verschilt bij 38/56 khz
volatile uint8_t aan_het_verzenden = 0; // staat op 1 als er informatie verzonden mag worden
volatile uint8_t aantal_verzenden = 0; // hoeveelheid berichten om te verzenden in de queue
volatile uint8_t state_send = 0; // state voor verzenden informatie in ISR
volatile uint8_t aantal_bits_verzonden = 0;
volatile uint8_t verzend_na_ontvangen = 0;
volatile unsigned int send_goal = 0;
volatile unsigned int send_count = 0;
volatile AANTAL_BITS_TYPE send_queue[SEND_RECEIVE_QUEUE_SIZE];
volatile AANTAL_BITS_TYPE receive_queue[SEND_RECEIVE_QUEUE_SIZE];
volatile AANTAL_BITS_TYPE prev_send = 0x00; // voor opnieuw verzenden bericht (als het verkeerd is aangekomen)
volatile uint8_t curr_resend_tries = 0;


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
		currcounter = TCNT2;

		// bepaal verschil huidige counterstand en vorige counterstand
		if (currcounter < prevcounter) { // als huidige counterstand lager is dan opgeslagen, tel rond
			diffcounter = (OCR2A - prevcounter) + currcounter;
			if (timer2_ovfs != 0) { // voorkomt diffcounter += ORC2A * -1
				diffcounter += (OCR2A * (timer2_ovfs - 1)); // aantal overflows bijop tellen
			}
		} else {
			diffcounter = currcounter - prevcounter;
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
			#ifdef PRINT_ONTVANGST
			USART_Transmit(0x4F); // test
			#endif
l
			// aantal bits vanaf LSB in byte zetten
//			raw_input = (raw_input>>(AANTAL_BITS_TYPE_BITS - AANTAL_BITS));
			// TODO, als AANTAL_BITS ongelijk is aan AANTAL_BITS_TYPE_BITS moet de byte nog (AANTAL_BITS_TYPE_BITS - AANTAL_BITS) naar rechts geshift worden

			if (AANTAL_BITS == aantal_bits) { // aantal bits checken op geldigheid

				if ((unsigned int) RESEND_BITS == (unsigned int) raw_input // systeem ontvangt request om vorige bericht opnieuw te verzenden
				&& (unsigned int) prev_send != (unsigned int) RESEND_BITS) { // vorige bericht is niet een request voor resend (anders loop)
					// laatste bericht is niet goed aangekomen, verstuur opnieuw
//					aantal_verzenden++;
					_delay_ms(10); // voorkomt soort loop waarin constant ongeldige berichten worden verstuurd
					IR_send_direct(prev_send); // meest vorige bericht dat is verstuurd opnieuw laten versturen
				} else {
					// sla input op om te laten uitlezen door hoofdprogramma
					if ((1 + nieuwe_input) < SEND_RECEIVE_QUEUE_SIZE) { // niet buiten array kunnen schrijven
						nieuwe_input++; // geef aan dat er nieuwe input is
						receive_queue[nieuwe_input] = raw_input; // input teruggeven aan programma wanneer alles binnen is
					}

					// softwarematige interrupt genereren met PCINT?
				}
				curr_resend_tries = 0;
			} else {
				if (curr_resend_tries < RESEND_TRIES) { // maximaal aantal keer informatie opnieuw proberen op te halen
					_delay_ms(10); // voorkomt soort loop waarin constant ongeldige berichten worden verstuurd
					IR_send_direct(RESEND_BITS); // vraag om laatste bericht opnieuw te versturen
					curr_resend_tries++;
				}
			}
			aan_het_ontvangen = 0; // aangeven dat er niks meer wordt ontvangen
			aantal_bits = 0; // aantal bits check resetten

			if (aantal_verzenden) { // als er informatie verzonden kan worden
				aantal_verzenden--; // opnieuw invoeren bericht
//				_delay_ms(10); // stabiliteit? niet getest dus weggelaten
				IR_send_direct(send_queue[(1 + aantal_verzenden)]); // direct verzenden (half-duplex)
			}
		} else { // byte informatie
			raw_input = (raw_input>>1); // shift input 1 naar rechts, nieuwe bit komt links
			if (diffcounter >= (BITIS1 - OFFSET) && diffcounter <= (BITIS1 + OFFSET)) { // bit is een 1
				raw_input |= (1<<(AANTAL_BITS-1)); // zet MSB op 1
				aantal_bits++;

				#ifdef PRINT_ONTVANGST
				USART_Transmit(0x31); // test
				#endif
			} else if (diffcounter >= (BITIS0 - OFFSET) && diffcounter <= (BITIS0 + OFFSET)) { // bit is een 0
				raw_input &= ~(1<<(AANTAL_BITS-1)); // zet MSB op 0 (mag weggelaten worden)
				aantal_bits++;

				#ifdef PRINT_ONTVANGST
				USART_Transmit(0x30); // test
				#endif
			} else {
				#ifdef PRINT_ONTVANGST
				USART_Transmit(0x21); // test
//				USART_Transmit(diffcounter);
				#endif
//				informatie_aan_het_ontvangen = 0;
			}
		}

		if (!aan_het_verzenden) { // niet aanroepen als timer klaar staat om iets te verzenden
			TIMSK2 &= ~(1<<OCIE2A); // OCR2A compare match interrupt uitschakelen, weer aanzetten bij neergaande flank
		}
	} else { // neergaande flank (1 -> 0)
		prevcounter = TCNT2; // onthoud counterstand, als het goed is 0, anders dicht in de buurt van 0.
		TIMSK2 |= (1<<OCIE2A); // OCR2A compare match interrupt, tel aantal overflows in TIMER2_COMPA_vect ISR
		timer2_ovfs = 0;
	}
}


ISR (TIMER2_COMPA_vect) { // wordt aangeroepen bij timer2 overflows, wanneer data wordt ontvangen om tijd te meten
	/* code voor ontvangen */
	// aangeroepen om de 16,384 ms met prescaler 1024
	timer2_ovfs++; // wordt niks mee gedaan tijdens verzenden, wordt gereset en gebruikt bij ontvangen

	/* code voor verzenden */
	if (aan_het_verzenden // als er output is om te verzenden, en ...
	&& aan_het_ontvangen == 0) { // als er niks ontvangen wordt, verzendt
		send_count += 1; // counter iets ophogen om doel te bereiken

		if (send_count >= send_goal) { // doel bereikt?
			if (TCCR2A & (1<<COM2B1)) { // als PWM poort aan staat
				TCCR2A ^= (1<<COM2B1); // schakel PWM poort (uit)
				send_goal = tijd0_s; // tijd waarop LED uit is
				// TODO, implementeren dat tijd dynamisch aangepast wordt gebaseerd op het type bit dat wordt verstuurd? lage prioriteit

				if (state_send == 4) { // afsluiten bericht nadat stopbit is verzonden
					state_send = 0;
					aan_het_verzenden = 0;
					aantal_verzenden--;

					// interrupts uitzetten
					TIMSK2 &= ~(1<<OCIE2A); // OCR2A compare match interrupt uit

					// luisteren naar nieuwe input ontvanger
					prepare_receive();

					// als er nog iets verzonden kan worden, verzend dit
					if (aantal_verzenden) {
						aantal_verzenden--; // opnieuw invoeren bericht
						IR_send(send_queue[(1 + aantal_verzenden)]);
					}
				}
			} else { // als PWM poort uit staat
				// bereken volgende doel
				if (state_send == 0) { // dummy bit, 1e bit wordt niet goed gelezen, TODO fixen
					send_goal = startbit_s;
					state_send++;
				} else if (state_send == 1) { // startbit
					send_goal = startbit_s;
					state_send++;
					prev_send = send_queue[aantal_verzenden]; // opslaan bericht om mogelijk opnieuw te verzenden als het verkeerd is aangekomen
				} else if (state_send == 2) { // informatie
					if (send_queue[aantal_verzenden] & (1<<0)) { // verzend 1
						send_goal = bitis1_s;
					} else { // verzend 0
						send_goal = bitis0_s;
					}
					send_queue[aantal_verzenden] = (send_queue[aantal_verzenden]>>1); // volgende bit (van rechts naar links)
					aantal_bits_verzonden++; // houd bij hoeveel bits er zijn verzonden
					if (aantal_bits_verzonden >= AANTAL_BITS) {
						state_send++;
					}
				} else if (state_send == 3) { // stopbit
					aantal_bits_verzonden = 0; // resetten variabele
					send_goal = stopbit_s;
					state_send++;
				}

				TCCR2A ^= (1<<COM2B1); // schakel PWM poort (aan)
			}
			send_count = 0; // resetten count
		}
	}
}


/* functions */
void IR_prepare(uint8_t frequentie) {
//	#ifdef PRINT_ONTVANGST
//	USART_Init();
//	#endif

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
		bitis1_s = BITIS1_S_38;
		bitis0_s = BITIS0_S_38;
		startbit_s = STARTBIT_S_38;
		stopbit_s = STOPBIT_S_38;
		tijd0_s = TIJD0_S_38;
	} else if (frequentie == FREQUENCY_2_SETNAME) {
		khz = KHZ_2;
		dutycycle = DUTYCYCLE_2;
		bitis1_s = BITIS1_S_56;
		bitis0_s = BITIS0_S_56;
		startbit_s = STARTBIT_S_56;
		stopbit_s = STOPBIT_S_56;
		tijd0_s = TIJD0_S_56;
	}

	prepare_receive(); // standaard voor luisteren/meten input
//	sei();
}


void IR_send(AANTAL_BITS_TYPE waarde) {
	_delay_ms(50); // korte delay zodat tweede arduino ook de kans krijgt om informatie te verzenden

	IR_send_direct(waarde);
}


// functie opgesplitst in tweeen. bij ongeldige input, direct request for resend verzenden
void IR_send_direct(AANTAL_BITS_TYPE waarde) {
	// functie zet waardes in variabelen, om in ISR te gebruiken
	if (1 + aantal_verzenden < SEND_RECEIVE_QUEUE_SIZE) { // niet buiten array kunnen schrijven
		aantal_verzenden++;
		send_queue[aantal_verzenden] = waarde;
	}
	// TODO, implementeren dat een waarde gelijk aan RESEND_BITS niet verzonden kan worden?

//	verzend_na_ontvangen = 0; // resetten variabele
	if (aan_het_ontvangen) { // als er nog informatie ontvangen wordt
		// verzend pas nadat informatie ontvangen is (half-duplex)
//		verzend_na_ontvangen = 1;
		// gaat niet goed als er geen stopbit(s) worden gelezen
	} else {
		// voorbereiding
		if (!aan_het_verzenden) {
			prepare_send();
		}

		// laatste regel zodat ISR niet vroegtijdig begint
		aan_het_verzenden = 1; // zet verzenden via timer aan
	}
}


// returned 1 als er nieuwe input is dat nog niet is uitgelezen
uint8_t IR_nieuwe_input(void) {
	if (nieuwe_input) { // nieuwe_input gaat gelijk op met het aantal berichten in de receive_queue array
		return 1;
	} else {
		return 0;
	}
//	return nieuwe_input;
}


AANTAL_BITS_TYPE IR_receive(void) {
	// mogelijk functie aanpassen om interrupt te genereren op ontvangst informatie?
	if (nieuwe_input) {
		AANTAL_BITS_TYPE returnable = receive_queue[nieuwe_input];
		nieuwe_input--;
		return returnable;
	} else {
		return 0;
	}
}


// ===========================================================================


// laatste bericht opnieuw verzenden
void IR_resend(void) {

}


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

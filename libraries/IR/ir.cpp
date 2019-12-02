/*
 *	IR communication library
 */


/* defines */
/*
 * #define MS_PER_TICK (1/(16000000/1024)) // prescaler 1024 timer2 TIJDENS ONTVANGEN, 0,064ms
 * sommige defines moeten handmatig uitgerekend en ingevoerd worden tegen het afronden van de compiler
 */
#if FREQUENCY == 38
#define KHZ 53/*52*/ // timer2 OVF count 38KHZ
#define DUTYCYCLE (KHZ / 2) // duty cycle 50% 38KHZ
#elif FREQUENCY == 56
#define KHZ 36/*36*/ // timer2 OVF count 56KHZ
#define DUTYCYCLE (KHZ / 2) // duty cycle 50% 56KHZ
#else
// exception error, geen (geldige) khz gekozen
#pragma GCC error "geen geldige frequentie gekozen"
#endif
#define BITIS1_MS 30 // ms waarop LED aanstaat voor 1
#define BITIS1 215 /*(BITIS1_MS / MS_PER_TICK)*/
#define BITIS0_MS 20 // ms waarop LED aanstaat voor 0
#define BITIS0 60 /*(BITIS0_MS / MS_PER_TICK)*/
#define STARTBIT_MS 400 // ms waarop LED aanstaat voor startbit
#define STARTBIT 80 /*(STARTBIT_MS / MS_PER_TICK)*/
#define STOPBIT_MS 200 // ms waarop LED aanstaat voor stopbit
#define STOPBIT 40 /*(STOPBIT_MS / MS_PER_TICK)*/
#define OFFSET 10 /*(4 / MS_PER_TICK)*/ // offset waarde voor kleine afwijking (ontvangen), constante geeft ms aan
#define TIJD0_MS 20 // tijd waarop LED tussen bits uit is
#define AGC_TIJD_ONTVANGER_MS 600 // tijd waarop de Automatic Gain Control op de ontvanger moet aanpassen

#define DYNAMIC_TIJD0 // als defined, pas TIJD0 dynamisch aan aan de tijdsduur van de gestuurde bit
#ifdef DYNAMIC_TIJD0
#define MAXTIJD_PER_BIT 60 // tijd van bit + TIJD0, moet groter zijn dan BITIS1_MS & BITIS0_MS
#endif


/* includes */
#include "ir.h"


/* global variables */
volatile uint8_t prevcounter;
volatile uint8_t diffcounter;
volatile uint8_t input = 0x37/*test*/; // bevat de gestuurde byte
volatile uint8_t raw_input; // wordt overgezet naar "input" bij stopbit
volatile uint8_t timer2_ovfs; // telt aantal overflows bij ontvangen data
volatile int aantal_bits; // telt aantal bits of dit geldig is

/* function prototypes */
void schakel_IR_LED(uint8_t aan);
void var_delay_ms(int ms);
void prepare_send(void);
void prepare_receive(void);


/* ISR */
ISR (PCINT2_vect) { // wordt aangeroepen bij logische 1 naar 0 of 0 naar 1 van ontvanger
	/*
	 * sla stand van hardware counter op (timer2)
	 * vergelijk huidige stand met vorige stand
	 * meet de tijd tussen deze interrupts, dus een 0 of 1
	 */

	if (PIND & (1<<PD2)) { // opgaande flank (0 -> 1)
//		USART_Transmit(0x21); // test

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

		if (diffcounter >= (STARTBIT - OFFSET) && diffcounter <= (STARTBIT + OFFSET)) { // startbit
			aantal_bits = 0; // aantal bits check resetten
			USART_Transmit(0x41); // test
		} else if (diffcounter >= (STOPBIT - OFFSET) && diffcounter <= (STOPBIT + OFFSET)) { // stopbit
			if (8 == aantal_bits) { // aantal bits checken op geldigheid
				input = raw_input; // input teruggeven aan programma wanneer alles binnen is
				aantal_bits = 0; // aantal bits check resetten
			}
			USART_Transmit(0x4F); // test
		} else { // byte informatie
			raw_input = (raw_input>>1); // shift input 1 naar rechts, nieuwe bit komt links
			if (diffcounter >= (BITIS1 - OFFSET) && diffcounter <= (BITIS1 + OFFSET)) { // bit is een 1
				raw_input |= (1<<7); // zet MSB op 1
				USART_Transmit(0x31); // test
			} else if (diffcounter >= (BITIS0 - OFFSET) && diffcounter <= (BITIS0 + OFFSET)) { // bit is een 0
				raw_input &= ~(1<<7); // zet MSB op 0 (mag weggelaten worden)
				USART_Transmit(0x30); // test
			} else {
				USART_Transmit(0x21); // test
			}
			aantal_bits++;
		}

		TIMSK2 &= ~(1<<OCIE2A); // OCR2A compare match interrupt uitschakelen, weer aanzetten bij neergaande flank
	} else { // neergaande flank (1 -> 0)
//		TCNT1 = 0; // TCNT1 op 0 zetten? Hoeft niet?
		prevcounter = TCNT2; // onthoud counterstand, als het goed is 0, anders dicht in de buurt van 0.
		TIMSK2 |= (1<<OCIE2A); // OCR2A compare match interrupt, tel aantal overflows in TIMER2_COMPA_vect ISR
		timer2_ovfs = 0;
	}
}

ISR (TIMER2_COMPA_vect) { // wordt aangeroepen bij timer2 overflows, wanneer data wordt ontvangen om tijd te meten
	if (PCMSK2 & (1<<PCINT18)) { // kijk of er wordt ontvangen
		// aangeroepen om de 16,384 ms met prescaler 1024
		timer2_ovfs++;
	} else { // er wordt verzonden
		TCNT2 = 0;
	}
}


/* functions */
void IR_prepare(void) {
	DDRD |= (1<<PD3); // pin 3 output (IR LED)

	/* PCINT - Voor IR ontvanger */ // zie pagina 8 technisch ontwerp
	DDRD &= ~(1<<DDD2); //pin 2 input
	PORTD |= (1<<PORTD2); //pull-up resistor pin 2
	PCICR |= (1<<PCIE2); // pin change interrupt enable 2 (PCINT[23:16])
	/*
	 * PCMSK2 |= (1<<PCINT18); // pin 2 interrupts doorlaten
	 * dit wordt toegepast in functie prepare_receive() zodat dit getoggled kan worden
	 */

	prepare_receive(); // standaard voor luisteren/meten input
//	sei();
}


void IR_send(uint8_t waarde) {
	// voorbereiding
	prepare_send();

	// variabelen
	int vorige_bit_ms = 0;

//	// AGC tijd
//	schakel_IR_LED(1);
//	_delay_ms(AGC_TIJD_ONTVANGER_MS);
//	schakel_IR_LED(0);
//	_delay_ms(TIJD0_MS);

	// startbit
	schakel_IR_LED(1);
	_delay_ms(STARTBIT_MS);
	schakel_IR_LED(0);
	_delay_ms(TIJD0_MS);

	// byte
	for (uint8_t i=1; i<=8; i++) {
		schakel_IR_LED(1);
		if (waarde & (1<<0)) { // LSB is 1
			_delay_ms(BITIS1_MS);

			#ifdef DYNAMIC_TIJD0
			vorige_bit_ms = BITIS1_MS;
			#endif
		} else { // LSB is 0
			_delay_ms(BITIS0_MS);

			#ifdef DYNAMIC_TIJD0
			vorige_bit_ms = BITIS0_MS;
			#endif
		}
		schakel_IR_LED(0);
		#ifndef DYNAMIC_TIJD0 // default
		_delay_ms(TIJD0_MS);

		#else // dynamisch aanpassen TIJD0
		var_delay_ms(MAXTIJD_PER_BIT - vorige_bit_ms);
		#endif

		waarde = (waarde>>1); // volgende bit (van rechts naar links)
	}

	// stopbit
	schakel_IR_LED(1);
	_delay_ms(STOPBIT_MS);
	schakel_IR_LED(0);

	// misschien nog toepassen dat berichten even lang duren door uit-tijd dynamisch aan te passen

	// luisteren naar nieuwe input ontvanger
	prepare_receive();
}


uint8_t IR_receive(void) {
	// mogelijk functie aanpassen om interrupt te genereren op ontvangst informatie
	return input;
}

// ===========================================================================

// voor aan- en uitschakelen IR LED
void schakel_IR_LED(uint8_t aan) {
	if (aan) { // LED aan
		TCCR2A |= (1<<COM2B1);
	} else { // LED uit
		TCCR2A &= ~(1<<COM2B1);
	}
}

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
//	GTCCR |= (1<<PSRASY); // reset prescaler timer2
	TCCR2A |= (1<<WGM21) | (1<<WGM20); // fast PWM
//	TCCR2B |= (1<<WGM22); // fast PWM
	TCCR2B |= /*(1<<CS22) | */(1<<CS21)/* | (1<<CS20)*/; // prescaler 8, (Prescaler 1 maakt 38 en 56 KHz nagenoeg onmogelijk (zeer ingewikkeld om te realiseren)
	TCCR2B &= ~(1<<CS22) & (1<<CS20); // uitzetten settings receive
	/*
	 * TCCR2A |= (1<<COM2B1); // clear on compare, non-inverting-mode
	 * deze regel wordt gebruikt om IR LED aan/uit te zetten,
	 * het wordt aangeroepen in IR_send()
	 */
	TCCR2A |= (1<<COM2A0);
//	TIFR2 |= (1<<OCF2A); // compare interrupt OCR2A

	OCR2A = KHZ;
	OCR2B = DUTYCYCLE;
}

void prepare_receive(void) {
	/* TIMER2 - Voor tellen delays */
//	GTCCR |= (1<<PSRASY); // reset prescaler timer2
	TCCR2A |= (1<<WGM21); // CTC, OCRA top
	TCCR2B &= ~(1<<WGM20); // uitzetten settings send
//	TCCR2B &= ~(1<<WGM22); // uitzetten settings send
	TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20); // prescaler 1024
	OCR2A = 255; // max 2^8 = 255 (256-1)
	OCR2B = 0; // uitzetten settings send
	TCCR2B &= ~(1<<COM2A0);
//	TIFR2 &= ~(1<<OCF2A); // uitzetten settings send
	/*
	 * TIMSK2 |= (1<<OCIE2A); // OCR2A compare match interrupt, ga naar TIMER2_COMPA_vect ISR
	 * deze regel wordt in de ISR aangeroepen zodat alleen interrupts worden gegenereerd wanneer nodig
	 */

	PCMSK2 |= (1<<PCINT18); // interrupts van ontvanger doorlaten
}

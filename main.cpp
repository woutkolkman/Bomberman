/* defines */
#define FREQUENCY 56 // 38/56, geef frequentie aan IR LED
#define BAUD 9600 // baudrate USART
#define PLAYER 1 // 1/2
//#define ADC_FREERUNNING // als dit defined is werkt de ADC op freerunning
#define VAR_TYPE_IR uint8_t // variabele type voor IR communicatie


/* includes */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <cspi.h>
#include <usart.h>
#include <Wire.h>
#include <stdint.h>
#include "libraries/IR/ir.h" // IR library
//#include "ir.h"
// ... // LCD library


/* global variables */
volatile uint8_t brightness = 0;


/* function prototypes */
void adc_init(void);
void init(void);
void timer0_init(void);
void test_ir(void); // test
//void timer1_init();
#ifndef ADC_FREERUNNING
void single_conversion(void);
#endif
void ir_ontcijfer(VAR_TYPE_IR input);
void ir_verzenden(void);


/* ISR */
ISR(ADC_vect) { // wordt aangeroepen wanneer ADC conversie klaar is
	brightness = (ADC>>2); // 10 bits, gooi 2 LSB weg, uitkomst 8 bits

	// brightness toepassen op beeldscherm
}


int main(void) {
	/* setup */
	init(); // initialize

	/* loop */
	for(;;) {
		#ifndef ADC_FREERUNNING
//		single_conversion();
		#endif

		test_ir();
	}


	/* never reached */
	return 0;
}


void init() {
	// init Wire
	USART_Init(); // init serial
	IR_prepare(FREQUENCY); // init IR
	// init CSPI
//	timer0_init();
//	timer1_init();
//	timer2_init();
//	adc_init();

	// pin in/outputs
	/*
	 * TFT scherm : digital 13-9
	 * Touchscreen : digital 8
	 * MicroSD lezer : digital 4 (als die wordt gebruikt)
	 * IR-zender : digital 3
	 * IR-ontvanger (?) : digital 2
	 * UART verbinding PC : digital 1, 0
	 * Podmeter : analog 2
	 * Nunchuck : analog 4, 5
	 */
	DDRB |= (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5); // TFT scherm

	sei(); // set global interrupt flag
}


void test_ir() {
	#define IR_TEST 3 // 0(uit)/1/2/3/4

	#if IR_TEST == 1
	if (IR_nieuwe_input()) { IR_send((IR_receive() + 1)); }
	#elif IR_TEST == 2
	VAR_TYPE_IR test_input;
	test_input = USART_Receive();
	if (test_input != 0x00) { IR_send(test_input); }
	test_input = 0x00;
	_delay_ms(3000);
	if (IR_nieuwe_input()) { USART_Transmit(IR_receive()); }
	#elif IR_TEST == 3
//	IR_send(0xAA); // 1010 1010
//	IR_send(0xFF);
//	IR_send(0x00);
	IR_send(0x32); // 0011 0010, print '2'
	_delay_ms(1500);
	#elif IR_TEST == 4
	USART_Transmit(IR_receive());
	_delay_ms(3000);
	#endif
}


// functie voor het ontcijferen en verwerken van nieuwe IR input
void ir_ontcijfer(VAR_TYPE_IR input) {
	// roep functie aan bij nieuwe informatie (PCINT?)

	// bepaal type informatie (zie laatste 3 bits)
	VAR_TYPE_IR kopie = input;
	kopie = (kopie>>5);
	if (kopie == 0x00) {
		// type 1
	} else if (kopie == 0x01) {
		// type 2
	} // etc.

	// verwerk input naar variabelen
	// ...
}


// functie voor het verzamelen en verzenden van IR output
void ir_verzenden() {
	// roep functie aan op gameticks

	VAR_TYPE_IR waarde = 0x00;

	// bepaal volgende type informatie en stel laatste 3 bits in
	// ...

	// haal informatie op en stel rest van de bits in
	// ...

	IR_send(waarde);
}


void timer0_init() {
	
}


//void timer1_init() {
//	
//}


void adc_init() { // initialiseer ADC, voor podmeter / brightness scherm
	ADMUX |= /*(1<<REFS1) | */(1<<REFS0); // reference voltage on AVCC (5V)
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // ADC clock prescaler ...(nog kiezen)
	ADMUX |= (1<<MUX1); // input kanaal A2
	ADCSRA |= (1<<ADIE); // ADC interrupt enable, ADC_vect

	#ifdef ADC_FREERUNNING
	ADCSRA |= (1<<ADATE); // ADC auto trigger enable \/
	ADCSRB &= ~(1<<ADTS2) & ~(1<<ADTS1) & ~(1<<ADTS0); // free running mode
	ADCSRA |= (1<<ADEN); // enable ADC
        ADCSRA |= (1<<ADSC); // start eerste meting
	#else
	ADCSRA |= (1<<ADEN); // enable ADC
	#endif
}


#ifndef ADC_FREERUNNING
void single_conversion() {
	ADCSRA |= (1<<ADSC); // start single ADC conversion
//	while (ADCSRA & (1<<ADSC)); // wait until done

	// values worden in de ISR gezet
}
#endif

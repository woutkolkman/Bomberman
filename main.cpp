/* defines */
#define FREQUENCY 38 // 38/56
#define BAUD 9600
#define PLAYER 1 // 1/2
//#define ADC_FREERUNNING // als dit defined is werkt de ADC op freerunning


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
// ... // LCD library


/* global variables */
volatile uint8_t brightness = 0;


/* function prototypes */
void adc_init();
void init();
void timer0_init();
//void timer1_init();
void ir_init();
#ifndef ADC_FREERUNNING
void single_conversion();
#endif


/* ISR */
ISR(ADC_vect) { // wordt aangeroepen wanneer ADC conversie klaar is
	brightness = (ADC>>2); // 10 bits, gooi 2 LSB weg, uitkomst 8 bits

	// brightness toepassen op beeldscherm
}


int main(void) {
	/* setup */
	init(); // initialize
//	prepare_receive(); // test
//	prepare_send(); // test

	/* loop */
	for(;;) {
		#ifndef ADC_FREERUNNING
//		single_conversion();
		#endif

//		IR_send(0xAA); // 1010 1010
//		IR_send(0xFF);
//		IR_send(0x00);
//		IR_send(0x32); // 0011 0010
//		USART_Transmit(IR_receive()); // test
		_delay_ms(3000);

		#define TEST 0 // 0(uit)/1/2
		#if TEST == 1
		if (IR_nieuwe_input()) { IR_send(IR_receive() + 1); }
		#elif TEST == 2
		uint8_t test_input;
		test_input = USART_Receive();
		if (test_input != 0x00) { IR_send(test_input); }
		test_input = 0x00;
		_delay_ms(3000);
		if (IR_nieuwe_input()) { USART_Transmit(IR_receive()); }
		#endif
	}


	/* never reached */
	return 0;
}


void init() {
	// init Wire
	USART_Init(); // init serial
	ir_init(); // init IR
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


void ir_init() {
	IR_prepare();
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

/* defines */
#define FREQUENCY 38 // 38/56
#define BAUD 9600
#define IR_RECEIVE_PIN PD2
#define IR_SEND_PIN PD3
#define NUMBITS 8


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
//#include "./libraries/IRremote-2.2.3/IRremote.h" // test library voor IR
// ... // LCD library


/* global variables */
volatile uint8_t brightness = 0;
//volatile IRsend irsend;


/* function prototypes */
void adc_init();
void init();
void timer0_init();
//void timer1_init();
//void timer2_init();
void ir_init();


/* ISR */
//ISR(TIMER1_COMPA_vect) {
//	TCCR2A ^= (1<<COM2A1); //toggle timer2 fastPWM/off
//}

ISR(ADC_vect) { // wordt aangeroepen wanneer ADC conversie klaar is
	brightness = (ADC>>2); // 10 bits, gooi 2 LSB weg, uitkomst 8 bits

	// brightness toepassen op beeldscherm
}


int main(void) {
	/* setup */
	init(); // initialize


	/* loop */
	for(;;) {
//		for (long i=0; i<2000000; i++) {}
//		IR_send(10101010);
//		IR_send(0xFF);
//		TCCR2A ^= (1<<COM2B1);
//		USART_Transmit(getInput());
//		_delay_ms(50000);
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
//	adc_init();

	// pin in/outputs
	/*
	 * TFT scherm : digital 13-9
	 * Touchscreen : digital 8
	 * MicroSD lezer : digital 4 (als die wordt gebruikt)
	 * IR-zender : digital 3
	 * IR-ontvanger (?) : digital 2
	 * UART verbinding PC : digital 1, 0
	 * ? : analog 2
	 * Nunchuck : analog 4, 5
	 */
	DDRD |= (1<<DDD3); // IR-zender
	DDRD &= ~(1<<DDD2); //IR-ontvanger
	PORTD |= (1<<PORTD2); //pull-up resistor voor ontvanger
	DDRB |= (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5); // TFT scherm
	DDRD |= (1<<DDD0) | (1<<DDD1); //UART

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

//void timer2_init() {
//	
//}

void adc_init() { // initialiseer ADC, voor podmeter / brightness scherm
	ADMUX |= (1<<REFS0); // reference voltage on AVCC (5V)
	ADCSRA |= (1<<ADIE); // ADC interrupt enable
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // ADC clock prescaler ...(nog kiezen)

	ADCSRA |= (1<<ADATE); // ADC auto trigger enable \/
	ADCSRB &= ~(1<<ADTS2) & ~(1<<ADTS1) & ~(1<<ADTS0); // free running mode

	ADCSRA |= (1<<ADEN); // enable ADC
        ADCSRA |= (1<<ADSC); // start eerste meting
}

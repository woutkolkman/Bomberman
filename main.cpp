/* defines */
#define HALFDUTYCYCLE 128;
#define KHZ38 421;
#define BAUD 9600


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
void timer1_init();
void timer2_init();


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
		
	}


	/* never reached */
	return 0;
}

void init() {
	// init Wire
	USART_Init(); // init serial
	// init IR
	// init CSPI
	timer0_init();
	timer1_init();
	timer2_init();
	adc_init();

	// pin in/outputs
	/*
	 * TFT scherm : digital 13-9
	 * Touchscreen : digital 8 (als deze wordt gebruikt)
	 * MicroSD lezer : digital 4 (als die wordt gebruikt)
	 * IR-zender : digital 3
	 * IR-ontvanger (?) : digital 2
	 * UART verbinding PC : digital 1, 0
	 * ? : analog 2
	 * Nunchuck : analog 4, 5
	 */
	DDRD |= (1<<DDD3); // IR-zender
	DDRD |= (1<<DDD2); // IR-ontvanger
	DDRB |= (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5); // TFT scherm
	//DDRB |= (1<<PB0); //touchscreen
	//DDRD |= (1<<PD4); //SD lezer

	DDRD |= (1<<DDD0) | (1<<DDD1); //UART
	DDRC |= (1<<DDC4) /*?*/ | (1<<DDC5); //nunchuck I2C

	sei(); // set global interrupt flag
}

void timer0_init() {
	
}

void timer1_init() {
	
}

void timer2_init() {
	
}

void adc_init() { // initialiseer ADC
	ADMUX |= (1<<REFS0); // reference voltage on AVCC (5V)
	ADCSRA |= (1<<ADIE); // ADC interrupt enable
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // ADC clock prescaler ...(nog kiezen)

	ADCSRA |= (1<<ADATE); // ADC auto trigger enable \/
	ADCSRB &= ~(1<<ADTS2) & ~(1<<ADTS1) & ~(1<<ADTS0); // free running mode

	ADCSRA |= (1<<ADEN); // enable ADC
        ADCSRA |= (1<<ADSC); // start eerste meting
}


/* includes */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "libraries/IR/ir.h" // IR library
// ... // LCD library

// Nadia Kraken test 2

/* defines and global variables */
volatile uint8_t brightness = 0;


/* function prototypes */
void adc_init();
void init();


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
	// init UART
	// init IR
	// init CSPI
	timer0_init();
	timer1_init();
	timer2_init();
	adc_init();

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
	DDRD |= (1<<PD3); // IR-zender
	DDRD |= (1<<PD13) | (1<<PD12) | (1<<PD11) | (1<<PD10) | (1<<PD9); // TFT scherm

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
	ADCSRB &= ~(1<<ADTS2) | ~(1<<ADTS1) | ~(1<<ADTS0); // free running mode

	ADCSRA |= (1<<ADEN); // enable ADC
        ADCSRA |= (1<<ADSC); // start eerste meting
}


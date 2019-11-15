/* includes */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


/* defines */
#define TEST


/* function prototypes */
void adc_init();
void init();


/* ISR */
ISR(ADC_vect) { // wordt aangeroepen wanneer ADC conversie klaar is
	brightness = (ADC>>2); // 10 bits, gooi 2 LSB weg, uitkomst 8 bits
}


int main(void) {
	/* setup */
	// initialize
	init();


	/* loop */
	for(;;) {
		
	}


	/* never reached */
	return 0;
}

void init() {
	// init wire
	// init uart
	// init IR
	// init timer0
	// init timer1
	// init timer2
	adc_init();

	// pin in/outputs

	sei(); // set global interrupt flag
}

void adc_init() { // initialiseer ADC
	ADMUX |= (1<<REFS0); // reference voltage on AVCC (5V)
	ADCSRA |= (1<<ADIE); // ADC interrupt enable
	// ...
}

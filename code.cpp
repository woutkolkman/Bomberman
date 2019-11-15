/* includes */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


/* defines */



/* function prototypes */
void adc_init();
void init();


/* ISR */


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
	
}

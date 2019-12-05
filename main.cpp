/* defines */
//#define ADDRESS 0x52 // I2C Wire adress nunchuk
#define GAMETICK_FREQUENCY 0.3 // gameticks in HZ, max 0,119HZ, min 7812,5HZ
#define FCLK 16000000 // arduino clock frequency
#define PRESCALER_TIMER1 1024 // prescaler, zie ook functie timer1_init()
#define OFFSET_VAKJE 24 // breedte & hoogte van een vakje
#define OFFSET_PLAYER_X 12 // offset waarop player in vakje zit X
#define OFFSET_PLAYER_Y 20 // offset waarop player in vakje zit Y


/* includes */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "libraries/IR/ir.h" // IR library
//#include <Adafruit_ILI9341.h>
//#include <Adafruit_GFX.h>
//#include <Arduino.h>
#include <Wire.h>
//#include "libraries/Nunchuk/Nunchuk.h"
#include <Nunchuk.h>
#include "nunchuk.cpp"


/* global variables */
volatile uint8_t brightness = 0;
volatile uint8_t player1_x = 0;
volatile uint8_t player1_y = 0;
volatile uint8_t player2_x = 0;
volatile uint8_t player2_y = 0;


/* function prototypes */
void adc_init(void);
void init(void);
void timer0_init(void);
void timer1_init(void);
void adc_init(void);


/* ISR */
ISR(ADC_vect) { // wordt aangeroepen wanneer ADC conversie klaar is
	brightness = (ADC>>2); // 10 bits, gooi 2 LSB weg, uitkomst 8 bits

	// brightness toepassen op beeldscherm
}


ISR(TIMER1_COMPA_vect) { // gameticks
	
}


int main(void) {
	/* setup */
	init(); // initialize

	/* loop */
	for(;;) {
		Nunchuk.getState(ADDRESS); // retrieve states joystick and buttons Nunc$

		// code to move block over x axis and y axis (on sides)
		moveCharacterRight(8);
		moveCharacterLeft(0);
		moveCharacterUp(8);
		moveCharacterDown(8);
	}


	/* never reached */
	return 0;
}


void init(void) {
	// init UART
	// init IR
	// init CSPI
	timer0_init();
	timer1_init();
	tft.begin();
	Wire.begin();
	nunchuk_init();
	screen_init();

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
//	DDRB |= (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5); // TFT scherm
//	DDRB |= (1<<PB0); //touchscreen
//	DDRD |= (1<<PD4); //SD lezer

	sei(); // set global interrupt flag
}


void timer0_init(void) {
	
}


void timer1_init(void) { // gameticks timer 1
	TCCR1B |= (1<<WGM12); // CTC, OCR1A top
	OCR1A = (FCLK / (GAMETICK_FREQUENCY * 2 * PRESCALER_TIMER1)); // frequentie aangeven

	#if PRESCALER_TIMER1 == 1024
	TCCR1B |= (1<<CS12) /*| (1<<CS11)*/ | (1<<CS10); // prescaler 1024
	#else
	#pragma GCC error "geen bruikbare prescaler ingesteld"
	#endif

	TIMSK1 |= (1<<OCIE1A); // output compare match interrupt A enable
}


void adc_init(void) { // initialiseer ADC
	ADMUX |= (1<<REFS0); // reference voltage on AVCC (5V)
	ADCSRA |= (1<<ADIE); // ADC interrupt enable
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // ADC clock prescaler ...(nog kiezen)

	ADCSRA |= (1<<ADATE); // ADC auto trigger enable \/
	ADCSRB &= ~(1<<ADTS2) & ~(1<<ADTS1) & ~(1<<ADTS0); // free running mode

	ADCSRA |= (1<<ADEN); // enable ADC
        ADCSRA |= (1<<ADSC); // start eerste meting
}

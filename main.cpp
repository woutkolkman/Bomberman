/* defines */
#define BAUD 9600
#define TFT_DC 9 // initialisatie LCD
#define TFT_CS 10 // initialisatie LCD
#define AANTALLENGTEBREEDTE 9//aantal hokjes in lengte en breedte
#define LIGHTBROWN 0x7A00
#define DARKBROWN 0x5980
#define XUP 10
#define YUP 50
#define OBJOFFSET 2
#define MAXOBJ 8

/* includes */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "libraries/IR/ir.h" // IR library
#include <Adafruit_ILI9341.h> // LCD library
#include <Adafruit_GFX.h>// LCD library
#include <Arduino.h> // LCD library
#include <avr/io.h> // LCD library
#include <SPI.h>
#include <cspi.h>
#include <usart.h>

/* global variables */
volatile uint8_t brightness = 0;
uint8_t lw = 220 / AANTALLENGTEBREEDTE;

/* Use Hardware SPI (on Uno, #13, #12, #11) and #10 and # 9for  CS/DC   */
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

/* function prototypes */
void adc_init();
void init_2();
void timer1_init();
void drawGrid();
void drawHeartLeft();
void drawHeartRight();
void drawPlayer1(uint8_t x, uint8_t y);
void drawPlayer2(uint8_t x, uint8_t y);
void drawBomb(uint8_t x, uint8_t y);
void drawTon(uint8_t x, uint8_t y);
/* ISR */
ISR(ADC_vect) { // wordt aangeroepen wanneer ADC conversie klaar is
	brightness = (ADC>>2); // 10 bits, gooi 2 LSB weg, uitkomst 8 bits

	// brightness toepassen op beeldscherm
}
ISR(TIMER1_OVF_vect /*TIMER1_COMPA_vect*/) {
//	gametick
}

int main(void) {
	/* setup */
	//USART_Transmit(0x76);
	init();
	tft.begin();
	//scherm is 240 * 320 pixels
	tft.fillScreen(LIGHTBROWN);
	//tft.drawRect(10, 50, 220, 220, ILI9341_WHITE);
	drawHeartLeft();
	drawHeartRight();
	drawGrid();
	drawPlayer1(8, 0);
	drawPlayer2(0, 8);
	drawBomb(4, 2);

	/* loop */
	for(;;){
		//USART_Transmit(0x76);
		//_delay_ms(1000);
	}


	/* never reached */
	return 0;
}

void init_2() {
	// init Wire
	USART_Init();// init UART
	// init IR
	// init CSPI
	//timer0_init();
	//timer1_init();
	//timer2_init();
	//adc_init();

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

void adc_init() { // initialiseer ADC
	ADMUX |= (1<<REFS0); // reference voltage on AVCC (5V)
	ADCSRA |= (1<<ADIE); // ADC interrupt enable
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // ADC clock prescaler ...(nog kiezen)

	ADCSRA |= (1<<ADATE); // ADC auto trigger enable \/
	ADCSRB &= ~(1<<ADTS2) & ~(1<<ADTS1) & ~(1<<ADTS0); // free running mode

	ADCSRA |= (1<<ADEN); // enable ADC
        ADCSRA |= (1<<ADSC); // start eerste meting
}

void timer1_init() {
TCCR1B |= (1<<WGM12); //CTC mode
TCCR1B |= (1<<CS11); //prescaling 8
TIMSK1 |= (1<<TOIE1); //overflow interupt enable
//TIMSK1 |= (1<<OCIEA); //compare output interrupt enable
}

void drawGrid() {
        tft.fillRect(XUP, YUP, AANTALLENGTEBREEDTE*lw, AANTALLENGTEBREEDTE*lw, DARKBROWN);
        for(int x = 0; x < 9; x++) {
                for(int y = 0; y < 9; y++) {
                        tft.drawRect((x*lw) + XUP, (y*lw) + YUP, lw+1, lw+1, ILI9341_BLACK);
                }
        }
}
void drawHeartLeft() {
	tft.fillTriangle(190, 25, 200, 15, 200, 35, ILI9341_RED);
	tft.fillCircle(203, 30, 5, ILI9341_RED);
	tft.fillCircle(203, 20, 5, ILI9341_RED);
}
void drawHeartRight() {

}
void drawPlayer1(uint8_t x, uint8_t y) {
	tft.fillRect(x*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET + 1, lw - 2*OBJOFFSET + 1, ILI9341_CYAN);
}
void drawPlayer2(uint8_t x, uint8_t y) {
	tft.fillRect(x*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET + 1, lw - 2*OBJOFFSET + 1, ILI9341_RED);
}
void drawBomb(uint8_t x, uint8_t y) {
	tft.fillCircle(x*lw + XUP + (0.3*lw), y*lw + YUP + (0.3*lw), 5, ILI9341_BLACK);
}
void drawTon(uint8_t x, uint8_t y) {
	
}

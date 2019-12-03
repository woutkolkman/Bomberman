/* defines */
#define BAUD 9600
#define TFT_DC 9 // initialisatie LCD
#define TFT_CS 10 // initialisatie LCD
#define AANTALLENGTEBREEDTE 9//aantal hokjes in lengte en breedte
#define XUP 50 //offset from screen border
#define YUP 10 //ofset from screen border
#define OBJOFFSET 2 //no overlap with line
#define MAXOBJ 8 //object max x/y axis
#define ROTATION 3 //rotation of screen
#define HOFFSET 1 //don't draw over line

/* Colour defines */
#define LIGHTBROWN 0x7A00
#define TONBROWN 0x28A0
#define DARKBROWN 0x5980
#define SKIN 0xF5D0
#define PLAYER1 0x135F
#define PLAYER2 ILI9341_RED
#define GRIDCOLOUR DARKBROWN
#define MAPCOLOUR LIGHTBROWN
#define HEARTCOLOUR ILI9341_RED

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
uint8_t livesleft = 3; //REMOVE


/* Use Hardware SPI (on Uno, #13, #12, #11) and #10 and # 9for  CS/DC   */
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

/* function prototypes */
void adc_init();
void init_2();
void timer1_init();
void initGame();
void drawGrid();
void drawPlayer1Field();
void drawPlayer2Field();
void drawPlayer1(uint8_t x, uint8_t y);
void drawPlayer2(uint8_t x, uint8_t y);
void drawBomb(uint8_t x, uint8_t y);
void drawTon(uint8_t x, uint8_t y);
void drawMap();

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
	initGame();
	drawMap(); //

	//scherm is 240 * 320 pixels

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

void initGame() {
	tft.setRotation(3); //set rotation;
	tft.fillScreen(LIGHTBROWN); //lichtbruine achtergrond volledige scherm
}

void drawMap(){
	//scherm is 240 * 320 pixels
	tft.fillScreen(MAPCOLOUR);
	drawPlayer1Field();
	drawPlayer2Field();
	drawGrid();
	drawPlayer1(8, 0);
	drawPlayer2(0, 8);
	drawBomb(4, 2);
	drawTon(4, 3);
	drawTon(6, 6);
	drawTon(7, 5);
	drawTon(5, 7);
	drawTon(1, 3);
	drawTon(2, 0);
}

void drawGrid() {
        tft.fillRect(XUP /*niet op grens van scherm X */, YUP/*niet op grens van scherm Y*/, AANTALLENGTEBREEDTE*lw /*volledige game-grid*/, AANTALLENGTEBREEDTE*lw /*volledige game-grid*/, GRIDCOLOUR /*donkerbruine achtergrond*/);
        for(int x = 0; x < 9; x++) {
                for(int y = 0; y < 9; y++) {
                        tft.drawRect((x*lw) + XUP, (y*lw) + YUP, lw+1, lw+1, ILI9341_BLACK); //lijnen tussen grid
                }
        }
}

void drawHeart(uint16_t x, uint16_t y, uint16_t b, uint16_t h) {
	tft.fillTriangle((x + 0.5*b), (y + h), x, (y + 0.44*h), (x + b), (y + 0.44*h), HEARTCOLOUR); //driehoek van hartje
	tft.fillCircle((x+0.25*b), (y + 0.28*h), (0.25*b), HEARTCOLOUR); //cirkel linksboven van hartje
        tft.fillCircle((x+0.75*b), (y + 0.28*h), (0.25*b), HEARTCOLOUR); //cirkel rechtsboven van hartje
}

void drawPlayer1Field() {
	drawHeart(15, 20, 20, 18); //teken hartje
	if(livesleft >= 2) {
		drawHeart(15, 40, 20, 18); //als 2 levens, teken 2e hartje
	}if(livesleft == 3) {
		drawHeart(15, 60, 20, 18); //als 3 levens, teken 3e hartje
	}
}

void drawPlayer2Field() {
	drawHeart(285, 200, 20, 18); //teken hartje
	if(livesleft >= 2) {
		drawHeart(285, 180, 20, 18); //als 2 levens, teken 2e hartje
	} if(livesleft == 3) {
		drawHeart(285, 160, 20, 18); //als 3 levens, teken 3e hartje
	}
}

void drawPlayer1(uint8_t x, uint8_t y) { 
	// fillRect( x, y, w, h, c)
	// fillCircle( x, y, r, c)
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 7, y*lw + YUP + (0.3*lw) + 5, 5, SKIN); // head
	/* Hat  */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 15, (y*lw) + YUP + OBJOFFSET + 5, lw - 2*OBJOFFSET -15 , lw - 2*OBJOFFSET - 9, PLAYER1); // main hat
	tft.drawRect(x*lw + XUP + OBJOFFSET + 15, (y*lw) + YUP + OBJOFFSET + 5, lw - 2*OBJOFFSET -15 , lw - 2*OBJOFFSET - 9, ILI9341_BLACK);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 13, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET -16 , lw - 2*OBJOFFSET - 9, PLAYER1); // brim
	tft.drawRect(x*lw + XUP + OBJOFFSET + 13, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET -16 , lw - 2*OBJOFFSET - 9, ILI9341_BLACK);
	/* Body  */

}

void drawPlayer2(uint8_t x, uint8_t y) {
	tft.fillRect(x*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET + 1, lw - 2*OBJOFFSET + 1, PLAYER2);
	tft.fillCircle(x*lw + XUP + (0.3*lw), y*lw + YUP + (0.3*lw), 5, SKIN); // head
	//tft.fillRect(x*lw + XUP + OBJOFFSET + 15, (y*lw) + YUP + OBJOFFSET + 5, lw - 2*OBJOFFSET -15 , lw - 2*OBJOFFSET - 9, PLAYER2); // hat
	//tft.drawRect(x*lw + XUP + OBJOFFSET + 15, (y*lw) + YUP + OBJOFFSET + 5, lw - 2*OBJOFFSET -15 , lw - 2*OBJOFFSET - 9, ILI9341_BLACK); // hat
	//tft.fillRect(x*lw + XUP + OBJOFFSET + 13, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET -16 , lw - 2*OBJOFFSET - 9, PLAYER2); // hat
	//tft.drawRect(x*lw + XUP + OBJOFFSET + 13, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET -16 , lw - 2*OBJOFFSET - 9, ILI9341_BLACK); // hat
}

void drawBomb(uint8_t x, uint8_t y) { 
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 3, y*lw + YUP + (0.3*lw) + 5, 5, ILI9341_BLACK); // lichaam bom
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11 , (y*lw) + YUP + OBJOFFSET + 9.5 , lw - 2*OBJOFFSET -13  , lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // lontje bom
}

void drawTon(uint8_t x, uint8_t y) { 
	//lw = 220 / 9 = 24,444  objoffset = 2 24,444 - 2*2 = 20,444
	// x = 4, lw = 220/9, XUP = 10 x*lw+xup+0.3*lw = 4*220/9 +10+ 0.3*220/9 = 115,11111111111111
	//tft.fillRect( x-as , y-as , width , hight , colour );
	//	      |       X-as	     |          Y-as	       |       Width         |        Heigth       | Colour
	//tft.fillRect(x*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET + 1, lw - 2*OBJOFFSET + 1, TONBROWN);
	//tft.fillCricle( x-as , y-as, Radius , colour );
	// 	        |    X-as center      |     Y-as center      | Radius | Colour
	//tft.fillCircle(x*lw + XUP + (0.3*lw), y*lw + YUP + (0.3*lw),   5    , ILI9341_PINK);

	tft.fillRect(x*lw + XUP + OBJOFFSET + 3 , (y*lw) + YUP + OBJOFFSET + 3 , lw - 2*OBJOFFSET - 5, lw - 2*OBJOFFSET - 5, TONBROWN); // lichaam ton
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 8, y*lw + YUP + (0.3*lw) + 5,   7   , TONBROWN); // lichaam ton
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 2, y*lw + YUP + (0.3*lw) + 5,   7   , TONBROWN);	// lichaam ton
	tft.fillRect(x*lw + XUP + OBJOFFSET + 5 , (y*lw) + YUP + OBJOFFSET + 3 , lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 5, ILI9341_BLACK); // details
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12 , (y*lw) + YUP + OBJOFFSET + 3 , lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 5, ILI9341_BLACK); // details
}

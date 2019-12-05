/* defines */
#define BAUD 9600
#define AANTALLENGTEBREEDTE 9//aantal hokjes in lengte en breedte
#define XUP 50 //offset from screen border
#define YUP 10 //ofset from screen border
#define OBJOFFSET 2 //no overlap with line
#define MAXOBJ 8 //object max x/y axis

//LCD init defines
#define TFT_DC 9 // initialisatie LCD
#define TFT_CS 10 // initialisatie LCD
#define ROTATION 3 //rotation of screen

//title
#define TITLETPOSX 50
#define TITLETPOSY 10
#define TITLETSIZE 4 //start button text size
//mainmenucolors
#define ACOLOR ILI9341_PURPLE
#define BCOLOR ILI9341_YELLOW
#define ECOLOR DARKBROWN
#define MCOLOR ILI9341_RED
#define NCOLOR ILI9341_NAVY
#define OCOLOR ILI9341_CYAN
#define RCOLOR ILI9341_WHITE
#define TEXTCOLOR ILI9341_BLACK
#define SELECTEDTEXTCOLOR ILI9341_GREEN
#define SHADOWCOLOR ILI9341_LIGHTGREY

//buttoncolor defines
#define STARTBUTCOLOR 0x0575
#define STARTBUTSELCOLOR 0xAFFF
#define STCOLOR ILI9341_BLACK
#define STSELCOLOR ILI9341_BLACK
#define HSBUTCOLOR 0x0500
#define HSBUTSELCOLOR 0x87F0
#define HSTCOLOR ILI9341_BLACK
#define HSTSELCOLOR ILI9341_BLACK
#define QUITBUTCOLOR 0xC800
#define QUITBUTSELCOLOR 0xFAAA
#define QUITTCOLOR ILI9341_BLACK
#define QUITTSELCOLOR ILI9341_BLACK

//startbutton defines
#define STARTBUTRX 50 //start button rectangle position x
#define STARTBUTRY 50 //start button rectangle position y
#define STARTBUTRW 220 //start button rectangle width
#define STARTBUTRH 40 //start button rectangle height
#define STARTBUTTPOSX 125 //start button text position x
#define STARTBUTTPOSY 65 //start button text position y
#define STARTBUTTSIZE 2 //start button text size
#define STARTBUTSTPOSX STARTBUTTPOSX + 2
#define STARTBUTSTPOSY STARTBUTTPOSY - 2

//High score button defines
#define HSBUTRX 50
#define HSBUTRY 100
#define HSBUTRW 220
#define HSBUTRH 40
#define HSBUTTPOSX 95
#define HSBUTTPOSY 115
#define HSBUTTSIZE 2
#define HSBUTSTPOSX HSBUTTPOSX + 2
#define HSBUTSTPOSY HSBUTTPOSY - 2

//Quit button defines
#define QUITBUTRX 50
#define QUITBUTRY 150
#define QUITBUTRW 220
#define QUITBUTRH 40
#define QUITBUTTPOSX 128
#define QUITBUTTPOSY 165
#define QUITBUTTSIZE 2
#define QUITBUTSTPOSX QUITBUTTPOSX + 2
#define QUITBUTSTPOSY QUITBUTTPOSY - 2

/* Colour defines */
#define LIGHTBROWN 0x7A00
#define TONBROWN 0x28A0
#define DARKBROWN 0x5980
#define SKIN 0xF5D0
#define PLAYER1 0x135F
#define PLAYER2 0xF2EB
#define GRIDCOLOUR DARKBROWN
#define MAPCOLOUR LIGHTBROWN
#define HEARTCOLOUR ILI9341_RED
#define MOOIEBRUIN 0x6101
#define LONT 0xFDAB
#define LONT2 0xDC29
#define FIRE 0xF9E1
#define MAINMENUCOLOR ILI9341_BLACK
#define FIRESPREAD ILI9341_RED
#define WALL 0x6B8E

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
uint8_t mainmenuselect = 0;

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
void drawMainMenu();
void drawTitle();
void drawStart();
void drawHighScore();
void drawQuit();
void drawBombExplosie(uint8_t x, uint8_t y);
void fireSpread(uint8_t x, uint8_t y);
void drawTitleBomb();
void drawWall(uint8_t x, uint8_t y);
void drawMap2();

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
	//drawMap(); //draw Map
	drawMainMenu();
	//drawMap2(); 

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
	//tft.fillScreen(LIGHTBROWN); //lichtbruine achtergrond volledige scherm
}

void drawMap(){
	//scherm is 240 * 320 pixels
	tft.fillScreen(MOOIEBRUIN);
	drawWall();
	drawPlayer1Field();
	drawPlayer2Field();
	drawGrid();
	drawPlayer1(0, 0);
	drawPlayer2(8, 8);
	drawBomb(4, 2);
	drawTon(4, 3);
	drawTon(6, 6);
	drawTon(7, 5);
	drawTon(5, 7);
	drawTon(1, 3);
	drawTon(2, 0);
	drawBombExplosie(0, 3);
	livesleft = 2;
	drawPlayer2Field();
	drawBombExplosie(4, 0);
	drawPlayer1Field();
	drawBombExplosie(8, 3); 
	livesleft = 1;
	drawPlayer1Field();
	drawBombExplosie(3, 8); 
}

void drawMap2(){ 
	tft.fillScreen(MOOIEBRUIN);
	drawGrid();
	drawPlayer1Field(); // hartjes
	drawPlayer2Field();
	/* draw walls */	
	for(int x = 1; x < 8; x = x+2){
		for(int y = 1; y < 8; y = y+2){
			drawWall(x,y);		
		}	
	}	
	//drawBombExplosie(2, 1);
	//drawBombExplosie(4, 3);
	/* draw tonnetjes */
	for(int x = 2; x < 8; x++){	//x = 0, y = 0
			int y = 0;		
			drawTon(x,y);	
	}
	for(int x = 0; x < 8; x = x+2){	//x = 1 , y = 1
		if(x != 0){
			int y = 1;		
			drawTon(x,y);}	
	}
	for(int x = 0; x < 9; x++){	//x = 2 , y = 2
			int y = 2;		
			drawTon(x,y);	
	}
	for(int x = 0; x < 8; x++){	//x = 3 , y = 3
		if(x == 0 || x == 6){
			int y = 3;		
			drawTon(x,y);}	
	}
	for(int x = 0; x < 9; x++){	//x = 4 , y = 4
		if(x != 6){
			int y = 4;		
			drawTon(x,y);}	
	}	
	for(int x = 0; x < 9; x = x+2){	//x = 5 , y = 5
			int y = 5;		
			drawTon(x,y);	
	}
	for(int x = 1; x < 9; x++){	//x = 6 , y = 6
		if(x != 2){
			int y = 6;		
			drawTon(x,y);}	
	}
	for(int x = 0; x < 9; x = x+2){	//x = 7 , y = 7
		if(x != 6 && x != 8){			
			int y = 7;		
			drawTon(x,y);}	
	}
	for(int x = 0; x < 9; x++){	//x = 8 , y = 8
		if(x != 2 && x != 7 && x != 8){
			int y = 8;		
			drawTon(x,y);}	
	}
	drawPlayer1(0, 0); // spelers
	drawPlayer2(8, 8);				
}

void drawMainMenu() {
	tft.fillScreen(MAINMENUCOLOR);
	drawTitle();
//	drawTitleBomb();
	drawStart();
	drawHighScore();
	drawQuit();
}

void drawGrid() {
        tft.fillRect(XUP /*niet op grens van scherm X */, YUP/*niet op grens van scherm Y*/, AANTALLENGTEBREEDTE*lw /*volledige game-grid*/, AANTALLENGTEBREEDTE*lw /*volledige game-grid*/, GRIDCOLOUR /*donkerbruine achtergrond*/);
        for(int x = 0; x < AANTALLENGTEBREEDTE; x++) {
                for(int y = 0; y < AANTALLENGTEBREEDTE; y++) {
                        tft.drawRect((x*lw) + XUP, (y*lw) + YUP, lw+1, lw+1, ILI9341_BLACK); //lijnen tussen grid
                }
        }
}

void drawWall(uint8_t x, uint8_t y){
	tft.fillRect(x*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET, WALL);
}

void drawHeart(uint16_t x, uint16_t y, uint16_t b, uint16_t h) {
	tft.fillTriangle((x + 0.5*b), (y + h), x, (y + 0.44*h), (x + b), (y + 0.44*h), HEARTCOLOUR); //driehoek van hartje
	tft.fillCircle((x+0.25*b), (y + 0.28*h), (0.25*b), HEARTCOLOUR); //cirkel linksboven van hartje
        tft.fillCircle((x+0.75*b), (y + 0.28*h), (0.25*b), HEARTCOLOUR); //cirkel rechtsboven van hartje
	tft.fillRect(x+3,y+2,1,1,ILI9341_WHITE);// details
	tft.fillRect(x+2,y+3,1,1,ILI9341_WHITE);
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
	/* Pants */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6.5, (y*lw) + YUP + OBJOFFSET + 10, lw - 2*OBJOFFSET - 12 , lw - 2*OBJOFFSET - 15, ILI9341_BLACK); // pant
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6.5, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // left leg
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // right leg
	/* Shoes */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 4, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 15, lw - 2*OBJOFFSET - 18, PLAYER1); // left shoe
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 15, lw - 2*OBJOFFSET - 18, PLAYER1); // right shoe	
	/* Body  */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6.5, (y*lw) + YUP + OBJOFFSET + 2, lw - 2*OBJOFFSET - 12 , lw - 2*OBJOFFSET - 10, PLAYER1); // chest 
	tft.fillRect(x*lw + XUP + OBJOFFSET + 2, (y*lw) + YUP + OBJOFFSET + 3, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 14, PLAYER1); // left arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 3, (y*lw) + YUP + OBJOFFSET + 3, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 16, PLAYER1); // left shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 2, (y*lw) + YUP + OBJOFFSET + 9, lw - 2*OBJOFFSET - 16 , lw - 2*OBJOFFSET - 16, SKIN);// left hand
	tft.fillRect(x*lw + XUP + OBJOFFSET + 15, (y*lw) + YUP + OBJOFFSET + 3, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 14, PLAYER1); // right arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 3, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 16, PLAYER1); // right shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 15, (y*lw) + YUP + OBJOFFSET + 9, lw - 2*OBJOFFSET - 16 , lw - 2*OBJOFFSET - 16, SKIN);// right hand	
	/* Head */
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) - 6 , 5, SKIN); // head
	/* Face */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET - 1, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // left eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET - 1, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // left eye white
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET - 1, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // right eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET - 1, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // right eye white
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 3, ILI9341_BLACK);// mouth
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 2, ILI9341_BLACK);
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET + 3, ILI9341_BLACK);
	/* Hat  */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6, (y*lw) + YUP + OBJOFFSET - 9, lw - 2*OBJOFFSET -9 , lw - 2*OBJOFFSET - 15, PLAYER1); // main hat
	tft.drawRect(x*lw + XUP + OBJOFFSET + 6, (y*lw) + YUP + OBJOFFSET - 9, lw - 2*OBJOFFSET -9 , lw - 2*OBJOFFSET - 15, ILI9341_BLACK);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET - 6, lw - 2*OBJOFFSET -11 , lw - 2*OBJOFFSET - 16, PLAYER1); // brim
	tft.drawRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET - 6, lw - 2*OBJOFFSET -11 , lw - 2*OBJOFFSET - 16, ILI9341_BLACK);
}

void drawPlayer2(uint8_t x, uint8_t y) {
	/* Pants */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6.5, (y*lw) + YUP + OBJOFFSET + 10, lw - 2*OBJOFFSET - 12 , lw - 2*OBJOFFSET - 15, ILI9341_BLACK); // pant
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6.5, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // left leg
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // right leg
	/* Shoes */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 4, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 15, lw - 2*OBJOFFSET - 18, PLAYER2); // left shoe
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 15, lw - 2*OBJOFFSET - 18, PLAYER2); // right shoe	
	/* Body  */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6.5, (y*lw) + YUP + OBJOFFSET + 2, lw - 2*OBJOFFSET - 12 , lw - 2*OBJOFFSET - 10, PLAYER2); // chest 
	tft.fillRect(x*lw + XUP + OBJOFFSET + 2, (y*lw) + YUP + OBJOFFSET + 3, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 14, PLAYER2); // left arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 3, (y*lw) + YUP + OBJOFFSET + 3, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 16, PLAYER2); // left shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 2, (y*lw) + YUP + OBJOFFSET + 9, lw - 2*OBJOFFSET - 16 , lw - 2*OBJOFFSET - 16, SKIN);// left hand
	tft.fillRect(x*lw + XUP + OBJOFFSET + 15, (y*lw) + YUP + OBJOFFSET + 3, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 14, PLAYER2); // right arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 3, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 16, PLAYER2); // right shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 15, (y*lw) + YUP + OBJOFFSET + 9, lw - 2*OBJOFFSET - 16 , lw - 2*OBJOFFSET - 16, SKIN);// right hand	
	/* Head */
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) - 6 , 5, SKIN); // head
	/* Face */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET - 1, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // left eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET - 1, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // left eye white
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET - 1, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // right eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET - 1, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // right eye white
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 3, ILI9341_BLACK);// mouth
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 2, ILI9341_BLACK);
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET + 3, ILI9341_BLACK);
	/* Hat  */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6, (y*lw) + YUP + OBJOFFSET - 9, lw - 2*OBJOFFSET -9 , lw - 2*OBJOFFSET - 15, PLAYER2); // main hat
	tft.drawRect(x*lw + XUP + OBJOFFSET + 6, (y*lw) + YUP + OBJOFFSET - 9, lw - 2*OBJOFFSET -9 , lw - 2*OBJOFFSET - 15, ILI9341_BLACK);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET - 6, lw - 2*OBJOFFSET -11 , lw - 2*OBJOFFSET - 16, PLAYER2); // brim
	tft.drawRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET - 6, lw - 2*OBJOFFSET -11 , lw - 2*OBJOFFSET - 16, ILI9341_BLACK);
}

void drawBomb(uint8_t x, uint8_t y) { 
	tft.fillRect(x*lw + XUP + OBJOFFSET + 9.5, (y*lw) + YUP + OBJOFFSET + 3 , lw - 2*OBJOFFSET - 18  , lw - 2*OBJOFFSET - 13, LONT2); // lontje bom	
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, ILI9341_BLACK); // lichaam bom
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , ILI9341_WHITE); // details
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , ILI9341_WHITE);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, FIRE); // fire
}

void drawBombExplosie(uint8_t x, uint8_t y){
	/* Bom tekeken */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 9.5, (y*lw) + YUP + OBJOFFSET + 3 , lw - 2*OBJOFFSET - 18  , lw - 2*OBJOFFSET - 13, LONT2); // lontje bom	
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, ILI9341_BLACK); // lichaam bom
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , ILI9341_WHITE); // details
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , ILI9341_WHITE);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, FIRE); // fire
	/* Bom tikt */	
	_delay_ms(1000);	// explosie timer
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, ILI9341_RED); // lichaam bom // explosie
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , ILI9341_WHITE); // details
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , ILI9341_WHITE);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, FIRE); // fire
	_delay_ms(1000);	// explosie timer
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, ILI9341_BLACK); // lichaam bom
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , ILI9341_WHITE); // details
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , ILI9341_WHITE);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, FIRE); // fire
	_delay_ms(650);	// explosie timer
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, ILI9341_RED); // lichaam bom // explosie
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , ILI9341_WHITE); // details
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , ILI9341_WHITE);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, FIRE); // fire
	_delay_ms(650);	// explosie timer
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, ILI9341_BLACK); // lichaam bom // explosie
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , ILI9341_WHITE); // details
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , ILI9341_WHITE);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, FIRE); // fire
	_delay_ms(350);	// explosie timer
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, ILI9341_RED); // lichaam bom // explosie
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , ILI9341_WHITE); // details
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , ILI9341_WHITE);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, FIRE); // fire
	_delay_ms(350);	// explosie timer
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, ILI9341_BLACK); // lichaam bom // explosie
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , ILI9341_WHITE); // details
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , ILI9341_WHITE);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, FIRE); // fire
	_delay_ms(350);	// explosie timer
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, ILI9341_RED); // lichaam bom // explosie
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , ILI9341_WHITE); // details
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , ILI9341_WHITE);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, FIRE); // fire
	/* bom ge-explodeerd */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 9.5, (y*lw) + YUP + OBJOFFSET + 3 , lw - 2*OBJOFFSET - 18  , lw - 2*OBJOFFSET - 13, GRIDCOLOUR); // lontje bom	
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, GRIDCOLOUR); // lichaam bom
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , GRIDCOLOUR); // details
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , GRIDCOLOUR);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, GRIDCOLOUR); // fire
	
	fireSpread(x, y);
}

void fireSpread(uint8_t x, uint8_t y) {
	if((x >= 0 && x <= 8) && (y >= 0 && y <= 8) && (!(x % 2) || !(y % 2))){			
		tft.fillRect(x*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET +1, FIRESPREAD); // vuur op bom
	}
	if((x -1 >= 0 && x -1 <= 8) && (y >= 0 && y <= 8) && (!(x - 1 % 2) || !(y % 2))){
		tft.fillRect((x-1)*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET +1, FIRESPREAD); // vuur links van bom
	}	
	if((x +1 >= 0 && x +1 <= 8) && (y >= 0 && y <= 8) && (!(x + 1 % 2) || !(y % 2))){
		tft.fillRect((x+1)*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET +1, FIRESPREAD); // vuur rechts van bom
	}	
	if((x >= 0 && x <= 8) && (y -1 >= 0 && y -1 <= 8) && (!(x % 2) || !(y - 1 % 2))){
		tft.fillRect(x*lw + XUP + OBJOFFSET, ((y-1)*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET +1, FIRESPREAD); // vuur boven van bom	
	}	
	if((x >= 0 && x <= 8) && (y +1 >= 0 && y +1 <= 8) && (!(x % 2) || !(y + 1 % 2))){
		tft.fillRect(x*lw + XUP + OBJOFFSET, ((y+1)*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET +1, FIRESPREAD); // vuur onder van bom
	}
	
	_delay_ms(700); // timer firespread
	if((x >= 0 && x <= 8) && (y >= 0 && y <= 8) && (!(x % 2) || !(y % 2))){			
		tft.fillRect(x*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET +1, GRIDCOLOUR); // vuur op bom
	}
	if((x -1 >= 0 && x -1 <= 8) && (y >= 0 && y <= 8) && (!(x - 1 % 2) || !(y % 2))){
		tft.fillRect((x-1)*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET +1, GRIDCOLOUR); // vuur links van bom
	}	
	if((x +1 >= 0 && x +1 <= 8) && (y >= 0 && y <= 8) && (!(x + 1 % 2) || !(y % 2))){
		tft.fillRect((x+1)*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET +1, GRIDCOLOUR); // vuur rechts van bom
	}	
	if((x >= 0 && x <= 8) && (y -1 >= 0 && y -1 <= 8) && (!(x % 2) || !(y - 1 % 2))){
		tft.fillRect(x*lw + XUP + OBJOFFSET, ((y-1)*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET +1, GRIDCOLOUR); // vuur boven van bom	
	}	
	if((x >= 0 && x <= 8) && (y +1 >= 0 && y +1 <= 8) && (!(x % 2) || !(y + 1 % 2))){
		tft.fillRect(x*lw + XUP + OBJOFFSET, ((y+1)*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET +1, GRIDCOLOUR); // vuur onder van bom
	}
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
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 8,   7   , TONBROWN); // lichaam ton
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 2,   7   , TONBROWN);	// lichaam ton
	tft.fillRect(x*lw + XUP + OBJOFFSET +  3, (y*lw) + YUP + OBJOFFSET + 5 , lw - 2*OBJOFFSET - 5, lw - 2*OBJOFFSET - 17, ILI9341_BLACK); // details
	tft.fillRect(x*lw + XUP + OBJOFFSET + 3 , (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 5, lw - 2*OBJOFFSET - 17, ILI9341_BLACK); // details
}

void drawTitle() {
	tft.setCursor(TITLETPOSX, TITLETPOSY); //startpositie tekst
	tft.setTextSize(TITLETSIZE); //textsize
	tft.setTextColor(BCOLOR);
	tft.print("B"); //startpositie tekst
	tft.setTextColor(OCOLOR);
	tft.print("O");
	tft.setTextColor(MCOLOR);
	tft.print("M");
	tft.setTextColor(BCOLOR);
        tft.print("B");
        tft.setTextColor(ECOLOR);
        tft.print("E");
	tft.setTextColor(RCOLOR);
        tft.print("R");
        tft.setTextColor(MCOLOR);
        tft.print("M");
	tft.setTextColor(ACOLOR);
        tft.print("A");
        tft.setTextColor(NCOLOR);
        tft.print("N");
}

void drawTitleBomb() {
	tft.fillRect(50, 50, 20, 40, LONT2); // lontje bom 
        tft.fillCircle(40, 60, 10, ILI9341_BLACK); // lichaam bom
        tft.drawPixel(43, 55, ILI9341_WHITE); // details
        tft.drawPixel(44, 56, ILI9341_WHITE);
        tft.fillRect(40, 30, 20, 10, FIRE); // fire
}

void drawStart() {
	if(mainmenuselect == 0) { //voor nunchuck
		tft.fillRect(STARTBUTRX, STARTBUTRY, STARTBUTRW, STARTBUTRH, STARTBUTSELCOLOR);
		tft.setCursor(STARTBUTSTPOSX, STARTBUTSTPOSY);
		tft.setTextColor(SHADOWCOLOR);
		tft.setTextSize(STARTBUTTSIZE);
		tft.println("START");
		tft.setCursor(STARTBUTTPOSX, STARTBUTTPOSY);
		tft.setTextColor(STSELCOLOR);
		tft.println("START");
	} else {
		tft.fillRect(STARTBUTRX, STARTBUTRY, STARTBUTRW, STARTBUTRH, STARTBUTCOLOR);
		tft.setCursor(STARTBUTTPOSX, STARTBUTTPOSY);
		tft.setTextColor(STCOLOR);
		tft.setTextSize(STARTBUTTSIZE);
		tft.println("START");
	}
	tft.drawRect(STARTBUTRX, STARTBUTRY, STARTBUTRW, STARTBUTRH, ILI9341_BLACK);
}

void drawHighScore() {
	if(mainmenuselect == 1) {//voor nunchuck
		tft.fillRect(HSBUTRX, HSBUTRY, HSBUTRW, HSBUTRH, HSBUTSELCOLOR);
		tft.setCursor(HSBUTSTPOSX, HSBUTSTPOSY);
		tft.setTextColor(SHADOWCOLOR);
		tft.setTextSize(HSBUTTSIZE);
		tft.println("HIGH-SCORES");
		tft.setCursor(HSBUTTPOSX, HSBUTTPOSY);
		tft.setTextColor(HSTSELCOLOR);
		tft.println("HIGH-SCORES");
	} else {
		tft.fillRect(HSBUTRX, HSBUTRY, HSBUTRW, HSBUTRH, HSBUTCOLOR);
		tft.setCursor(HSBUTTPOSX, HSBUTTPOSY);
		tft.setTextColor(HSTCOLOR);
		tft.setTextSize(HSBUTTSIZE);
		tft.println("HIGH-SCORES");
	}
	tft.drawRect(HSBUTRX, HSBUTRY, HSBUTRW, HSBUTRH, ILI9341_BLACK);
}

void drawQuit() {
	if(mainmenuselect == 2) {//voor nunchuck
		tft.fillRect(QUITBUTRX, QUITBUTRY, QUITBUTRW, QUITBUTRH, QUITBUTSELCOLOR);
		tft.setCursor(QUITBUTSTPOSX, QUITBUTSTPOSY);
		tft.setTextColor(SHADOWCOLOR);
		tft.setTextSize(QUITBUTTSIZE);
		tft.println("QUIT");
		tft.setCursor(QUITBUTTPOSX, QUITBUTTPOSY);
		tft.setTextColor(QUITTSELCOLOR);
		tft.println("QUIT");
	} else {
		tft.fillRect(QUITBUTRX, QUITBUTRY, QUITBUTRW, QUITBUTRH, QUITBUTCOLOR);
		tft.setCursor(QUITBUTTPOSX, QUITBUTTPOSY);
		tft.setTextColor(QUITTCOLOR);
		tft.setTextSize(QUITBUTTSIZE);
		tft.println("QUIT");
	}
	tft.drawRect(QUITBUTRX, QUITBUTRY, QUITBUTRW, QUITBUTRH, ILI9341_BLACK);
}


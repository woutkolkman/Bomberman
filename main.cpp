// defines
#define ADDRESS 0x52
#define GAMETICK_FREQUENCY 0.3 // gameticks in HZ, max 0,119HZ, min 7812,5HZ
#define FCLK 16000000 // arduino clock frequency
#define PRESCALER_TIMER1 1024 // prescaler, zie ook functie timer1_init()
#define OFFSET_VAKJE 24 // breedte & hoogte van een vakje
#define OFFSET_PLAYER_X 12 // offset waarop player in vakje zit X
#define OFFSET_PLAYER_Y 20 // offset waarop player in vakje zit Y
#define BAUD 9600
#define TFT_DC 9 // initialisatie LCD
#define TFT_CS 10 // initialisatie LCD
#define AANTALLENGTEBREEDTE 9 //aantal hokjes in lengte en breedte
#define LIGHTBROWN 0x7A00
#define DARKBROWN 0x5980
#define XUP 10
#define YUP 50
#define OBJOFFSET 2
#define MAXOBJ 8
#define BORDERLEFTSIDE 0
#define BORDERRIGHTSIDE 8
#define BORDERUP 8
#define BORDERDOWN 0

// includes
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <Adafruit_ILI9341.h> // LCD library
#include <Adafruit_GFX.h>// LCD library
#include <Arduino.h> // LCD library
#include <SPI.h>
#include <Wire.h>
#include <Nunchuk.h>

// global variables
volatile uint8_t brightness = 0;
volatile unsigned int counter = 0;
volatile uint8_t lw = 220 / AANTALLENGTEBREEDTE; // BREEDTE VAN EEN VAKJE!!
volatile uint8_t player1_x = 0;
volatile uint8_t player1_y = 0;
volatile uint8_t player2_x = 0;
volatile uint8_t player2_y = 0;
volatile uint8_t currentPosition;

// use hardware SPI (on Uno, #13, #12, #11) and #10 and #9 for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// function prototypes
void nunchuk_init();
void moveCharacterRight(uint8_t y_position);
void moveCharacterLeft(uint8_t y_position);
void moveCharacter(void);
void drawGrid();
void drawHeartLeft();
void drawHeartRight();
void clearDrawPlayer1(uint8_t x, uint8_t y);
void drawPlayer1(uint8_t x, uint8_t y);
void drawPlayer2(uint8_t x, uint8_t y);
void drawBomb(uint8_t x, uint8_t y);
void drawTon(uint8_t x, uint8_t y);
void adc_init(void);
void init(void);
void timer0_init(void);
void timer1_init(void);
void adc_init(void);
void game_init(void);
void screen_init(void);
void draw_screen(void);


/* ISR */
ISR(ADC_vect) { // wordt aangeroepen wanneer ADC conversie klaar is
	brightness = (ADC>>2); // 10 bits, gooi 2 LSB weg, uitkomst 8 bits

	// brightness toepassen op beeldscherm
}


ISR(TIMER1_COMPA_vect) { // gameticks
	moveCharacter();
	draw_screen();
}


int main(void) {
	/* setup */
	game_init();

	/* loop */
	for(;;) {
     		Nunchuk.getState(ADDRESS); // retrieve states joystick and buttons Nunchuk

//		// code to move block over x axis and y axis (on sides)
//		moveCharacterRight(4);
		moveCharacter();
        	draw_screen();
		_delay_ms(10);
	}

	/* never reached */
	return 0;
}

// globale initialisatie functie (ter vervanging van "init")
void game_init(void) {
	init(); // onzichtbare functie
	timer0_init();
	timer1_init();
	screen_init();
	Wire.begin(); // enable TWI communication
	nunchuk_init(); // start communication between Nunchuk and Arduino

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

	// enable global interrupts
	sei();
}

void screen_init(void) {
	DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5); // TFT scherm

	tft.begin(); // enable SPI communication
	tft.setRotation(2); // rotate screen

	// screen is 240 x 320
        tft.fillScreen(LIGHTBROWN);

//        drawHeartLeft();
//        drawHeartRight();
//        drawGrid();
//        drawPlayer1(8, 0);
//        drawPlayer2(0, 8);
//        drawBomb(4, 2);
//        moveCharacter();
//        drawPlayer1(player1_y, player1_x);
}

void draw_screen(void) {
	// screen is 240 x 320
//        tft.fillScreen(LIGHTBROWN);

        drawHeartLeft();
        drawHeartRight();
//	tft.fillRect(XUP, YUP, AANTALLENGTEBREEDTE * lw, AANTALLENGTEBREEDTE * lw, DARKBROWN);
        drawGrid();
//      drawPlayer1(8, 0);
//      drawPlayer2(0, 8);
        drawBomb(4, 2);
	drawPlayer1(player1_y, player1_x);
}

void nunchuk_init() {
	DDRC &= ~(1 << DDC4) & ~(1 << DDC5); // Nunchuk
	Nunchuk.begin(ADDRESS); // start communication with Arduino and Nunchuk
}

void moveCharacter() {
	if (Nunchuk.X_Axis() == 255) {
		if (player1_x < BORDERRIGHTSIDE) {
//			clearDrawPlayer1();
			player1_x++;
		}
	}
	if (Nunchuk.X_Axis() == 0) {
		if (player1_x > BORDERLEFTSIDE) {
//			clearDrawPlayer1();
			player1_x--;
		}
	}
	if (Nunchuk.Y_Axis() == 255) {
                if (player1_y < BORDERUP) {
//			clearDrawPlayer1();
                        player1_y++;
                }
        }
        if (Nunchuk.Y_Axis() == 0) {
                if (player1_y > BORDERDOWN) {
//			clearDrawPlayer1();
                        player1_y--;
                }
        }
}

void drawGrid() {
        tft.fillRect(XUP, YUP, AANTALLENGTEBREEDTE * lw, AANTALLENGTEBREEDTE * lw, DARKBROWN);
        for (int x = 0; x < 9; x++) {
                for (int y = 0; y < 9; y++) {
                        tft.drawRect((x * lw) + XUP, (y * lw) + YUP, lw + 1, lw + 1, ILI9341_BLACK);
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

void clearDrawPlayer1() {
	uint8_t x = player1_x;
	uint8_t y = player1_y;

//        tft.fillRect((x * lw) + XUP + OBJOFFSET, (y * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, DARKBROWN);
//	tft.fillRect(x,y,DARKBROWN);
}

void drawPlayer1(uint8_t x, uint8_t y) {
	tft.fillRect(x * lw + XUP + OBJOFFSET, (y * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_CYAN);
}

void drawPlayer2(uint8_t x, uint8_t y) {
	tft.fillRect(x * lw + XUP + OBJOFFSET, (y * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_RED);
}

void drawBomb(uint8_t x, uint8_t y) {
	tft.fillCircle(x * lw + XUP + (0.3 * lw), y * lw + YUP + (0.3 * lw), 5, ILI9341_BLACK);
}

void drawTon(uint8_t x, uint8_t y) {
	
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

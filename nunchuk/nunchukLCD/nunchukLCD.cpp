// defines
#define ADDRESS 0x52
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

// includes
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <Adafruit_ILI9341.h> // LCD library
#include <Adafruit_GFX.h>// LCD library
#include <Arduino.h> // LCD library
#include <avr/io.h> // LCD library
#include <SPI.h>
#include <Wire.h>
#include <Nunchuk.h>

// global variables
volatile uint8_t brightness = 0;
uint8_t lw = 220 / AANTALLENGTEBREEDTE;

// use hardware SPI (on Uno, #13, #12, #11) and #10 and #9 for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// function prototypes
void nunchuk_init();
void drawGrid();
void drawHeartLeft();
void drawHeartRight();
void drawPlayer1(uint8_t x, uint8_t y);
void drawPlayer2(uint8_t x, uint8_t y);
void drawBomb(uint8_t x, uint8_t y);
void drawTon(uint8_t x, uint8_t y);

int main(void) {

  // input & output
  DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5); // TFT scherm
  DDRC |= (1 << DDC4) | (1 << DDC5); // Nunchuk

  // initializiations
  init();
  tft.begin(); // enable SPI communication
  Wire.begin(); // enable TWI communication
  nunchuk_init(); // start communication between Nunchuk and Arduino

  // enable global interrupts
  sei();
  
  //scherm is 240 * 320 pixels
  tft.fillScreen(LIGHTBROWN);

  drawHeartLeft();
  drawHeartRight();
  drawGrid();
  drawPlayer1(8, 0);
  drawPlayer2(0, 8);
  drawBomb(4, 2);

	
   for(;;){

     Nunchuk.getState(ADDRESS); // retrieve states joystick and buttons Nunchuk

     
		
   }


	
   return 0;
}

void nunchuk_init() {
   
    Nunchuk.begin(ADDRESS); // start communication with Arduino and Nunchuk
}

void drawGrid() {
        tft.fillRect(XUP, YUP, AANTALLENGTEBREEDTE * lw, AANTALLENGTEBREEDTE * lw, DARKBROWN);
        for(int x = 0; x < 9; x++) {
                for(int y = 0; y < 9; y++) {
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

/* defines */
#define BAUD 9600
#define TFT_DC 9 // initialisatie LCD
#define TFT_CS 10 // initialisatie LCD

/* includes */
#include <Adafruit_ILI9341.h> // LCD library
#include <Adafruit_GFX.h>// LCD library
#include <SPI.h>
#include <Arduino.h>
#include <avr/io.h>
//#include <usart.h>

/* Use Hardware SPI (on Uno, #13, #12, #11) and #10 and # 9for  CS/DC   */
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

//int main(void) {}
/* setup */
void setup(){
  //USART_Init();
  //USART_Transmit(0x76);
  DDRB |= (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5); // TFT scherm
  //USART_Transmit(0x76);
  Serial.begin(9600);
  tft.begin();
  /* achtergrond kleuren  */
  tft.fillScreen(ILI9341_GREEN);
  /* pixel tekenen op y en x as */
  tft.drawPixel(90, 30, ILI9341_RED);
  tft.drawPixel(90, 31, ILI9341_RED);
  tft.drawPixel(91, 30, ILI9341_RED);
  tft.drawPixel(91, 31, ILI9341_RED);
}

/* loop */
void loop(){
	/* max resolutie is 240x320  */
	for(int y=-150; y<320; y++){ // loop for het bepalen van de y as
		tft.drawFastVLine(129, y, 120, ILI9341_RED); // tekenen pixels, teken 60 pixels op x-as: 128, y-as: y
		tft.drawFastVLine(128, y, 120, ILI9341_RED);
		tft.drawFastVLine(127, y, 120, ILI9341_RED);
		tft.drawFastVLine(126, y, 120, ILI9341_RED);

		delay(5); // snelheid van het bewegen van de lijn, hoger getal is lagere snelheid
		tft.drawFastVLine(129, y, 120, ILI9341_GREEN); // teken de 60 eerder getekende pixels weer de kleur van de achtergrond
		tft.drawFastVLine(128, y, 120, ILI9341_GREEN);
		tft.drawFastVLine(127, y, 120, ILI9341_GREEN);
		tft.drawFastVLine(126, y, 120, ILI9341_GREEN);;

	}
}

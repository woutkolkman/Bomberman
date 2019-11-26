/* defines */
#define BAUD 9600
#define TFT_DC 9 // initialisatie LCD
#define TFT_CS 10 // initialisatie LCD

// Color definitions
#define ILI9341_BLACK       0x0000  ///<   0,   0,   0
#define ILI9341_NAVY        0x000F  ///<   0,   0, 123
#define ILI9341_DARKGREEN   0x03E0  ///<   0, 125,   0
#define ILI9341_DARKCYAN    0x03EF  ///<   0, 125, 123
#define ILI9341_MAROON      0x7800  ///< 123,   0,   0
#define ILI9341_PURPLE      0x780F  ///< 123,   0, 123
#define ILI9341_OLIVE       0x7BE0  ///< 123, 125,   0
#define ILI9341_LIGHTGREY   0xC618  ///< 198, 195, 198
#define ILI9341_DARKGREY    0x7BEF  ///< 123, 125, 123
#define ILI9341_BLUE        0x001F  ///<   0,   0, 255
#define ILI9341_GREEN       0x07E0  ///<   0, 255,   0
#define ILI9341_CYAN        0x07FF  ///<   0, 255, 255
#define ILI9341_RED         0xF800  ///< 255,   0,   0
#define ILI9341_MAGENTA     0xF81F  ///< 255,   0, 255
#define ILI9341_YELLOW      0xFFE0  ///< 255, 255,   0
#define ILI9341_WHITE       0xFFFF  ///< 255, 255, 255
#define ILI9341_ORANGE      0xFD20  ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define ILI9341_PINK        0xFC18  ///< 255, 130, 198

#define Backgroundcolor ILI9341_YELLOW

/* includes */
#include <Adafruit_ILI9341.h> // LCD library
#include <Adafruit_GFX.h>// LCD library
#include <SPI.h>
#include <Arduino.h>
#include <avr/io.h>
//#include <usart.h>

/* Use Hardware SPI (on Uno, #13, #12, #11) and #10 and # 9for  CS/DC   */
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void tekenen_Lijn(){	
/* max resolutie is 240x320  */
	for(int y=-150; y<320; y++){ // loop for het bepalen van de y as
		tft.drawFastVLine(129, y, 120, ILI9341_RED); // tekenen pixels, teken 60 pixels op x-as: 128, y-as: y
		tft.drawFastVLine(128, y, 120, ILI9341_RED);
		tft.drawFastVLine(127, y, 120, ILI9341_RED);
		tft.drawFastVLine(126, y, 120, ILI9341_RED);

		delay(5); // snelheid van het bewegen van de lijn, hoger getal is lagere snelheid
		tft.drawFastVLine(129, y, 120, Backgroundcolor); // teken de 60 eerder getekende pixels weer de kleur van de achtergrond
		tft.drawFastVLine(128, y, 120, Backgroundcolor);
		tft.drawFastVLine(127, y, 120, Backgroundcolor);
		tft.drawFastVLine(126, y, 120, Backgroundcolor);
	}
}

void mannetje_tekenen(){
	tft.drawFastVLine(128, 100, 120, ILI9341_RED); // 1,1
	tft.drawFastVLine(128, 100, 120, ILI9341_RED);
	tft.drawFastVLine(128, 100, 120, ILI9341_RED);
	tft.drawFastVLine(128, 100, 120, ILI9341_RED); //1.4

	tft.drawFastVLine(128, 100, 120, ILI9341_RED); //2,2
	tft.drawFastVLine(128, 100, 120, ILI9341_RED);
	tft.drawFastVLine(128, 100, 120, ILI9341_RED);//2.4

}

/* setup */
void setup(){
  //USART_Init();
  //USART_Transmit(0x76);
  DDRB |= (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5); // TFT scherm
  //USART_Transmit(0x76);
  Serial.begin(9600);
  tft.begin();
  /* achtergrond kleuren  */
  //tft.fillScreen(ILI9341_GREEN);
  tft.fillScreen(Backgroundcolor);
  /* pixel tekenen op y en x as */
  //tft.drawPixel(90, 30, ILI9341_RED);
  //tft.drawPixel(90, 31, ILI9341_RED);
  //tft.drawPixel(91, 30, ILI9341_RED);
  //tft.drawPixel(91, 31, ILI9341_RED);
}

/* loop */
void loop(){
	//tekenen_Lijn();
	mannetje_tekenen();
}

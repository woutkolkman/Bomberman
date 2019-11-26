/* defines */
//#define BAUD 9600
#define TFT_DC 9 // initialisatie LCD
#define TFT_CS 10 // initialisatie LCD

/* includes */
#include <Adafruit_ILI9341.h> // LCD library
#include <Adafruit_GFX.h>// LCD library
#include <SPI.h>
#include <Arduino.h>

/* Use Hardware SPI (on Uno, #13, #12, #11) and #10 and # 9for  CS/DC   */
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int main(void) {
	/* setup */
	DDRB |= (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5); // TFT scherm
	//sei(); // set global interrupt flag

	Serial.begin(9600);
	tft.begin();
	tft.fillScreen(ILI9341_RED);

	/* loop */

	/* never reached */
	return 0;
}

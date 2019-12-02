#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include <Arduino.h>
#include <Nunchuk.h>
#include <util/delay.h>
#include <Adafruit_ILI9341.h> // LCD library
#include <Adafruit_GFX.h>// LCD library
#include <SPI.h>

#define ADDRESS 0x52

#define BAUD 9600
#define TFT_DC 9 
#define TFT_CS 10

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
#define backgroundColour ILI9341_ORANGE

#define standardPosition tft.fillRect(100, 140, 35, 45, ILI9341_BLACK);
<<<<<<< HEAD
#define clearStandardPosition tft.fillRect(100, 140, 35, 45, backgroundColour);
=======
>>>>>>> nunchuck
#define clearUp tft.fillRect(100 + y, 140, 35 , 45, backgroundColour);
#define clearDown tft.fillRect(100 - y, 140, 35, 45, backgroundColour);
#define clearLeft tft.fillRect(100, 140 - x, 35, 45, backgroundColour);
#define clearRight tft.fillRect(100, 140 + x, 35, 45, backgroundColour);

#define y 50
#define x 50

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {

  DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5); // TFT scherm

  PCICR |= (1 << PCIE1); // enable interrupt on C Port
  PCMSK1 |= (1 << PCINT12); // enable interrupt on I/O pin
  sei(); // enable interrupts

  Serial.begin(9600);
  Wire.begin(); // allow I2C communication
  tft.begin(); // allow SPI communication

  tft.fillScreen(backgroundColour); // background

  // nunchuk
  init();

  Nunchuk.begin(ADDRESS); // start communication with Arduino and Nunchuk
  
  Serial.print("ID: 0x"); // retrieve ID Nunchuk and display
  for (uint8_t i = 0; i < FRAMELEN; i++) {
     Serial.print(Nunchuk.id[i], HEX);
  }
  Serial.println("");

  _delay_ms(500);
}

void moveUp() {

   tft.fillRect(100 + y, 140, 35 , 45, ILI9341_BLACK);
}

void moveRight() {

   tft.fillRect(100, 140 + x, 35, 45, ILI9341_BLACK);
}

void moveLeft() {
   
   tft.fillRect(100, 140 - x, 35, 45, ILI9341_BLACK);
}

void moveDown() {
 
   tft.fillRect(100 - y, 140, 35, 45, ILI9341_BLACK);
}  

ISR(PCINT1_vect) {

   
}

void loop() {

  Nunchuk.getState(ADDRESS); // retrieve states (defined in .h and .cpp)

  /* X-axis: left: 0 - middle: 127 - right: 255
     Y-axis: up: 255 - middle: 128 - down: 0
     Z-button: released: 0 - pressed: 1
     C-button: released: 0 - pressed: 1 */

<<<<<<< HEAD
     if (Nunchuk.X_Axis() == 255) { // right
       clearLeft; clearUp; clearDown;
       moveRight();
     } else if (Nunchuk.X_Axis() == 0) { // left
        clearRight; clearUp; clearDown;
        moveLeft();
     } else if (Nunchuk.Y_Axis() == 255) { // up
        clearLeft; clearRight; clearDown;
        moveUp();
     } else if (Nunchuk.Y_Axis() == 0) { // down
        clearLeft; clearRight; clearUp;
        moveDown();
     }
=======
     if (Nunchuk.Y_Axis() == 128 && Nunchuk.X_Axis() == 127) {
	standardPosition;
     }
     
     // Y-axis
     if (Nunchuk.Y_Axis() == 255) {
        moveUp();
        } else if (Nunchuk.Y_Axis() == 0) {
           moveDown();
        } else {
           clearUp;
           clearDown;
        }

     // X-axis 
     if (Nunchuk.X_Axis() == 0) {
         moveLeft();
     	} else if (Nunchuk.X_Axis() == 255) {
	    moveRight();
        } else {
            clearLeft;	
            clearRight;
        }

>>>>>>> nunchuck
}
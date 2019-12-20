// Defines
#define BAUD 9600 				// baudrate USART
#define AANTALLENGTEBREEDTE WIDTH_MAP 		// aantal hokjes in lengte en breedte
#define DEFAULT_PLAYER_HEALTH 3
#define WIDTH_MAP (BORDERRIGHTSIDE + 1)
#define EMPTY_TILE 9            		// locatie in array is leeg, >0
#define BORDERRIGHTSIDE 8 			// main x
#define BORDERLEFTSIDE 0 			// min X
#define TFT_DC 9 				// initialisatie LCD
#define TFT_CS 10 				// initialisatie LCD

// win/lose messages
#define POSITIONX 109				// message posititon schaduw tekst x
#define POSITIONY 115				// message posititon schaduw tekst y
#define POSITIONX2 POSITIONX + 2		// message position tekst x
#define POSITIONY2 POSITIONY - 2		// message position tekst y
#define POSITIONRX 75				// message rechtangle position x
#define POSITIONRY 83				// message rechtangle position y
#define POSITIONRW 167		 		// message rechtangle width
#define POSITIONRH 72				// message rechtangle heigth
#define YOULOSEMESSAGE ILI9341_RED
#define YOUWINMESSAGE 0x5623
#define YOUWINSHADOW 0x52A9
#define POSITION 120

// defines - colors
#define WALL 0X6B8E 		// kleur voor de muren
#define PLAYER1 0x135F		// kleuren van de spelers
#define PLAYER2 0xD9E7
#define SKIN 0xF5D0
#define HEARTCOLOUR ILI9341_RED	// kleur voor hartjes
#define GRIDCOLOUR DARKBROWN    // kleur van de gridachtergrond
#define LONT2 0xDC29 		// kleur van de lont van de bom
#define FIRE 0xF9E1 		// kleur van het vuur van de bom
#define TONBROWN 0x28A0		// kleur van de tonnen
#define LIGHTBROWN 0x7A00 			// voor tekenen kleur
#define DARKBROWN 0x5980 			// voor tekenen kleur
#define XUP 50 	// 10				// voor tekenen
#define YUP 10 	// 50				// voor tekenen
#define OBJOFFSET 2 				// voor tekenen

// defines - menu's
#define MAINMENUCOLOR 0x016E // kleur van main menu
#define TITLECOLOUR 0xA841 // kleur van het blokje om de titel van het main menu
#define ACOLOR ILI9341_PURPLE
#define BCOLOR 0xFE20
#define TITLETSIZE 4 // text size
#define TITLETPOSX 50 // text positie x as
#define TITLETPOSY 12 // text positie y as
#define SHADOWBCOLOR 0xBA81 // shaduw kleur voor de titel van start menu
#define BCOLOR 0xFE20 // kleur van Titel tekst main menu
#define LONT2 0xDC29 // kleur van de lont van de bom
#define FIRE 0xF9E1 // kleur van vuur van de bom
#define SELECTEDTEXTCOLOR ILI9341_GREEN
#define SHADOWCOLOR ILI9341_LIGHTGREY // shaduw kleur letters

// defines - startbutton
#define STARTBUTRX 50 //start button rectangle position x
#define STARTBUTRY 50 //start button rectangle position y
#define STARTBUTRW 220 //start button rectangle width
#define STARTBUTRH 40 //start button rectangle height
#define STARTBUTTPOSX 125 //start button text position x
#define STARTBUTTPOSY 65 //start button text position y
#define STARTBUTTSIZE 2 //start button text size
#define STARTBUTSTPOSX STARTBUTTPOSX + 2
#define STARTBUTSTPOSY STARTBUTTPOSY - 2

// defines - buttoncolor
#define TEXTCOLOR ILI9341_BLACK
#define STARTBUTCOLOR 0x0575
#define STARTBUTSELCOLOR 0xAFFF
#define CONTINEBUTCOLOR 0x1380
#define CONTINEBUTSELBUTCOLOR 0x2600
#define HSBUTCOLOR 0x0500
#define HSBUTSELCOLOR 0x87F0
#define QUITBUTCOLOR 0xC800
#define QUITBUTSELCOLOR 0xFAAA

// defines - continue
#define CONTBUTTPOSX STARTBUTTPOSX - 10
#define CONTBUTSTPOSX STARTBUTSTPOSX - 10

// defines - High score button
#define HSBUTRX 50
#define HSBUTRY 100
#define HSBUTRW 220
#define HSBUTRH 40
#define HSBUTTPOSX 95
#define HSBUTTPOSY 115
#define HSBUTTSIZE 2
#define HSBUTSTPOSX HSBUTTPOSX + 2
#define HSBUTSTPOSY HSBUTTPOSY - 2

// defines - High score lis defines
#define HSFIELDX 30
#define HSFIELDY 45
#define HSFIELDW 260
#define HSFIELDH 150

// defines - Quit button defines
#define QUITBUTRX 50
#define QUITBUTRY 150
#define QUITBUTRW 220
#define QUITBUTRH 40
#define QUITBUTTPOSX 128
#define QUITBUTTPOSY 165
#define QUITBUTTSIZE 2
#define QUITBUTSTPOSX QUITBUTTPOSX + 2
#define QUITBUTSTPOSY QUITBUTTPOSY - 2

// defines - Back button defines
#define BACKBUTRX 120
#define BACKBUTRY 200
#define BACKBUTRW 80
#define BACKBUTRH 30
#define BACKSTPOSX BACKTPOSX + 2
#define BACKSTPOSY BACKTPOSY - 2
#define BACKBUTTSIZE 2
#define BACKTPOSX 135
#define BACKTPOSY 210

// defines - meer menu's kleuren
#define PAUSEMENUCOLOR 0xFD60
#define FIRESPREAD ILI9341_RED
#define GOLD 0xFE00
#define SILVER 0x94B2
#define BRONZE 0xB406
#define HIGHSCORESBACK 0x1B02 // achtergrond kleur van de tekst in highscores menu
#define HIGHSCORESTEXT 0xFAA0 // tekst kleur titel highscores menu
#define SHADOWHCOLOR 0xB222   // shaduw kleur voor de titel van highscores menu
#define PAUZEBACK 0xD300//  achtergrond kleur van de tekst in pauze menu
#define SHADOWPCOLOR 0x500F   // shaduw kleur voor de titel van pauze menu
#define PAUZETEXT 0xBABE// tekst kleur titel highscores menu
#define BACKBUTROOD 0xF165 //kleur backbutton color

// defines - animations
#define BOMB_FRAMES 2				// aantal frames van de animatie, handmatig toevoegen bij drawBomb(), >0, waarde begint bij 1
#define FIRE_FRAMES 2				// aantal frames van de animatie, handmatig toevoegen bij drawFire(), >0, waarde begint bij 1


// Includes
#include <stdint.h>
#include <Adafruit_ILI9341.h> // LCD library
#include <Adafruit_GFX.h>// LCD library
/*#include "libraries/IR/ir.h" // IR library
#include <util/setbaud.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <Arduino.h> // LCD library
#include <SPI.h>
#include <Wire.h>
#include <Nunchuk.h>
#include <usart.h>

*/

// global variables
volatile uint8_t mainmenuselect = 0; // mainmenuselect goes from 0 - 1 - 2
volatile char pausemenuselect = 0;
volatile uint32_t highscore1 = 68420;
volatile uint32_t highscore2 = 3140;
volatile uint32_t highscore3 = 220;
volatile uint32_t highscore4 = 10;
volatile uint32_t highscore5 = 0;
volatile uint8_t lw = 220 / AANTALLENGTEBREEDTE; // TEKENEN VAN BREEDTE VAN EEN VAKJE
volatile uint8_t livesleft1 = DEFAULT_PLAYER_HEALTH;
volatile uint8_t livesleft2 = DEFAULT_PLAYER_HEALTH;


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


// function prototypes
uint8_t coords_to_tile(uint8_t x, uint8_t y);
void displayLoseMessage();
void displayWinMessage();
void clear_tile(uint8_t tile);
void drawGrid();
void drawHeart(uint16_t x, uint16_t y, uint16_t b, uint16_t h);
void drawPlayer1Field();
void drawPlayer2Field();
void clearDraw(uint8_t x, uint8_t y);
void drawPlayer1(uint8_t x, uint8_t y);
void drawPlayer2(uint8_t x, uint8_t y);
void drawBomb(uint8_t x, uint8_t y);
void drawFire(uint8_t x, uint8_t y);
void drawWall(uint8_t x, uint8_t y);
void drawTon(uint8_t x, uint8_t y);
void drawMainMenu();
void drawTitle();
void drawTitleBomb();
void drawPauseMenu();
void drawHighScores();
void drawHighScoreboard();
void drawHighScoreButton();
void drawStartButton();
void drawQuitButton();
void drawContinueButton();
void drawBackButton();
void drawBomb2(uint16_t x, uint8_t y);
void drawTitleBackground();
uint8_t tile_to_coords_x(uint8_t tile);
//extern uint8_t tile_array[];


// Functies
// einde game berichten
void displayLoseMessage() {
		tft.fillRect(POSITIONRX, POSITIONRY, POSITIONRW, POSITIONRH, ILI9341_BLACK); // blokje om tekst
		tft.setCursor(POSITIONX, POSITIONY); // selecteerd de positie voor de schaduw tekst
		tft.setTextColor(SHADOWCOLOR); // selecteerd de shaduwkleur voor de tekst
		tft.setTextSize(HSBUTTSIZE); // selecteerd de tekst grootte
		tft.println("YOU LOSE"); // print de tekst
		tft.setCursor(POSITIONX2, POSITIONY2); // selecteerd een nieuwe positie voor de tekst
		tft.setTextColor(YOULOSEMESSAGE); // selecteerd de tekst kleur
		tft.println("YOU LOSE"); // print de tekst
}


void displayWinMessage() {
		tft.fillRect(POSITIONRX, POSITIONRY, POSITIONRW, POSITIONRH, ILI9341_BLACK); // blokje om tekst
		tft.setCursor(POSITIONX, POSITIONY); // selecteerd de positie voor de schaduw tekst
		tft.setTextColor(YOUWINSHADOW); // selecteerd de shaduwkleur voor de tekst
		tft.setTextSize(HSBUTTSIZE); // selecteerd de tekst grootte
		tft.println("YOU WIN"); // print de tekst
		tft.setCursor(POSITIONX2, POSITIONY2); // selecteerd een nieuwe positie voor de tekst
		tft.setTextColor(YOUWINMESSAGE); // selecteerd de tekst kleur
		tft.println("YOU WIN"); // print de tekst
}


// tekenen van game map
void drawGrid() {
        tft.fillRect(XUP /*niet op grens van scherm X */, YUP/*niet op grens van scherm Y*/, AANTALLENGTEBREEDTE*lw /*volledige game-grid*/, AANTALLENGTEBREEDTE*lw /*volledige game-grid*/, GRIDCOLOUR /*donkerbruine achtergrond*/);
        for (int x = 0; x < 9; x++) {
                for (int y = 0; y < 9; y++) {
                        tft.drawRect((x * lw) + XUP, (y * lw) + YUP, lw + 1, lw + 1, ILI9341_BLACK);
                }
        }
}


// tekenen levens van players
void drawHeart(uint16_t x, uint16_t y, uint16_t b, uint16_t h) { // tekent hartjes voor de spelers
	tft.fillTriangle((x + 0.5*b), (y + h), x, (y + 0.44*h), (x + b), (y + 0.44*h), HEARTCOLOUR); //driehoek van hartje
	tft.fillCircle((x+0.25*b), (y + 0.28*h), (0.25*b), HEARTCOLOUR); //cirkel linksboven van hartje
        tft.fillCircle((x+0.75*b), (y + 0.28*h), (0.25*b), HEARTCOLOUR); //cirkel rechtsboven van hartje
	tft.fillRect(x+3,y+2,1,1,ILI9341_WHITE);// details
	tft.fillRect(x+2,y+3,1,1,ILI9341_WHITE);
}


void drawPlayer1Field() { // tekent de hartjes op de jusite plek en haalt ze weg
	tft.fillRect(10, 15, 30, 70, ILI9341_BLACK);
	if(livesleft1 == 1) {
		drawHeart(15, 20, 20, 18);//teken hartje
	}if(livesleft1 == 2) {
		drawHeart(15, 20, 20, 18);//teken hartje
		drawHeart(15, 40, 20, 18); //als 2 levens, teken 2e hartje
	}if(livesleft1 == 3) {
		drawHeart(15, 20, 20, 18);//teken hartje
		drawHeart(15, 40, 20, 18); //als 2 levens, teken 2e hartje
		drawHeart(15, 60, 20, 18); //als 3 levens, teken 3e hartje
	}
}


void drawPlayer2Field() { // player 2
	tft.fillRect(280, 155, 30, 70, ILI9341_BLACK);
	if(livesleft2 == 1) {
		drawHeart(285, 200, 20, 18); //teken hartje
	}if(livesleft2 == 2) {
		drawHeart(285, 200, 20, 18); //teken hartje
		drawHeart(285, 180, 20, 18); //als 2 levens, teken 2e hartje
	}if(livesleft2 == 3) {
		drawHeart(285, 200, 20, 18); //teken hartje
		drawHeart(285, 180, 20, 18); //als 2 levens, teken 2e hartje
		drawHeart(285, 160, 20, 18); //als 3 levens, teken 3e hartje
	}
}


// vervang getekende vakje met een leeg vakje
void clearDraw(uint8_t x, uint8_t y) {
//	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
	uint8_t switch_value = x;
	x = y;
	y = switch_value;
//	tft.fillRect((x * lw) + XUP + OBJOFFSET, (y * lw) + YUP + OBJOFFSET - 1, lw - 2 * OBJOFFSET + 2, lw - 2 * OBJOFFSET + 3, DARKBROWN);
	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET - 1, lw - 2 * OBJOFFSET + 2, lw - 2 * OBJOFFSET + 3, DARKBROWN);
}


// voor tekenen player 1
void drawPlayer1(uint8_t x, uint8_t y) {
//	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
//	x = BORDERDOWN - x; // snelle fix omdraaien y-as
//	uint8_t switch_value = x;
//	x = y;
//	y = switch_value;

	// mannetje
	// Pants
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6.5, (y*lw) + YUP + OBJOFFSET + 10, lw - 2*OBJOFFSET - 12 , lw - 2*OBJOFFSET - 20 , ILI9341_BLACK); // pant
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // left leg
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // right leg
	// Shoes
	tft.fillRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 16, lw - 2*OBJOFFSET - 18, PLAYER1); // left shoe
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 16, lw - 2*OBJOFFSET - 18, PLAYER1); // right shoe	
	// Body
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7.5, (y*lw) + YUP + OBJOFFSET + 6, lw - 2*OBJOFFSET - 14 , lw - 2*OBJOFFSET - 12, PLAYER1); // chest 
	tft.fillRect(x*lw + XUP + OBJOFFSET + 3, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 18 , lw - 2*OBJOFFSET - 14, PLAYER1); // left arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 4, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, PLAYER1); // left shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 2, (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, SKIN);// left hand
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 18 , lw - 2*OBJOFFSET - 14, PLAYER1); // right arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 13, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, PLAYER1); // right shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, SKIN);// right hand	
	// Head
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) - 1 , 5, SKIN); // head
	// Face
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // left eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // left eye white
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // right eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // right eye white
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 8, ILI9341_BLACK);// mouth
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 7, ILI9341_BLACK);
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET + 8, ILI9341_BLACK);
	// Hat
	tft.fillRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET - 2, lw - 2*OBJOFFSET -10 , lw - 2*OBJOFFSET - 16, PLAYER1); // main hat
	tft.drawRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET - 2, lw - 2*OBJOFFSET -10 , lw - 2*OBJOFFSET - 16, ILI9341_BLACK);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET , lw - 2*OBJOFFSET -12 , lw - 2*OBJOFFSET - 17, PLAYER1); // brim
	tft.drawRect(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET , lw - 2*OBJOFFSET -12 , lw - 2*OBJOFFSET - 17, ILI9341_BLACK);
}


// voor tekenen player 2
void drawPlayer2(uint8_t x, uint8_t y) {
//	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
//	x = BORDERDOWN - x; // snelle fix omdraaien y-as
//	uint8_t switch_value = x;
//	x = y;
//	y = switch_value;

	// mannetje
	// Pants
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6.5, (y*lw) + YUP + OBJOFFSET + 10, lw - 2*OBJOFFSET - 12 , lw - 2*OBJOFFSET - 20 , ILI9341_BLACK); // pant
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // left leg
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // right leg
	// Shoes
	tft.fillRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 16, lw - 2*OBJOFFSET - 18, PLAYER2); // left shoe
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 16, lw - 2*OBJOFFSET - 18, PLAYER2); // right shoe	
	// Body
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7.5, (y*lw) + YUP + OBJOFFSET + 6, lw - 2*OBJOFFSET - 14 , lw - 2*OBJOFFSET - 11, PLAYER2); // chest 
	tft.fillRect(x*lw + XUP + OBJOFFSET + 3, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 18 , lw - 2*OBJOFFSET - 14, PLAYER2); // left arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 4, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, PLAYER2); // left shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 2, (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, SKIN);// left hand
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 18 , lw - 2*OBJOFFSET - 14, PLAYER2); // right arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 13, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, PLAYER2); // right shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, SKIN);// right hand	
	// Head
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) - 1 , 5, SKIN); // head
	// Face
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // left eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // left eye white
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // right eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // right eye white
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 8, ILI9341_BLACK);// mouth
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 7, ILI9341_BLACK);
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET + 8, ILI9341_BLACK);
	// Hat
	tft.fillRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET - 2, lw - 2*OBJOFFSET -10 , lw - 2*OBJOFFSET - 16, PLAYER2); // main hat
	tft.drawRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET - 2, lw - 2*OBJOFFSET -10 , lw - 2*OBJOFFSET - 16, ILI9341_BLACK);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET , lw - 2*OBJOFFSET -12 , lw - 2*OBJOFFSET - 17, PLAYER2); // brim
	tft.drawRect(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET , lw - 2*OBJOFFSET -12 , lw - 2*OBJOFFSET - 17, ILI9341_BLACK);
}


// Tekenen map attributen
void drawBomb(uint8_t x, uint8_t y) { // voor tekenen bom
	int frame = (tile_array[coords_to_tile(y, x)] % BOMB_FRAMES); // voor selecteren frame

//	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
//	x = BORDERDOWN - x; // snelle fix omdraaien y-as
//	uint8_t switch_value = x;
//	x = y;
//	y = switch_value;
//	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_PURPLE);

	/* Bom tekenen */
	if(frame == 0) { // zwarte bom
		tft.fillRect(x*lw + XUP + OBJOFFSET + 9.5, (y*lw) + YUP + OBJOFFSET + 3 , lw - 2*OBJOFFSET - 18  , lw - 2*OBJOFFSET - 13, LONT2); // lontje bom	
		tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, ILI9341_BLACK); // lichaam bom
		tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , ILI9341_WHITE); // details
		tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , ILI9341_WHITE);
		tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, FIRE); // fire
	} else if (frame == 1) { // eerst gekozen frame, rode bom
		tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 7, 5, ILI9341_RED); // lichaam bom // explosie
		tft.drawPixel(x*lw + XUP + OBJOFFSET + 8, (y*lw) + YUP + OBJOFFSET + 9 , ILI9341_WHITE); // details
		tft.drawPixel(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 10 , ILI9341_WHITE);
		tft.fillRect(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 2 ,lw - 2*OBJOFFSET - 17, lw - 2*OBJOFFSET - 17, FIRE); // fire
	}
}


void drawFire(uint8_t x, uint8_t y) { // voor tekenen vuur
	int frame = (tile_array[coords_to_tile(y, x)] % BOMB_FRAMES); // voor selecteren frame
	uint8_t switch_value = x;
	x = y;
	y = switch_value;

//	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as

	if(frame == 0) {
		tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_ORANGE);
	} else if (frame == 1) { // eerst gekozen frame
		tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_RED);
	}
}


void drawWall(uint8_t x, uint8_t y) { // voor tekenen muren (in het midden)
//	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, WALL);
//	tft.fillRect(x*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET, WALL);
}


void drawTon(uint8_t x, uint8_t y) { // tekenen ton
//	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
//	x = BORDERDOWN - x; // snelle fix omdraaien y-as
//	uint8_t switch_value = x;
//	x = y;
//	y = switch_value;
//	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_BLUE);

	tft.fillRect(x*lw + XUP + OBJOFFSET + 3 , (y*lw) + YUP + OBJOFFSET + 3 , lw - 2*OBJOFFSET - 5, lw - 2*OBJOFFSET - 5, TONBROWN); // lichaam ton
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 8,   7   , TONBROWN); // lichaam ton
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 2,   7   , TONBROWN);	// lichaam ton
	tft.fillRect(x*lw + XUP + OBJOFFSET +  3, (y*lw) + YUP + OBJOFFSET + 5 , lw - 2*OBJOFFSET - 5, lw - 2*OBJOFFSET - 17, ILI9341_BLACK); // details
	tft.fillRect(x*lw + XUP + OBJOFFSET + 3 , (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 5, lw - 2*OBJOFFSET - 17, ILI9341_BLACK); // details
}


// Teken main menu met attributen
void drawMainMenu() { // teken main menu
	drawTitle(); // tekent titel
	drawTitleBomb(); // tekent de bom op de 'o'
	drawStartButton(); // tekent de Start knop op het main menu
	drawHighScoreButton(); // tekent de Highscore knop op het main menu
	drawQuitButton(); // tekent de Quit knop op het main menu
}


void drawTitle() { // titel van main menu
	tft.fillScreen(MAINMENUCOLOR); // main menu achtergrond kleur
	drawTitleBackground(); // tekent bom achtergrond
	tft.fillRect(42, 5, 232, 42, TITLECOLOUR); // blokje om tekst
	tft.drawRect(41, 4, 233, 43, ILI9341_BLACK);
	tft.setCursor(TITLETPOSX + 2, TITLETPOSY - 2); // positie van schaduw tekst
	tft.setTextSize(TITLETSIZE); //textsize
	tft.setTextColor(SHADOWBCOLOR); // shaduw kleur van titel
	tft.println("B MBERMAN"); // schrijven van schaduw titel
	tft.setCursor(TITLETPOSX, TITLETPOSY);	// positie van titel
	tft.setTextColor(BCOLOR); // titel kleur
	tft.println("B MBERMAN"); // schrijven van titel
}


void drawTitleBomb() { // bom vorimge 'o' in main menu
	tft.fillRect(83, 9, 4, 10, LONT2); // lontje bom
	tft.fillRect(80, 14, 10, 5, ILI9341_BLACK); // topje bom
	tft.drawRect(80, 14, 10, 5, ILI9341_WHITE);
        tft.fillCircle(84, 29, 10, ILI9341_BLACK); // lichaam bom
	tft.drawCircle(84, 29, 11, ILI9341_WHITE);
        tft.fillRect(81, 22, 3, 3, ILI9341_WHITE); // details
        tft.fillRect(79, 24, 3, 3, ILI9341_WHITE);
	tft.fillRect(83, 7, 4, 4, FIRE); // fire
}


// Pauze menu
void drawPauseMenu() { // Tekent pauze menu
	tft.fillScreen(PAUSEMENUCOLOR); // tekent de achtergrond kleur van pauze menu
	drawTitleBackground(); // tekent de bom achtergrond
	tft.fillRect(47, 5, 225, 42, PAUZEBACK); // tekent het valk voor de titel
	tft.drawRect(46, 4, 226, 43, ILI9341_BLACK);
	tft.setTextSize(TITLETSIZE);
	tft.setCursor(TITLETPOSX + 52, TITLETPOSY - 2); // selecteerd de positie voor schaduw tekst
	tft.setTextColor(SHADOWPCOLOR); // selecteerd de schaduw tekst kleur
	tft.println("PAUSE"); // tekent het woord
	tft.setCursor(TITLETPOSX + 50, TITLETPOSY); //startpositie tekst
	tft.setTextColor(PAUZETEXT); // tekst kleur
	tft.println("PAUSE");
	drawContinueButton(); // tekent de continue knop
	drawQuitButton(); // tekent de quit knop
}


// Highscore scherm
void drawHighScores() {  // Tekent Highscores menu
	tft.fillScreen(HSBUTCOLOR); // tekent de highscore achtergrond kleur
	drawTitleBackground(); // tekent de bom achtergrond
	tft.fillRect(47, 5, 225, 42, HIGHSCORESBACK); // blokje om tekst
	tft.drawRect(46, 4, 226, 43, ILI9341_BLACK);
	tft.setCursor(TITLETPOSX + 17, TITLETPOSY ); // startpositie schaduw tekst
	tft.setTextSize(TITLETSIZE - 1); // tekst grootte
	tft.setTextColor(SHADOWHCOLOR); // schaduw kleur schaduw tekst
	tft.println("HIGH-SCORES"); // tekent het woord
	tft.setCursor(TITLETPOSX + 15, TITLETPOSY + 2); //startpositie tekst
	tft.setTextColor(HIGHSCORESTEXT); // kleur voor normale tekst
	tft.println("HIGH-SCORES"); // tekent het woord
	drawHighScoreboard(); // tekent het score board
	drawBackButton(); // tekent de terug knop
}


void drawHighScoreboard() { // Het score board waar de scores in staan
	tft.fillRect(HSFIELDX, HSFIELDY, HSFIELDW, (HSFIELDH), ILI9341_BLACK); // Achtergrond kleur
	tft.drawRect(HSFIELDX, HSFIELDY, HSFIELDW, 0.2*HSFIELDH, GOLD); // 1e high score kleur
	tft.drawRect(HSFIELDX, HSFIELDY+ 0.2*HSFIELDH, HSFIELDW, 0.2*HSFIELDH, SILVER); // 2e high score kleur
	tft.drawRect(HSFIELDX, HSFIELDY+ 0.4*HSFIELDH, HSFIELDW, 0.2*HSFIELDH, BRONZE); // 3e high score kleur
	tft.drawRect(HSFIELDX, HSFIELDY+ 0.6*HSFIELDH, HSFIELDW, 0.2*HSFIELDH, ILI9341_WHITE); // 4e en
	tft.drawRect(HSFIELDX, HSFIELDY+ 0.8*HSFIELDH, HSFIELDW, 0.2*HSFIELDH, ILI9341_WHITE); // 5e high score kleuren
	tft.setCursor(HSFIELDX + 10, HSFIELDY + 10); // locatie tekst 1e high score
	tft.setTextSize(2); // tekst grootte
	tft.setTextColor(GOLD); // tekst kleur 1e high score
	tft.print("1: "); // nummer 1
	tft.print(highscore1); // print variabele van 1e high score
	tft.setCursor(HSFIELDX + 10, HSFIELDY + 40); // locatie tekst 2e high score
	tft.setTextColor(SILVER); // tekst kleur 2e high score
	tft.print("2: ");
	tft.print(highscore2);
	tft.setCursor(HSFIELDX + 10, HSFIELDY + 70); // locatie tekst 3e high score
	tft.setTextColor(BRONZE); // tekst kleur 3e high score
	tft.print("3: ");
	tft.print(highscore3);
	tft.setCursor(HSFIELDX + 10, HSFIELDY + 100); // locatie tekst 4e high score
        tft.setTextColor(ILI9341_WHITE);
        tft.print("4: ");
        tft.print(highscore4);
        tft.setCursor(HSFIELDX + 10, HSFIELDY + 130); // locatie tekst 5e high score
        tft.setTextColor(ILI9341_WHITE);
        tft.print("5: ");
        tft.print(highscore5);
}


// Tekenen knoppen
void drawHighScoreButton() { // tekent de knop voor de highscores, kan voor meerdere menu's
	if(mainmenuselect == 1) {//voor nunchuck 1 = Highscores knop geselecteerd
		tft.fillRect(HSBUTRX, HSBUTRY, HSBUTRW, HSBUTRH, HSBUTSELCOLOR); // maakt het figuur voor de knop geselecteerd
		tft.setCursor(HSBUTSTPOSX, HSBUTSTPOSY); // selecteerd de positie voor de schaduw tekst
		tft.setTextColor(SHADOWCOLOR); // selecteerd de shaduwkleur voor de tekst
		tft.setTextSize(HSBUTTSIZE); // selecteerd de tekst grootte
		tft.println("HIGH-SCORES"); // print de tekst
		tft.setCursor(HSBUTTPOSX, HSBUTTPOSY); // selecteerd een nieuwe positie voor de tekst
		tft.setTextColor(TEXTCOLOR); // selecteerd de teskt kleur
		tft.println("HIGH-SCORES"); // print de tekst
	} else { // niet 1 = Highscore knop niet geselecteerd
		tft.fillRect(HSBUTRX, HSBUTRY, HSBUTRW, HSBUTRH, HSBUTCOLOR); // maakt het figuur voor de knop niet geselecteerd
		tft.setCursor(HSBUTTPOSX, HSBUTTPOSY);
		tft.setTextColor(TEXTCOLOR);
		tft.setTextSize(HSBUTTSIZE);
		tft.println("HIGH-SCORES");
	}
	tft.drawRect(HSBUTRX, HSBUTRY, HSBUTRW, HSBUTRH, ILI9341_BLACK); // omleining van knop
}


void drawStartButton() { // tekent de start knop kan voor meerdere menu's gebruikt worden
	if(mainmenuselect == 0) { //voor nunchuck 0 = Start button geselecteerd
		tft.fillRect(STARTBUTRX, STARTBUTRY, STARTBUTRW, STARTBUTRH, STARTBUTSELCOLOR); //make rectangle with select color
		tft.setCursor(STARTBUTSTPOSX, STARTBUTSTPOSY); //set cursur at shadow position (x + 2, y - 2)
		tft.setTextColor(SHADOWCOLOR); //shadow color (lightgrey)
		tft.setTextSize(STARTBUTTSIZE); //start button text size
		tft.println("START"); //shadowtext start
		tft.setCursor(STARTBUTTPOSX, STARTBUTTPOSY); //set cursor at 'start button text position x', and y
		tft.setTextColor(TEXTCOLOR); //set text color (when button is selected)
		tft.println("START"); //selected text start
	} else { // niet 0 = Start button niet geselecteerd
		tft.fillRect(STARTBUTRX, STARTBUTRY, STARTBUTRW, STARTBUTRH, STARTBUTCOLOR); //make rectangle with not selected color
		tft.setCursor(STARTBUTTPOSX, STARTBUTTPOSY); //set cursor at position
		tft.setTextColor(TEXTCOLOR); //text color
		tft.setTextSize(STARTBUTTSIZE);
		tft.println("START");
	}
	tft.drawRect(STARTBUTRX, STARTBUTRY, STARTBUTRW, STARTBUTRH, ILI9341_BLACK); // omleining van knop
}


void drawQuitButton() { // tekent de quit knop, voor meerdere menu's gebruikt
	if(mainmenuselect == 2 || pausemenuselect == 1) {//voor nunchuck als de 3e knop in main menu is geselecteerd of de 2e knop in het pauze menu
		tft.fillRect(QUITBUTRX, QUITBUTRY, QUITBUTRW, QUITBUTRH, QUITBUTSELCOLOR); // tekent het figuur waarbij de knop geselecteerd is
		tft.setCursor(QUITBUTSTPOSX, QUITBUTSTPOSY); // selecteerd de positie van de schaduw tekst
		tft.setTextColor(SHADOWCOLOR); // schaduw kleur voor shaduw tekst
		tft.setTextSize(QUITBUTTSIZE); // tekst groote
		tft.println("QUIT"); // tekent het woord
		tft.setCursor(QUITBUTTPOSX, QUITBUTTPOSY); // selecteerd nieuwe positie voor tekst
		tft.setTextColor(TEXTCOLOR); // tekst kleur
		tft.println("QUIT"); // tekent woord
	} else {
		tft.fillRect(QUITBUTRX, QUITBUTRY, QUITBUTRW, QUITBUTRH, QUITBUTCOLOR); // tekent het figuur waarbij de knop niet geselecteerd is
		tft.setCursor(QUITBUTTPOSX, QUITBUTTPOSY);
		tft.setTextColor(TEXTCOLOR);
		tft.setTextSize(QUITBUTTSIZE);
		tft.println("QUIT");
	}
	tft.drawRect(QUITBUTRX, QUITBUTRY, QUITBUTRW, QUITBUTRH, ILI9341_BLACK); // omleining knop
}


void drawContinueButton() { // tekent de continue knop
	if(pausemenuselect == 0) { //voor nunchuck als de 1e knop in het pauze menu is geselecteerd 
		tft.fillRect(STARTBUTRX, STARTBUTRY, STARTBUTRW, STARTBUTRH, CONTINEBUTCOLOR); //make rectangle with select color
		tft.setCursor(CONTBUTSTPOSX, STARTBUTSTPOSY); //set cursur at shadow position (x + 2, y - 2)
		tft.setTextColor(SHADOWCOLOR); //shadow color (lightgrey)
		tft.setTextSize(STARTBUTTSIZE); //start button text size
		tft.println("CONTINUE"); //shadowtext start
		tft.setCursor(CONTBUTTPOSX, STARTBUTTPOSY); //set cursor at 'start button text position x', and y
		tft.setTextColor(TEXTCOLOR); //set text color (when button is selected)
		tft.println("CONTINUE"); //selected text start
	} else { // als de 1e knop in het pauze menu niet is geselecteerd
		tft.fillRect(STARTBUTRX, STARTBUTRY, STARTBUTRW, STARTBUTRH, CONTINEBUTSELBUTCOLOR); //make rectangle with not selected color
		tft.setCursor(CONTBUTTPOSX, STARTBUTTPOSY); //set cursor at position
		tft.setTextColor(TEXTCOLOR); //text color
		tft.setTextSize(STARTBUTTSIZE);
		tft.println("CONTINUE");
	}
	tft.drawRect(STARTBUTRX, STARTBUTRY, STARTBUTRW, STARTBUTRH, ILI9341_BLACK); // omleining knop
}


void drawBackButton() { // tekent de terug knop
	tft.fillRect(BACKBUTRX, BACKBUTRY, BACKBUTRW, BACKBUTRH, BACKBUTROOD);  // tekent het figuur voor de knop
	tft.setCursor(BACKSTPOSX, BACKSTPOSY); // selecteerd de positie van de schaduw tekst
        tft.setTextColor(SHADOWCOLOR); // selecteerd de schaduw kleur voor de schaduw tekst
        tft.setTextSize(BACKBUTTSIZE); // selecteerd de tekst grootte
        tft.println("BACK"); // print de teskt
        tft.setCursor(BACKTPOSX, BACKTPOSY); // selecteerd de positie van de tekst
        tft.setTextColor(TEXTCOLOR); // selecteerd de tekst kleur
        tft.println("BACK"); // print de teskt
}


// Tekent de bom van de achtergrond van het main menu
void drawBomb2(uint16_t x, uint8_t y) { // tekent de bomentjes gebruikt voor de achtergrond
	tft.fillRect( x-1, y-15 , 3 , 5, LONT2); // lontje bom
	tft.fillRect( x-1, y-15, 3, 2, FIRE); // fire
	tft.fillRect( x-3, y-10, 7, 6, ILI9341_BLACK); // topje
	tft.drawRect( x-3, y-10, 7, 6, ILI9341_WHITE);
	tft.fillCircle( x, y, 7, ILI9341_BLACK); // lichaam bom
	tft.drawCircle( x, y, 7, ILI9341_WHITE);
	tft.fillRect(x-3, y-3, 2, 2, ILI9341_WHITE); // details
	tft.fillRect(x-4, y-2, 2, 2, ILI9341_WHITE);
}


// Tekent achter grond van main menu
void drawTitleBackground(){ // tekent de bom achtergrond
	for(int x = 20; x < 320; x = x + 40){ // tekent een gelijk aantal bommetjes op de hoogte y = 25
		int y = 25;
		drawBomb2(x, y);
	}
	for(int x = 0; x < 360; x = x + 40){ // hoogte op 60
		int y = 60;
		drawBomb2(x, y);
	}
	for(int x = 20; x < 320; x = x + 40){ // hoogte op 95
		int y = 95;
		drawBomb2(x, y);
	}
	for(int x = 0; x < 360; x = x + 40){ // hoogte op 130
		int y = 130;
		drawBomb2(x, y);
	}
	for(int x = 20; x < 320; x = x + 40){ // hoogte op 165
		int y = 165;
		drawBomb2(x, y);
	}
	for(int x = 0; x < 360; x = x + 40){ // hoogte op 200
		int y = 200;
		drawBomb2(x, y);
	}
	for(int x = 20; x < 320; x = x + 40){ // hoogte op 235
		int y = 235;
		drawBomb2(x, y);
	}
}
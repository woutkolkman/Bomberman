/* defines */
#define PLAYER 2 				// 1/2
#if PLAYER == 1 				// player-specifieke define settings
#define FREQUENCY 38 				// 38/56, geef frequentie aan IR LED
#elif PLAYER == 2
#define FREQUENCY 56 				// 38/56, geef frequentie aan IR LED
#endif
#define BAUD 9600 				// baudrate USART
//#define ADC_FREERUNNING 			// als dit defined is werkt de ADC op freerunning
//#define ADC_WAIT 				// als dit defined is wacht de processor totdat de ADC conversie klaar is
#define VAR_TYPE_IR uint16_t 			// variabele type voor IR communicatie
#define ADDRESS 0x52 				// nunchuk adres
#define GAMETICK_FREQUENCY 1 			// gameticks in HZ, max 0,119HZ, min 7812,5HZ
#define FCLK 16000000 				// arduino clock frequency
#define PRESCALER_TIMER1 1024 			// prescaler, zie ook functie timer1_init()
#define OFFSET_VAKJE 24 			// breedte & hoogte van een vakje
#define OFFSET_PLAYER_X 12 			// offset waarop player in vakje zit X
#define OFFSET_PLAYER_Y 20 			// offset waarop player in vakje zit Y
#define TFT_DC 9 				// initialisatie LCD
#define TFT_CS 10 				// initialisatie LCD
#define AANTALLENGTEBREEDTE WIDTH_MAP 		// aantal hokjes in lengte en breedte
#define LIGHTBROWN 0x7A00 			// voor tekenen kleur
#define DARKBROWN 0x5980 			// voor tekenen kleur
#define XUP 50 	// 10				// voor tekenen
#define YUP 10 	// 50				// voor tekenen
#define OBJOFFSET 2 				// voor tekenen
#define MAXOBJ 8 				// voor tekenen
#define TRUE 1
#define FALSE 0
#define TOMAINMENULENGTH 20			//tijd (in gameticks) hoelang het duurt voor mainmenu wordt getoond na einde spel

#define BORDERLEFTSIDE 0 			// min X
#define BORDERRIGHTSIDE 8 			// max X
#define WIDTH_MAP (BORDERRIGHTSIDE + 1)
#define BORDERUP 0 				// max Y
#define BORDERDOWN 8 				// min Y
#define HEIGHT_MAP (BORDERDOWN + 1)
#define FIRE_SPREADING 2			// geeft aan hoeveel vakken vuur moet bevatten vanuit de locatie van de bom
#define MAX_BOMBS 2				// geeft maximaal aantal bommen aan dat iedere player mag plaatsen
#define AANTALLENGTEBREEDTE WIDTH_MAP		// aantal hokjes in lengte en breedte
#define DEFAULT_PLAYER_HEALTH 3

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

// defines - tile states
#define BOMB_TILE_1S 10 			// player1 bom startwaarde, onderscheid voor bepalen score, >0
#define BOMB_TILE_1E (BOMB_TILE_1S + 12) 	// player1 bom eindwaarde, bepaalt na welke tijd bom afgaat, >=BOMB_TILE_1S
#define BOMB_TILE_2S 30 			// player2 bom startwaarde, onderscheid voor bepalen score, >0
#define BOMB_TILE_2E (BOMB_TILE_2S + 12) 	// player2 bom eindwaarde, bepaalt na welke tijd bom afgaat, >=BOMB_TILE_2S
#define FIRE_TILE_1S 50 			// player1 vuur startwaarde, onderscheid voor bepalen score, >0
#define FIRE_TILE_1E (FIRE_TILE_1S + 5) 	// player1 vuur eindwaarde, bepaalt hoe lang fire blijft staan, >=FIRE_TILE_1S
#define FIRE_TILE_2S 60 			// player2 vuur startwaarde, onderscheid voor bepalen score, >0
#define FIRE_TILE_2E (FIRE_TILE_2S + 5)  	// player2 vuur eindwaarde, bepaalt hoe lang fire blijft staan, >=FIRE_TILE_2S
#define EMPTY_TILE 9            		// locatie in array is leeg, >0
#define PLAYER1_TILE 1          		// locatie in array bevat player 1, >0
#define PLAYER2_TILE 2          		// locatie in array bevat player 2, >0
#define TON_TILE 3              		// locatie in array bevat box, >0
#define WALL_TILE 4             		// locatie in array bevat muur, >0
#if PLAYER == 1
#define PLAYER_TILE PLAYER1_TILE
#elif PLAYER == 2
#define PLAYER_TILE PLAYER2_TILE
#endif

// defines - animations
#define BOMB_FRAMES 2				// aantal frames van de animatie, handmatig toevoegen bij drawBomb(), >0, waarde begint bij 1
#define FIRE_FRAMES 2				// aantal frames van de animatie, handmatig toevoegen bij drawFire(), >0, waarde begint bij 1

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

// defines - datasoorten IR
#define LOST_CODE 0x01
#define READY_CODE 0x02
#define BOMB1_CODE 0x03
#define BOMB2_CODE 0x04
#define TON_CODE 0x05
#define WALL_CODE 0x06
#define UPDATE_HEALTH1_CODE 0x07
#define UPDATE_HEALTH2_CODE 0x08
#define PLAYER1_CODE 0x09
#define PLAYER2_CODE 0x0A
#define FIRE1_CODE 0x0B
#define FIRE2_CODE 0x0C


// algmeen
#define deleteScreen tft.fillScreen(ILI9341_BLACK);
#define quitScreen tft.fillScreen(ILI9341_BLACK);


/* includes IR */
//#include <cspi.h>
#include "libraries/IR/ir.h" // IR library
// includes
#include <util/setbaud.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <Adafruit_ILI9341.h> // LCD library
#include <Adafruit_GFX.h>// LCD library
#include <Arduino.h> // LCD library
#include <SPI.h>
#include <Wire.h>
#include <Nunchuk.h>
#include <usart.h>
#include <stdint.h>


// global variables
volatile uint8_t selectButtonFlag = 1; // variabele om functionaliteit menu te enablen/disablen
volatile uint8_t screenState = 0; // screen changes depending on its screenState
volatile uint8_t mainmenuselect = 0; // mainmenuselect goes from 0 - 1 - 2
volatile uint8_t state = 0; // states om interrupts in de main te laten uitrekenen, 0 = doe niks
volatile uint8_t brightness = 0; // brightness display
volatile unsigned int counter = 0;
volatile uint8_t lw = 220 / AANTALLENGTEBREEDTE; // TEKENEN VAN BREEDTE VAN EEN VAKJE
volatile uint8_t aantal_geplaatste_bommen = 0;
volatile uint8_t player1_locatie;
volatile uint8_t player2_locatie;
volatile uint8_t tile_array[(WIDTH_MAP * HEIGHT_MAP)]; // bevat players, boxes, muren, bommen, vuur
volatile uint8_t bomb_placed = 0;
volatile char pausemenuselect = 0;
volatile uint32_t highscore1 = 68420;
volatile uint32_t highscore2 = 3140;
volatile uint32_t highscore3 = 220;
volatile uint32_t highscore4 = 10;
volatile uint32_t highscore5 = 0;
volatile uint8_t livesleft1 = DEFAULT_PLAYER_HEALTH;
volatile uint8_t livesleft2 = DEFAULT_PLAYER_HEALTH;
volatile uint8_t counttomain = 0; //when losing or winning, wait 5 seconds (or 5 gameticks) to return to main menu


// use hardware SPI (on Uno, #13, #12, #11) and #10 and #9 for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


// function prototypes
void moveCursorNunchuk();
void selectButton();
void clearScreen();
void nunchuk_init();
void move(void);
void drawGrid();
void clearDraw(uint8_t x, uint8_t y);
void drawPlayer1(uint8_t x, uint8_t y);
void drawPlayer2(uint8_t x, uint8_t y);
void drawWall(uint8_t x, uint8_t y);
void drawBomb(uint8_t x, uint8_t y);
void drawTon(uint8_t x, uint8_t y);
void drawFire(uint8_t x, uint8_t y);
void adc_init(void);
void init(void);
void timer0_init(void);
void timer1_init(void);
void adc_init(void);
void game_init(void);
void screen_init(void);
void draw_screen(void);
void init_map(void);
uint8_t coords_to_tile(uint8_t x, uint8_t y);
uint8_t tile_to_coords_x(uint8_t tile);
uint8_t tile_to_coords_y(uint8_t tile);
uint8_t tile_is_leeg(uint8_t tile);
void bomb_placing(void);
void item_updating(void);
uint8_t tile_bevat_vuur(uint8_t tile);
uint8_t tile_bevat_bomb(uint8_t tile);
void bomb_explode(uint8_t tile);
void clear_tile(uint8_t tile);
uint8_t fire_placing(uint8_t tile, uint8_t fire_type, uint8_t eerste_bomb);
void drawPlayer1Field();
void drawPlayer2Field();
void drawHeart(uint16_t x, uint16_t y, uint16_t b, uint16_t h);
void drawMainMenu();
void drawHighScores();
void drawPauseMenu();
void drawTitle();
void drawStartButton();
void drawContinueButton();
void drawHighScoreButton();
void drawHighScoreboard();
void drawBackButton();
void drawQuitButton();
void drawTitleBomb();
void drawTitleBackground();
void drawBomb2(uint16_t x, uint8_t y);
void drawIets();
void ir_ontcijfer(VAR_TYPE_IR input);
void ir_verzenden(void);
void test_ir(void); // test
void ir_check_input(void);
#ifndef ADC_FREERUNNING
void single_conversion(void);
#endif


/* ISR */
ISR(ADC_vect) { // wordt aangeroepen wanneer ADC conversie klaar is
	brightness = (ADC >> 2); // 10 bits, gooi 2 LSB weg, uitkomst 8 bits
	// brightness toepassen op beeldscherm
}

ISR(TIMER1_COMPA_vect/*TIMER1_OVF_vect*/) { // gameticks
	state = 1; // uitvoeren in superloop
}

ISR(TIMER1_COMPB_vect) { // halve gametick
	state = 2; // uitvoeren in superloop
}


int main(void) {
	/* setup */
	DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5); // TFT scherm

	game_init();
	tft.begin(); // enable SPI communication
	tft.setRotation(3); // rotate screen
	drawMainMenu();
	//drawTitle();
	//drawTitleBomb();

	/* loop */
	for(;;) {
		Nunchuk.getState(ADDRESS); // retrieve states joystick and buttons Nunchuk
		_delay_ms(10);

		ir_check_input(); // pas IR ontvangen informatie toe wanneer beschikbaar

		if (screenState == 2) { // is start button is pressed
			selectButtonFlag = 0; // reset flag, op deze manier blijft functionaliteit mainmenu uit
			if (1 == state) { // TIMER1_COMPA_vect
				state = 0; // 1 keer uitvoeren na interrupt
				if(livesleft1 == 0 || livesleft2 == 0) {
	                                if(counttomain == TOMAINMENULENGTH) {
	                                        screenState = 0;
        	                                drawMainMenu();
                	                        livesleft1 = DEFAULT_PLAYER_HEALTH;
                        	                livesleft2 = DEFAULT_PLAYER_HEALTH;
                                	        counttomain = 0;
                               		} else {
                                	        counttomain++;
                                	}
                       		} else {
					clearDraw(tile_to_coords_x(player1_locatie), tile_to_coords_y(player1_locatie)); // haal speler weg huidige locatie
					clearDraw(tile_to_coords_x(player2_locatie), tile_to_coords_y(player2_locatie)); // haal speler weg huidige locatie
					move(); // pas nunchuk toe
					item_updating(); // animaties, en cycle door item states (bomb, fire)
					draw_screen(); // teken players opnieuw
				}
			}
			if (2 == state) { // TIMER1_COMPB_vect
				state = 0; // 1 keer uitvoeren na interrupt
				item_updating(); // animaties, en cycle door item states (bomb, fire)
			}
    		}

    		if (selectButtonFlag == 1) {		// in main menu knoppen kunnen selecteren
       			selectButton();					// in het begin staat flag altijd op 1, als spel bezig is op 0
    		}

		if (screenState == 0) { // aan het begin van het spel staat screenState op 0 om menuopties weer te geven
			drawStartButton();
			drawHighScoreButton();
			drawQuitButton();
		}

		#ifndef ADC_FREERUNNING
//		single_conversion();
		#endif
	}

	/* never reached */
	return 0;
}


void moveCursorNunchuk() {
	if (Nunchuk.Y_Axis() == 0 && mainmenuselect < 2) {
		mainmenuselect++;
	} else if (Nunchuk.Y_Axis() == 255 && mainmenuselect > 0) {
		mainmenuselect--;
	}
}


void selectButton() {
	moveCursorNunchuk(); // move cursor over buttons

	if (mainmenuselect == 2 && Nunchuk.C_Button() == 1) {
		screenState = 1;
		clearScreen();
	} else if (mainmenuselect == 0 && Nunchuk.C_Button() == 1) {
		screenState = 2;
		clearScreen();
	}
}


void clearScreen() {
	if (screenState == 2) { // if start button is pressed
		init_map(); // start map
		screen_init();
	} else if (screenState == 1) { // if quit button is pressed
		quitScreen;
		selectButtonFlag = 0;
	}
}


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


// globale initialisatie functie (ter vervanging van "init")
void game_init(void) {
	IR_prepare(FREQUENCY); // init IR

	init(); // onzichtbare functie
	timer0_init();
	timer1_init(); // gameticks
//	init_map(); // map vullen met players, muren, boxes, etc.
//	screen_init();
	Wire.begin(); // enable TWI communication
	nunchuk_init(); // start communication between Nunchuk and Arduino
	USART_Init(); // init serial

//	for (int i=0; i<=6; i++) { // dummy reads tegen te voeg plaatsen van bom bij sommige nunchuks
//		Nunchuk.getState(ADDRESS);
//		int dummy_read = Nunchuk.Z_Button();
//		dummy_read += 1;
//	}

	// pin in/outputs
	/*
	 * TFT scherm : digital 13-9
	 * Touchscreen : digital 8 (als deze wordt gebruikt)
	 * MicroSD lezer : digital 4 (als die wordt gebruikt)
	 * IR-zender : digital 3
	 * IR-ontvanger (?) : digital 2
	 * UART verbinding PC : digital 1, 0
	 * Podmeter : analog 2
	 * Nunchuck : analog 4, 5
	 */

	// enable global interrupts
	sei();
}


// functie voor het checken van input via IR, verwijst door naar ir_ontcijfer
void ir_check_input(void) {
	if (IR_nieuwe_input()) { ir_ontcijfer(IR_receive()); } // pas IR ontvangen informatie toe wanneer beschikbaar
}


// functie voor het ontcijferen en verwerken van nieuwe IR input
void ir_ontcijfer(VAR_TYPE_IR input) {
	// roep functie aan bij nieuwe informatie (PCINT?)

	// bepaal type informatie (zie laatste 3 bits)
	uint8_t data = input;
//	uint8_t kopie = input;
//	uint8_t kopie = (input & 0xFF00);
	uint8_t kopie = (input>>8);

	// verwerk input naar variabelen
	if (kopie == PLAYER1_CODE) {
//		clear_tile(player1_locatie);
		clearDraw(tile_to_coords_x(player1_locatie), tile_to_coords_y(player1_locatie));
		player1_locatie = data;
//		tile_array[data] = PLAYER1_TILE;
	} else if (kopie == PLAYER2_CODE) {
//		clear_tile(player1_locatie);
		clearDraw(tile_to_coords_x(player2_locatie), tile_to_coords_y(player2_locatie));
		player2_locatie = data;
//		tile_array[data] = PLAYER2_TILE;
	} else if (kopie == LOST_CODE) {
		// you win message
	} else if (kopie == READY_CODE) {
		// andere systeem is klaar om informatie te ontvangen, of om het spel te beginnen
	} else if (kopie == BOMB1_CODE) {
		tile_array[data] = BOMB_TILE_1S;
	} else if (kopie == BOMB2_CODE) {
		tile_array[data] = BOMB_TILE_2S;
	} else if (kopie == TON_CODE) {
		tile_array[data] = TON_TILE;
	} else if (kopie == WALL_CODE) {
		tile_array[data] = WALL_TILE;
	} else if (kopie == UPDATE_HEALTH1_CODE) {
		// update health player 1
		// teken hartjes
	} else if (kopie == UPDATE_HEALTH2_CODE) {
		// update health player 2
		// teken hartjes
	}
}


// functie voor het verzamelen en verzenden van IR output
void ir_verzenden(uint8_t data_type, uint8_t data) {
	VAR_TYPE_IR waarde = data; // stel eerste 8 bits in
	waarde |= (data_type<<8); // stel laatste 8 bits in
	IR_send(waarde); // verzend data
}


void screen_init(void) {
	// screen is 240 x 320
	tft.fillScreen(LIGHTBROWN);
	drawPlayer1Field(); // tekent de hartjes van player 1
	drawPlayer2Field(); // tekent de hartjes van player 2
	// tekent de speler's hartjes


	drawGrid();
	for (int i=0; i<(WIDTH_MAP * HEIGHT_MAP); i++) { // loop door volledige tile-array en teken alle items
		uint8_t tile = tile_array[i];
		if (tile == WALL_TILE) { // teken de muren
			drawWall(tile_to_coords_x(i), tile_to_coords_y(i));
		}
		if (tile == TON_TILE) {
			drawTon(tile_to_coords_x(i), tile_to_coords_y(i));
		}
		if (tile_bevat_vuur(tile) == PLAYER1_TILE) {
			drawFire(tile_to_coords_x(i), tile_to_coords_y(i));
		}
		if (tile_bevat_vuur(tile) == PLAYER2_TILE) {
			drawFire(tile_to_coords_x(i), tile_to_coords_y(i));
		}
		if (tile_bevat_bomb(tile) == PLAYER1_TILE) {
			drawBomb(tile_to_coords_x(i), tile_to_coords_y(i));
		}
		if (tile_bevat_bomb(tile) == PLAYER2_TILE) {
			drawBomb(tile_to_coords_x(i), tile_to_coords_y(i));
		}
	}
}


void draw_screen(void) {
	// screen is 240 x 320

	drawPlayer1(tile_to_coords_x(player1_locatie), tile_to_coords_y(player1_locatie));
	drawPlayer2(tile_to_coords_x(player2_locatie), tile_to_coords_y(player2_locatie));
}


// voor opvullen tile_array met players, muren & willekeurig geplaatste boxes
void init_map(void) {
	/*
	 * Locatie 0,0 is linksonder (0)
	 * Locatie 8,8 is rechtsboven (80)
	 */

	for (int i=0; i<(WIDTH_MAP * HEIGHT_MAP); i++) {
		tile_array[i] = EMPTY_TILE; // vul volledige tile_array met lege plekken
	}

	// test
	for (int i=0; i<(WIDTH_MAP * HEIGHT_MAP); i++) {
		tile_array[i] = TON_TILE; // TEST, vul volledige tile_array met tonnetjes
	}
	tile_array[9] = EMPTY_TILE;
	tile_array[18] = EMPTY_TILE;
	tile_array[1] = EMPTY_TILE;
	tile_array[71] = EMPTY_TILE;
	tile_array[62] = EMPTY_TILE;
	tile_array[79] = EMPTY_TILE;
	// test

	tile_array[0] = PLAYER1_TILE; // plaats player 1 linksboven
	player1_locatie = 0;
	tile_array[80] = PLAYER2_TILE; // plaats player 2 rechtsonder
	player2_locatie = 80;

	for (int i=10; i<=64; i+=18) {
		for (int j=0; j<=6; j+=2) {
			tile_array[i+j] = WALL_TILE; // plaats 4x4 muren met ruimte ertussen
		}
	}

//	tile_array[4] = TON_TILE; // plaats 1 doos, test
//	tile_array[5] = BOMB_TILE_1S; // plaats 1 bom, test
//	tile_array[40] = BOMB_TILE_2S;
//	tile_array[6] = FIRE_TILE_1S; // plaats 1 vuur, test

	/*
	 * Locaties in array (9x9)
	 *	0	1	2	3	4	5	6	7	8
	 *	9	10	11	12	13	14	15	16	17
	 *	18	19	20	21	22	23	24	25	26
	 *	27	28	29	30	31	32	33	34	35
	 *	36	37	38	39	40	41	42	43	44
	 *	45	46	47	48	49	50	51	52	53
	 *	54	55	56	57	58	59	60	61	62
	 *	63	64	65	66	67	68	69	70	71
	 *	72	73	74	75	76	77	78	79	80
	 */
}


// verkrijg tile nummer van coordinaten
uint8_t coords_to_tile(uint8_t x, uint8_t y) {
	return ((x * WIDTH_MAP) + y); // x bepaalt in welke rij, y bepaalt in welke kolom
}


// verkrijg x coordinaat van tile nummer
uint8_t tile_to_coords_x(uint8_t tile) {
	return (tile % WIDTH_MAP); // stuur rest van deling
}


// verkrijg y coordinaat van tile nummer
uint8_t tile_to_coords_y(uint8_t tile) {
	return (tile / HEIGHT_MAP); // stuur deling zonder rest
}


// return 1 als tile leeg is, 0 als tile vol is
uint8_t tile_is_leeg(uint8_t tile) {
	if (tile_array[tile] == EMPTY_TILE) {
		return 1;
	} else {
		return 0;
	}
}


// return 1 als fire van player 1 is, 2 als fire van player 2 is
uint8_t tile_bevat_vuur(uint8_t tile) {
	uint8_t type_tile = tile_array[tile];

	if (type_tile >= FIRE_TILE_1S && type_tile <= FIRE_TILE_1E) {
		// fire is van player 1
		return PLAYER1_TILE;
	} else if (type_tile >= FIRE_TILE_2S && type_tile <= FIRE_TILE_2E) {
		// fire is van player 2
		return PLAYER2_TILE;
	} else {
		// geen fire-tile
		return 0;
	}
}


// return 1 als bomb van player 1 is, 2 als bomb van player 2 is
uint8_t tile_bevat_bomb(uint8_t tile) {
	int type_tile = tile_array[tile];

        if (type_tile >= BOMB_TILE_1S && type_tile <= BOMB_TILE_1E) {
                // bom is van player 1
                return PLAYER1_TILE;
        } else if (type_tile >= BOMB_TILE_2S && type_tile <= BOMB_TILE_2E) {
                // bom is van player 2
                return PLAYER2_TILE;
        } else {
                // geen bomb-tile
                return 0;
        }
}


// haal getekende vakje weg en reset tile in tile_array
void clear_tile(uint8_t tile) {
	tile_array[tile] = EMPTY_TILE;
	clearDraw(tile_to_coords_x(tile), tile_to_coords_y(tile));
}


// functie voor damagen huidige speler, i.v.m. scores check welk soort fire wordt getekend
// iedere client houdt voor zichzelf bij of de betreffende speler gedamaged wordt
void damage_player(uint8_t fire_type) {
	if (PLAYER == 1) {
		livesleft1--;
		if (fire_type >= FIRE_TILE_1S && fire_type <= FIRE_TILE_1E) { // is het friendly-fire?
			// speler is door eigen bom geraakt
			// score toepassen
		} else {
			// speler is geraakt door bom van tegenstander
			// score toepassen
		}
		drawPlayer1Field(); // hartjes
		if (livesleft1 <= 0) {
//			if(PLAYER == 1) {
			displayLoseMessage(); //player 1 lose
			// transmit lose ir
//			} else {
//				displayWinMessage(); //player 2 wins
//			}
		}
	} else if (PLAYER == 2) {
		livesleft2--;
		if (fire_type >= FIRE_TILE_2S && fire_type <= FIRE_TILE_2E) { // is het friendly-fire?
			// speler is door eigen bom geraakt
			// score toepassen
		} else {
			// speler is geraakt door bom van tegenstander
			// score toepassen
		}
		drawPlayer2Field(); // hartjes
		if (livesleft2 <= 0) {
//			if(PLAYER == 1) {
//                                displayWinMessage(); //player 1 wins
//                        } else {
                	displayLoseMessage(); //player 2 loses
			// transmit lose ir
//                	}
		}
	}
}


// bewegingsfunctie voor de player die wordt gespeeld (1/2)
void move(void) {
	volatile uint8_t *player_pointer;
	#if PLAYER == 1
	player_pointer = &player1_locatie;
	#elif PLAYER == 2
	player_pointer = &player2_locatie;
	#endif
	if (!player_pointer) { // player_pointer = NULL
		return;
	}

	// kan maar 1 kant op bewegen per keer, zolang er niks in de weg staat en player niet van de map afgaat
	if (Nunchuk.X_Axis() == 255) { // 1 naar rechts
        	if (tile_to_coords_x(*player_pointer) < BORDERRIGHTSIDE // als player niet van map afgaat
		&& (tile_is_leeg(1 + *player_pointer) // en als er niks in de weg staat, of
		|| tile_bevat_vuur(1 + *player_pointer))) { // ..als er vuur in de weg staat
			tile_array[*player_pointer] = EMPTY_TILE;
			bomb_placing(); // check of er een bomb geplaatst moet worden
                	*player_pointer += 1;
			if (tile_bevat_vuur(*player_pointer)) { damage_player(tile_array[*player_pointer]); } // als player1_locatie nu vuur bevat, damage player
			#if PLAYER == 1
			tile_array[player1_locatie] = PLAYER1_TILE;
			ir_verzenden(PLAYER1_CODE, player1_locatie); // verzend via IR
			#elif PLAYER == 2
			tile_array[player2_locatie] = PLAYER2_TILE;
			ir_verzenden(PLAYER2_CODE, player2_locatie); // verzend via IR
			#endif
        	}
	} else if (Nunchuk.X_Axis() == 0) { // 1 naar links
        	if (tile_to_coords_x(*player_pointer) > BORDERLEFTSIDE // als player niet van map afgaat
		&& (tile_is_leeg(-1 + *player_pointer) // en als er niks in de weg staat, of
		|| tile_bevat_vuur(-1 + *player_pointer))) { // ..als er vuur in de weg staat
			tile_array[*player_pointer] = EMPTY_TILE;
			bomb_placing(); // check of er een bomb geplaatst moet worden
                	*player_pointer -= 1;
			if (tile_bevat_vuur(*player_pointer)) { damage_player(tile_array[*player_pointer]); } // als player1_locatie nu vuur bevat, damage player
			#if PLAYER == 1
			tile_array[player1_locatie] = PLAYER1_TILE;
			ir_verzenden(PLAYER1_CODE, player1_locatie); // verzend via IR
			#elif PLAYER == 2
			tile_array[player2_locatie] = PLAYER2_TILE;
			ir_verzenden(PLAYER2_CODE, player2_locatie); // verzend via IR
			#endif
        	}
	} else if (Nunchuk.Y_Axis() == 255) { // 1 omhoog
                if (tile_to_coords_y(*player_pointer) > BORDERUP // als player niet van map afgaat
		&& (tile_is_leeg(-WIDTH_MAP + *player_pointer) // en als er niks in de weg staat, of
		|| tile_bevat_vuur(-WIDTH_MAP + *player_pointer))) { // ..als er vuur in de weg staat
			tile_array[*player_pointer] = EMPTY_TILE;
			bomb_placing(); // check of er een bomb geplaatst moet worden
                        *player_pointer -= WIDTH_MAP;
			if (tile_bevat_vuur(*player_pointer)) { damage_player(tile_array[*player_pointer]); } // als player1_locatie nu vuur bevat, damage player
			#if PLAYER == 1
			tile_array[player1_locatie] = PLAYER1_TILE;
			ir_verzenden(PLAYER1_CODE, player1_locatie); // verzend via IR
			#elif PLAYER == 2
			tile_array[player2_locatie] = PLAYER2_TILE;
			ir_verzenden(PLAYER2_CODE, player2_locatie); // verzend via IR
			#endif
                }
        } else if (Nunchuk.Y_Axis() == 0) { // 1 omlaag
                if (tile_to_coords_y(*player_pointer) < BORDERDOWN // als player niet van map afgaat
		&& (tile_is_leeg(WIDTH_MAP + *player_pointer) // en als er niks in de weg staat, of
		|| tile_bevat_vuur(WIDTH_MAP + *player_pointer))) { // ..als er vuur in de weg staat
			tile_array[*player_pointer] = EMPTY_TILE;
			bomb_placing(); // check of er een bomb geplaatst moet worden
                        *player_pointer += WIDTH_MAP;
			if (tile_bevat_vuur(*player_pointer)) { damage_player(tile_array[*player_pointer]); } // als player1_locatie nu vuur bevat, damage player
			#if PLAYER == 1
			tile_array[player1_locatie] = PLAYER1_TILE;
			ir_verzenden(PLAYER1_CODE, player1_locatie); // verzend via IR
			#elif PLAYER == 2
			tile_array[player2_locatie] = PLAYER2_TILE;
			ir_verzenden(PLAYER2_CODE, player2_locatie); // verzend via IR
			#endif
                }
        }
	if (Nunchuk.Z_Button() == 1) { // als bomb button is ingedrukt
		bomb_placed = 1; // bij volgende move(), leg een bomb neer
	}
//	free((void*) player_pointer); // niet weghalen, TODO mogelijk pointer weghalen
}


// plaats bom als button was ingedrukt, vervangt huidige locatie player met een bom
void bomb_placing(void) {
	if (bomb_placed == 1 && aantal_geplaatste_bommen < MAX_BOMBS) {
		#if PLAYER == 1
		tile_array[player1_locatie] = BOMB_TILE_1S;
		ir_verzenden(BOMB1_CODE, player1_locatie); // verzend via IR
		drawBomb(tile_to_coords_x(player1_locatie), tile_to_coords_y(player1_locatie)); // tijdelijk
		#elif PLAYER == 2
		tile_array[player2_locatie] = BOMB_TILE_2S;
		ir_verzenden(BOMB2_CODE, player2_locatie); // verzend via IR
		drawBomb(tile_to_coords_x(player2_locatie), tile_to_coords_y(player2_locatie)); // tijdelijk
		#endif
		// plaats bom van huidige speler

		bomb_placed = 0;
		aantal_geplaatste_bommen++;
	} else {
		bomb_placed = 0; // resetten button zodat er niet onverwachts een bom wordt geplaatst
	}
}


// updated items op het veld, bombs & fire item states, ook voor animaties
void item_updating(void) {
	for (int i=0; i<(WIDTH_MAP * HEIGHT_MAP); i++) { // loop door volledige tile_array
                uint8_t tile = tile_array[i];
		if (tile_bevat_bomb(i) == PLAYER1_TILE) { // player 1 bom
			tile_array[i]++; // volgende frame
			tile++;
			clearDraw(tile_to_coords_x(i), tile_to_coords_y(i));
			if (tile >= BOMB_TILE_1E) { // als bom in laatste state is
				bomb_explode(i);
			} else {
				// bepaal welke frame of texture van de animatie displayed moet worden
				// drawBomb(tile_to_coords_x(tile), tile_to_coords_y(tile), (tile_array[tile]%BOMB_FRAMES));

				drawBomb(tile_to_coords_x(i), tile_to_coords_y(i));
			}
		} else if (tile_bevat_bomb(i) == PLAYER2_TILE) { // player 2 bom
			tile_array[i]++; // volgende frame
			tile++;
			clearDraw(tile_to_coords_x(i), tile_to_coords_y(i));
			if (tile >= BOMB_TILE_2E) { // als bom in laatste state is
				bomb_explode(i);
			} else {
				// bepaal welke frame of texture van de animatie displayed moet worden
				// ...

				drawBomb(tile_to_coords_x(i), tile_to_coords_y(i));
			}
		} else if (tile_bevat_vuur(i) == PLAYER1_TILE) {
			tile_array[i]++; // volgende frame
			tile++;
			clearDraw(tile_to_coords_x(i), tile_to_coords_y(i));
			if (tile >= FIRE_TILE_1E) { // vuur weghalen als het lang genoeg heeft bestaan
				clear_tile(i);
			} else {
				// bepaal welke frame of texture van de animatie displayed moet worden
				// ...

				drawFire(tile_to_coords_x(i), tile_to_coords_y(i));
			}
		} else if (tile_bevat_vuur(i) == PLAYER2_TILE) {
			tile_array[i]++; // volgende frame
			tile++;
			clearDraw(tile_to_coords_x(i), tile_to_coords_y(i));
			if (tile >= FIRE_TILE_2E) { // vuur weghalen als het lang genoeg heeft bestaan
				clear_tile(i);
			} else {
				// bepaal welke frame of texture van de animatie displayed moet worden
				// ...

				drawFire(tile_to_coords_x(i), tile_to_coords_y(i));
			}
//		} else if () {
//
//		} else if () {
//
		}
	}
}


// voor tekenen en genereren explosie met FIRE_TILEs
void bomb_explode(uint8_t tile) {
	uint8_t te_tekenen_tile;

	// bepaal van welke speler de bom is
	if (tile_bevat_bomb(tile) == PLAYER1_TILE) { // bom is van player 1
		te_tekenen_tile = FIRE_TILE_1S; // teken vuur van player 1
		#if PLAYER == 1
		aantal_geplaatste_bommen--;
		#endif
	} else if (tile_bevat_bomb(tile) == PLAYER2_TILE) { // bom is van player 2
		te_tekenen_tile = FIRE_TILE_2S; // teken vuur van player 2
		#if PLAYER == 2
		aantal_geplaatste_bommen--;
		#endif
	} else { // meegekregen tile is geen bomb
		return;
	}

	fire_placing(tile, te_tekenen_tile+1, TRUE); // vervang bom door vuur

	int i = 0;
	while (i<FIRE_SPREADING) { // vuur verspreiden omhoog
		if (tile_to_coords_y(tile-(i*WIDTH_MAP)) == BORDERUP) { // wordt hier uitgevoerd zodat array niet out-of-bounds kan worden gelezen
			break; // stop als het vuur anders van de map af wordt getekend
		}
		i++;
		if (fire_placing(tile-(i*WIDTH_MAP), te_tekenen_tile+1, FALSE)) { // plaats vuur
			break; // stop als er iets in de weg stond
		}
	}
	i = 0;
	while (i<FIRE_SPREADING) { // vuur verspreiden omlaag
		if (tile_to_coords_y(tile+(i*WIDTH_MAP)) == BORDERDOWN) { // wordt hier uitgevoerd zodat array niet out-of-bounds kan worden gelezen
			break; // stop als het vuur anders van de map af wordt getekend
		}
		i++;
		if (fire_placing(tile+(i*WIDTH_MAP), te_tekenen_tile, FALSE)) { // plaats vuur
			break; // stop als er iets in de weg stond
		}
	}
	i = 0;
	while (i<FIRE_SPREADING) { // vuur verspreiden rechts
		if (tile_to_coords_x(tile+i) == BORDERRIGHTSIDE) { // wordt hier uitgevoerd zodat array niet out-of-bounds kan worden gelezen
			break; // stop als het vuur anders van de map af wordt getekend
		}
		i++;
		if (fire_placing(tile+i, te_tekenen_tile, FALSE)) { // plaats vuur
			break; // stop als er iets in de weg stond
		}
	}
	i = 0;
	while (i<FIRE_SPREADING) { // vuur verspreiden links
		if (tile_to_coords_x(tile-i) == BORDERLEFTSIDE) { // wordt hier uitgevoerd zodat array niet out-of-bounds kan worden gelezen
			break; // stop als het vuur anders van de map af wordt getekend
		}
		i++;
		if (fire_placing(tile-i, te_tekenen_tile+1, FALSE)) { // plaats vuur
			break; // stop als er iets in de weg stond
		}
	}
}


// voor plaatsen fire, return 1 als er iets in de weg stond (behalve map border)
uint8_t fire_placing(uint8_t tile, uint8_t fire_type, uint8_t eerste_bomb) {
	int return_iets = 0;
	if (PLAYER_TILE == tile_array[tile]) { // als player op de locatie van het te tekenen vuur staat
		return_iets = 1;
		damage_player(fire_type); // damage huidige speler
	} else if (TON_TILE == tile_array[tile]) {
		return_iets = 1;
	} else if (tile_bevat_bomb(tile) && !eerste_bomb) {
		return_iets = 1;
		bomb_explode(tile);
	}

	if (WALL_TILE == tile_array[tile]) {
		return_iets = 1;
	} else {
		// vuur mag alleen geplaatst worden als tile leeg is of gelijk is aan player of ton, niet gelijk aan muur
		if (tile_array[tile] != PLAYER1_TILE && tile_array[tile] != PLAYER2_TILE) {
			// tonnetjes worden overschreven, players niet
			tile_array[tile] = fire_type;
		}
		drawFire(tile_to_coords_x(tile), tile_to_coords_y(tile));
	}

	if (return_iets) {
		return 1;
	} else {
		return 0;
	}
}


void drawGrid() {
        tft.fillRect(XUP /*niet op grens van scherm X */, YUP/*niet op grens van scherm Y*/, AANTALLENGTEBREEDTE*lw /*volledige game-grid*/, AANTALLENGTEBREEDTE*lw /*volledige game-grid*/, GRIDCOLOUR /*donkerbruine achtergrond*/);
        for (int x = 0; x < 9; x++) {
                for (int y = 0; y < 9; y++) {
                        tft.drawRect((x * lw) + XUP, (y * lw) + YUP, lw + 1, lw + 1, ILI9341_BLACK);
                }
        }
}


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

	/* blokje */
//	tft.fillRect((x * lw) + XUP + OBJOFFSET, (y * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_CYAN);
//	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_CYAN);

	/* mannetje */
	/* Pants */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6.5, (y*lw) + YUP + OBJOFFSET + 10, lw - 2*OBJOFFSET - 12 , lw - 2*OBJOFFSET - 20 , ILI9341_BLACK); // pant
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // left leg
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // right leg
	/* Shoes */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 16, lw - 2*OBJOFFSET - 18, PLAYER1); // left shoe
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 16, lw - 2*OBJOFFSET - 18, PLAYER1); // right shoe	
	/* Body  */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7.5, (y*lw) + YUP + OBJOFFSET + 6, lw - 2*OBJOFFSET - 14 , lw - 2*OBJOFFSET - 12, PLAYER1); // chest 
	tft.fillRect(x*lw + XUP + OBJOFFSET + 3, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 18 , lw - 2*OBJOFFSET - 14, PLAYER1); // left arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 4, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, PLAYER1); // left shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 2, (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, SKIN);// left hand
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 18 , lw - 2*OBJOFFSET - 14, PLAYER1); // right arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 13, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, PLAYER1); // right shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, SKIN);// right hand	
	/* Head */
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) - 1 , 5, SKIN); // head
	/* Face */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // left eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // left eye white
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // right eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // right eye white
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 8, ILI9341_BLACK);// mouth
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 7, ILI9341_BLACK);
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET + 8, ILI9341_BLACK);
	/* Hat  */
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

	/* blokje */
//	tft.fillRect((x * lw) + XUP + OBJOFFSET, (y * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_RED);
//	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_RED);

	/* mannetje */
	/* Pants */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 6.5, (y*lw) + YUP + OBJOFFSET + 10, lw - 2*OBJOFFSET - 12 , lw - 2*OBJOFFSET - 20 , ILI9341_BLACK); // pant
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // left leg
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // right leg
	/* Shoes */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 16, lw - 2*OBJOFFSET - 18, PLAYER2); // left shoe
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 16, lw - 2*OBJOFFSET - 18, PLAYER2); // right shoe	
	/* Body  */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7.5, (y*lw) + YUP + OBJOFFSET + 6, lw - 2*OBJOFFSET - 14 , lw - 2*OBJOFFSET - 11, PLAYER2); // chest 
	tft.fillRect(x*lw + XUP + OBJOFFSET + 3, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 18 , lw - 2*OBJOFFSET - 14, PLAYER2); // left arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 4, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, PLAYER2); // left shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 2, (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, SKIN);// left hand
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 18 , lw - 2*OBJOFFSET - 14, PLAYER2); // right arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 13, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, PLAYER2); // right shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, SKIN);// right hand	
	/* Head */
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) - 1 , 5, SKIN); // head
	/* Face */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // left eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // left eye white
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // right eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // right eye white
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 8, ILI9341_BLACK);// mouth
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 7, ILI9341_BLACK);
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET + 8, ILI9341_BLACK);
	/* Hat  */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET - 2, lw - 2*OBJOFFSET -10 , lw - 2*OBJOFFSET - 16, PLAYER2); // main hat
	tft.drawRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET - 2, lw - 2*OBJOFFSET -10 , lw - 2*OBJOFFSET - 16, ILI9341_BLACK);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET , lw - 2*OBJOFFSET -12 , lw - 2*OBJOFFSET - 17, PLAYER2); // brim
	tft.drawRect(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET , lw - 2*OBJOFFSET -12 , lw - 2*OBJOFFSET - 17, ILI9341_BLACK);
}


// voor tekenen muren (in het midden)
void drawWall(uint8_t x, uint8_t y) {
//	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, WALL);
//	tft.fillRect(x*lw + XUP + OBJOFFSET, (y*lw) + YUP + OBJOFFSET, lw - 2*OBJOFFSET +1, lw - 2*OBJOFFSET, WALL);
}


// voor tekenen vuur
void drawFire(uint8_t x, uint8_t y) {
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


// voor tekenen bom
void drawBomb(uint8_t x, uint8_t y) {
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


// voor tekenen ton
void drawTon(uint8_t x, uint8_t y) {
//	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
//	x = BORDERDOWN - x; // snelle fix omdraaien y-as
//	uint8_t switch_value = x;
//	x = y;
//	y = switch_value;
//	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_BLUE);

	/* Ton tekenen */
	tft.fillRect(x*lw + XUP + OBJOFFSET + 3 , (y*lw) + YUP + OBJOFFSET + 3 , lw - 2*OBJOFFSET - 5, lw - 2*OBJOFFSET - 5, TONBROWN); // lichaam ton
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 8,   7   , TONBROWN); // lichaam ton
	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) + 2,   7   , TONBROWN);	// lichaam ton
	tft.fillRect(x*lw + XUP + OBJOFFSET +  3, (y*lw) + YUP + OBJOFFSET + 5 , lw - 2*OBJOFFSET - 5, lw - 2*OBJOFFSET - 17, ILI9341_BLACK); // details
	tft.fillRect(x*lw + XUP + OBJOFFSET + 3 , (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 5, lw - 2*OBJOFFSET - 17, ILI9341_BLACK); // details
}


void nunchuk_init() {
	DDRC &= ~(1 << DDC4) & ~(1 << DDC5); // Nunchuk
	Nunchuk.begin(ADDRESS); // start communication with Arduino and Nunchuk
}


void timer0_init(void) {
	
}

void timer1_init(void) { // gameticks timer 1
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1B |= (1 << WGM12); // CTC, OCR1A top
	OCR1A = (FCLK / (GAMETICK_FREQUENCY * 2 * PRESCALER_TIMER1)); // frequentie aangeven
	OCR1B = (OCR1A / 2);

	#if PRESCALER_TIMER1 == 1024
	TCCR1B |= (1 << CS12) /* | (1<<CS11) */ | (1 << CS10); // prescaler 1024
	#else
	#pragma GCC error "geen bruikbare prescaler ingesteld"
	#endif

	TIMSK1 |= (1 << OCIE1A); // output compare match interrupt A enable
	TIMSK1 |= (1 << OCIE1B); // output compare match interrupt B enable
//	TIMSK1 |= (1 << TOIE1); // overflow interrupt enable
}


void adc_init(void) { // initialiseer ADC
	ADMUX |= (1 << REFS0); // reference voltage on AVCC (5V)
	ADCSRA |= (1 << ADIE); // ADC interrupt enable
	ADMUX |= (1<<MUX1); // input kanaal A2 // uit IR adc_init
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // ADC clock prescaler ...(nog kiezen)

	#ifdef ADC_FREERUNNING
	ADCSRA |= (1<<ADATE); // ADC auto trigger enable \/
	ADCSRB &= ~(1<<ADTS2) & ~(1<<ADTS1) & ~(1<<ADTS0); // free running mode
	ADCSRA |= (1<<ADEN); // enable ADC
        ADCSRA |= (1<<ADSC); // start eerste meting
	#else
	ADCSRA |= (1<<ADEN); // enable ADC
	#endif
}


#ifndef ADC_FREERUNNING
void single_conversion() {
	ADCSRA |= (1<<ADSC); // start single ADC conversion
	#ifdef ADC_WAIT
	while (ADCSRA & (1<<ADSC)); // wait until done
	#endif

	// values worden in de ISR gezet
}
#endif


/* Alle schermpjes/menu's/knopjes */
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


void test_ir() {
	#define IR_TEST 0 // 0(uit)/1/2/3/4

	#if IR_TEST == 1
	if (IR_nieuwe_input()) { IR_send((IR_receive() + 1)); }
	#elif IR_TEST == 2
	VAR_TYPE_IR test_input;
	test_input = USART_Receive();
	if (test_input != 0x00) { IR_send(test_input); }
	test_input = 0x00;
	_delay_ms(3000);
	if (IR_nieuwe_input()) { USART_Transmit(IR_receive()); }
	#elif IR_TEST == 3
//	IR_send(0xAA); // 1010 1010
//	IR_send(0xFF);
//	IR_send(0x00);
//	IR_send(0x32); // 0011 0010, print '2'
	IR_send(0x1432);
//	IR_send(0xFFFF);
//	IR_send(0x33);
//	IR_send(0x41);
//	IR_send(0x42);
	_delay_ms(3500);
	#elif IR_TEST == 4
	if (IR_nieuwe_input()) {
		_delay_ms(500);
		USART_Transmit(IR_receive());
	}
	#endif
}

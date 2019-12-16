// defines
#define PLAYER 1 				// 1/2
#define ADDRESS 0x52 				// nunchuk adres
#define GAMETICK_FREQUENCY 1 			// gameticks in HZ, max 0,119HZ, min 7812,5HZ
#define FCLK 16000000 				// arduino clock frequency
#define PRESCALER_TIMER1 1024 			// prescaler, zie ook functie timer1_init()
#define OFFSET_VAKJE 24 			// breedte & hoogte van een vakje
#define OFFSET_PLAYER_X 12 			// offset waarop player in vakje zit X
#define OFFSET_PLAYER_Y 20 			// offset waarop player in vakje zit Y
#define BAUD 9600 				// baudrate USART
#define TFT_DC 9 				// initialisatie LCD
#define TFT_CS 10 				// initialisatie LCD
#define AANTALLENGTEBREEDTE WIDTH_MAP 		// aantal hokjes in lengte en breedte
#define LIGHTBROWN 0x7A00 			// voor tekenen kleur
#define DARKBROWN 0x5980 			// voor tekenen kleur
#define XUP 50 // was 10 					// voor tekenen
#define YUP 10 // was 50					// voor tekenen
#define OBJOFFSET 2 				// voor tekenen
#define MAXOBJ 8 				// voor tekenen
#define TRUE 1
#define FALSE 0

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
#define BOMB_TILE_2S 20 			// player2 bom startwaarde, onderscheid voor bepalen score, >0
#define BOMB_TILE_2E (BOMB_TILE_2S + 12) 	// player2 bom eindwaarde, bepaalt na welke tijd bom afgaat, >=BOMB_TILE_2S
#define FIRE_TILE_1S 40 			// player1 vuur startwaarde, onderscheid voor bepalen score, >0
#define FIRE_TILE_1E (FIRE_TILE_1S + 5) 	// player1 vuur eindwaarde, bepaalt hoe lang fire blijft staan, >=FIRE_TILE_1S
#define FIRE_TILE_2S 50 			// player2 vuur startwaarde, onderscheid voor bepalen score, >0
#define FIRE_TILE_2E (FIRE_TILE_2S + 5)  	// player2 vuur eindwaarde, bepaalt hoe lang fire blijft staan, >=FIRE_TILE_2S
#define EMPTY_TILE 9            		// locatie in array is leeg, >0
#define PLAYER1_TILE 1          		// locatie in array bevat player 1, >0
#define PLAYER2_TILE 2          		// locatie in array bevat player 2, >0
#define TON_TILE 3              		// locatie in array bevat box, >0
#define WALL_TILE 4             		// locatie in array bevat muur, >0

// defines - animations
#define BOMB_FRAMES 2				// aantal frames van de animatie, handmatig toevoegen bij drawBomb(), >0, waarde begint bij 1
#define FIRE_FRAMES 2				// aantal frames van de animatie, handmatig toevoegen bij drawFire(), >0, waarde begint bij 1

#if PLAYER == 1
#define PLAYER_TILE PLAYER1_TILE
#elif PLAYER == 2
#define PLAYER_TILE PLAYER2_TILE
#endif


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
volatile uint8_t state = 0; // states om interrupts in de main te laten uitrekenen, 0 = doe niks
volatile uint8_t player1_health = DEFAULT_PLAYER_HEALTH;
volatile uint8_t player2_health = DEFAULT_PLAYER_HEALTH;
volatile uint8_t brightness = 0; // brightness display
volatile unsigned int counter = 0;
volatile uint8_t lw = 220 / AANTALLENGTEBREEDTE; // TEKENEN VAN BREEDTE VAN EEN VAKJE
volatile uint8_t aantal_geplaatste_bommen = 0;
volatile uint8_t player1_locatie;
volatile uint8_t player2_locatie;
volatile uint8_t tile_array[(WIDTH_MAP * HEIGHT_MAP)]; // bevat players, boxes, muren, bommen, vuur
volatile uint8_t bomb_placed = 0;
volatile uint8_t livesleft1 = 3; //REMOVE Toegevoegd
volatile uint8_t livesleft2 = 3;


// use hardware SPI (on Uno, #13, #12, #11) and #10 and #9 for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


// function prototypes
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
	game_init();

	/* loop */
	for(;;) {
		Nunchuk.getState(ADDRESS); // retrieve states joystick and buttons Nunchuk

		if (1 == state) { // TIMER1_COMPA_vect
			state = 0; // 1 keer uitvoeren na interrupt
			clearDraw(tile_to_coords_x(player1_locatie), tile_to_coords_y(player1_locatie)); // haal speler weg huidige locatie
			clearDraw(tile_to_coords_x(player2_locatie), tile_to_coords_y(player2_locatie)); // haal speler weg huidige locatie
			move(); // pas nunchuk toe
			item_updating(); // animaties, en cycle door item states (bomb, fire)
			draw_screen(); // teken players opnieuw
		}
		if (2 == state) { // TIMER1_COMPB_vect
			state = 0; // 1 keer uitvoeren na interrupt
			item_updating(); // animaties, en cycle door item states (bomb, fire)
		}
	}

	/* never reached */
	return 0;
}


// globale initialisatie functie (ter vervanging van "init")
void game_init(void) {
	init(); // onzichtbare functie
	timer0_init();
	timer1_init(); // gameticks
	init_map(); // map vullen met players, muren, boxes, etc.
	screen_init();
	Wire.begin(); // enable TWI communication
	nunchuk_init(); // start communication between Nunchuk and Arduino
//	USART_Init();

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
	 * ? : analog 2
	 * Nunchuck : analog 4, 5
	 */

	// enable global interrupts
	sei();
}


void screen_init(void) {
	DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5); // TFT scherm

	tft.begin(); // enable SPI communication
	tft.setRotation(3); // rotate screen

	// screen is 240 x 320
	tft.fillScreen(LIGHTBROWN);

//	drawHeartLeft();
//	drawHeartRight();
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
//	drawPlayer1(8, 0);
//      drawPlayer2(0, 8);
//	drawBomb(4, 2);
}


void draw_screen(void) {
	// screen is 240 x 320
//	tft.fillScreen(LIGHTBROWN);

//	tft.fillRect(XUP, YUP, AANTALLENGTEBREEDTE * lw, AANTALLENGTEBREEDTE * lw, DARKBROWN);
//	drawGrid();
//      drawPlayer1(8, 0);
//      drawPlayer2(0, 8);
//	drawBomb(4, 2);
//	drawPlayer1(player1_x, player1_y);
//	drawPlayer2(player2_x, player2_y);
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
		player1_health--;
		if (fire_type >= FIRE_TILE_1S && fire_type <= FIRE_TILE_1E) { // is het friendly-fire?
			// speler is door eigen bom geraakt
			// score toepassen
		} else {
			// speler is geraakt door bom van tegenstander
			// score toepassen
		}
		if (player1_health <= 0) {
			// player 2 wins
		}
	} else if (PLAYER == 2) {
		player2_health--;
		if (fire_type >= FIRE_TILE_2S && fire_type <= FIRE_TILE_2E) { // is het friendly-fire?
			// speler is door eigen bom geraakt
			// score toepassen
		} else {
			// speler is geraakt door bom van tegenstander
			// score toepassen
		}
		if (player2_health <= 0) {
			// player 1 wins
		}
	}
}


// bewegingsfunctie voor de player die wordt gespeeld (1/2)
void move(void) {
	// kan maar 1 kant op bewegen per keer, zolang er niks in de weg staat en player niet van de map afgaat
	if (Nunchuk.X_Axis() == 255) { // 1 naar rechts
        	if (tile_to_coords_x(player1_locatie) < BORDERRIGHTSIDE // als player niet van map afgaat
		&& (tile_is_leeg(1 + player1_locatie) // en als er niks in de weg staat, of
		|| tile_bevat_vuur(1 + player1_locatie))) { // ..als er vuur in de weg staat
			tile_array[player1_locatie] = EMPTY_TILE;
			bomb_placing(); // check of er een bomb geplaatst moet worden
                	player1_locatie++;
			if (tile_bevat_vuur(player1_locatie)) { damage_player(tile_array[player1_locatie]); } // als player1_locatie nu vuur bevat, damage player
			tile_array[player1_locatie] = PLAYER1_TILE;
        	}
	} else if (Nunchuk.X_Axis() == 0) { // 1 naar links
        	if (tile_to_coords_x(player1_locatie) > BORDERLEFTSIDE // als player niet van map afgaat
		&& (tile_is_leeg(-1 + player1_locatie) // en als er niks in de weg staat, of
		|| tile_bevat_vuur(-1 + player1_locatie))) { // ..als er vuur in de weg staat
			tile_array[player1_locatie] = EMPTY_TILE;
			bomb_placing(); // check of er een bomb geplaatst moet worden
                	player1_locatie--;
			if (tile_bevat_vuur(player1_locatie)) { damage_player(tile_array[player1_locatie]); } // als player1_locatie nu vuur bevat, damage player
			tile_array[player1_locatie] = PLAYER1_TILE;
        	}
	} else if (Nunchuk.Y_Axis() == 255) { // 1 omhoog
                if (tile_to_coords_y(player1_locatie) > BORDERUP // als player niet van map afgaat
		&& (tile_is_leeg(-WIDTH_MAP + player1_locatie) // en als er niks in de weg staat, of
		|| tile_bevat_vuur(-WIDTH_MAP + player1_locatie))) { // ..als er vuur in de weg staat
			tile_array[player1_locatie] = EMPTY_TILE;
			bomb_placing(); // check of er een bomb geplaatst moet worden
                        player1_locatie -= WIDTH_MAP;
			if (tile_bevat_vuur(player1_locatie)) { damage_player(tile_array[player1_locatie]); } // als player1_locatie nu vuur bevat, damage player
			tile_array[player1_locatie] = PLAYER1_TILE;
                }
        } else if (Nunchuk.Y_Axis() == 0) { // 1 omlaag
                if (tile_to_coords_y(player1_locatie) < BORDERDOWN // als player niet van map afgaat
		&& (tile_is_leeg(WIDTH_MAP + player1_locatie) // en als er niks in de weg staat, of
		|| tile_bevat_vuur(WIDTH_MAP + player1_locatie))) { // ..als er vuur in de weg staat
			tile_array[player1_locatie] = EMPTY_TILE;
			bomb_placing(); // check of er een bomb geplaatst moet worden
                        player1_locatie += WIDTH_MAP;
			if (tile_bevat_vuur(player1_locatie)) { damage_player(tile_array[player1_locatie]); } // als player1_locatie nu vuur bevat, damage player
			tile_array[player1_locatie] = PLAYER1_TILE;
                }
        }
	if (Nunchuk.Z_Button() == 1) { // als bomb button is ingedrukt
		bomb_placed = 1; // bij volgende move(), leg een bomb neer
	}
}


// plaats bom als button was ingedrukt, vervangt huidige locatie player met een bom
void bomb_placing(void) {
	if (bomb_placed == 1 && aantal_geplaatste_bommen < MAX_BOMBS) {
		tile_array[player1_locatie] =
		#if PLAYER == 1
		BOMB_TILE_1S
		#elif PLAYER == 2
		BOMB_TILE_2S
		#endif
		; // plaats bom van huidige speler
		drawBomb(tile_to_coords_x(player1_locatie), tile_to_coords_y(player1_locatie)); // tijdelijk
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
		}
		if (tile_bevat_bomb(i) == PLAYER2_TILE) { // player 2 bom
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
		}
		if (tile_bevat_vuur(i) == PLAYER1_TILE) {
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
		}
		if (tile_bevat_vuur(i) == PLAYER2_TILE) {
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
		}
    }
}


// voor tekenen en genereren explosie met FIRE_TILEs
void bomb_explode(uint8_t tile) {
	uint8_t te_tekenen_tile;

	// bepaal van welke speler de bom is
	if (tile_bevat_bomb(tile) == PLAYER1_TILE) { // bom is van player 1
		te_tekenen_tile = FIRE_TILE_1S; // teken vuur van player 1
		aantal_geplaatste_bommen--;
	} else if (tile_bevat_bomb(tile) == PLAYER2_TILE) { // bom is van player 2
		te_tekenen_tile = FIRE_TILE_2S; // teken vuur van player 2
	} else { // meegekregen tile is geen bomb
		return;
	}

	fire_placing(tile, te_tekenen_tile, TRUE); // vervang bom door vuur

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
	drawHeart(15, 20, 20, 18); //teken hartje
	if(livesleft1 >= 2) {
		drawHeart(15, 40, 20, 18); //als 2 levens, teken 2e hartje
	}if(livesleft1 == 3) {
		drawHeart(15, 60, 20, 18); //als 3 levens, teken 3e hartje
	}
}


void drawPlayer2Field() {
	tft.fillRect(280, 155, 30, 70, ILI9341_BLACK);
	drawHeart(285, 200, 20, 18); //teken hartje
	if(livesleft2 >= 2) {
		drawHeart(285, 180, 20, 18); //als 2 levens, teken 2e hartje
	} if(livesleft2 == 3) {
		drawHeart(285, 160, 20, 18); //als 3 levens, teken 3e hartje
	}
}


// vervang getekende vakje met een leeg vakje
void clearDraw(uint8_t x, uint8_t y) {
	uint8_t switch_value = x;
	x = y;
	y = switch_value;
//	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
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
/*	tft.fillRect(x*lw + XUP + OBJOFFSET + 6.5, (y*lw) + YUP + OBJOFFSET + 10, lw - 2*OBJOFFSET - 12 , lw - 2*OBJOFFSET - 20 , ILI9341_BLACK); // pant
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // left leg
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 15, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 13, ILI9341_BLACK); // right leg
	/* Shoes */
/*	tft.fillRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 16, lw - 2*OBJOFFSET - 18, PLAYER1); // left shoe
	tft.fillRect(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 20, lw - 2*OBJOFFSET - 16, lw - 2*OBJOFFSET - 18, PLAYER1); // right shoe	
	/* Body  */
/*	tft.fillRect(x*lw + XUP + OBJOFFSET + 7.5, (y*lw) + YUP + OBJOFFSET + 6, lw - 2*OBJOFFSET - 14 , lw - 2*OBJOFFSET - 12, PLAYER1); // chest 
	tft.fillRect(x*lw + XUP + OBJOFFSET + 3, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 18 , lw - 2*OBJOFFSET - 14, PLAYER1); // left arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 4, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, PLAYER1); // left shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 2, (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, SKIN);// left hand
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 18 , lw - 2*OBJOFFSET - 14, PLAYER1); // right arm
	tft.fillRect(x*lw + XUP + OBJOFFSET + 13, (y*lw) + YUP + OBJOFFSET + 8, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, PLAYER1); // right shoulder
	tft.fillRect(x*lw + XUP + OBJOFFSET + 14, (y*lw) + YUP + OBJOFFSET + 13, lw - 2*OBJOFFSET - 17 , lw - 2*OBJOFFSET - 17, SKIN);// right hand	
	/* Head */
/*	tft.fillCircle(x*lw + XUP + (0.3*lw) + 5, y*lw + YUP + (0.3*lw) - 1 , 5, SKIN); // head
	/* Face */
/*	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // left eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 7, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // left eye white
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 18, lw - 2*OBJOFFSET - 18, ILI9341_BLACK); // right eye
	tft.fillRect(x*lw + XUP + OBJOFFSET + 12, (y*lw) + YUP + OBJOFFSET + 4, lw - 2*OBJOFFSET - 19, lw - 2*OBJOFFSET - 19, ILI9341_WHITE); // right eye white
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 10, (y*lw) + YUP + OBJOFFSET + 8, ILI9341_BLACK);// mouth
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 11, (y*lw) + YUP + OBJOFFSET + 7, ILI9341_BLACK);
	tft.drawPixel(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET + 8, ILI9341_BLACK);
	/* Hat  */
/*	tft.fillRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET - 2, lw - 2*OBJOFFSET -10 , lw - 2*OBJOFFSET - 16, PLAYER1); // main hat
	tft.drawRect(x*lw + XUP + OBJOFFSET + 5, (y*lw) + YUP + OBJOFFSET - 2, lw - 2*OBJOFFSET -10 , lw - 2*OBJOFFSET - 16, ILI9341_BLACK);
	tft.fillRect(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET , lw - 2*OBJOFFSET -12 , lw - 2*OBJOFFSET - 17, PLAYER1); // brim
	tft.drawRect(x*lw + XUP + OBJOFFSET + 9, (y*lw) + YUP + OBJOFFSET , lw - 2*OBJOFFSET -12 , lw - 2*OBJOFFSET - 17, ILI9341_BLACK);
*/

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
	uint8_t switch_value = x;
	x = y;
	y = switch_value;
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
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // ADC clock prescaler ...(nog kiezen)

	ADCSRA |= (1<<ADATE); // ADC auto trigger enable \/
	ADCSRB &= ~(1 << ADTS2) & ~(1 << ADTS1) & ~(1 << ADTS0); // free running mode

	ADCSRA |= (1 << ADEN); // enable ADC
	ADCSRA |= (1 << ADSC); // start eerste meting
}

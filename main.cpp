// defines
#define PLAYER 1 		// 1/2
#define ADDRESS 0x52 		// nunchuk adres
#define GAMETICK_FREQUENCY 1 	// gameticks in HZ, max 0,119HZ, min 7812,5HZ
#define FCLK 16000000 		// arduino clock frequency
#define PRESCALER_TIMER1 1024 	// prescaler, zie ook functie timer1_init()
#define OFFSET_VAKJE 24 	// breedte & hoogte van een vakje
#define OFFSET_PLAYER_X 12 	// offset waarop player in vakje zit X
#define OFFSET_PLAYER_Y 20 	// offset waarop player in vakje zit Y
#define BAUD 9600 		// baudrate USART
#define TFT_DC 9 		// initialisatie LCD
#define TFT_CS 10 		// initialisatie LCD
#define AANTALLENGTEBREEDTE 9 	//aantal hokjes in lengte en breedte
#define LIGHTBROWN 0x7A00 	// voor tekenen kleur
#define DARKBROWN 0x5980 	// voor tekenen kleur
#define XUP 10 			// voor tekenen
#define YUP 50 			// voor tekenen
#define OBJOFFSET 2 		// voor tekenen
#define MAXOBJ 8 		// voor tekenen
#define TRUE 1
#define FALSE 0

#define BORDERLEFTSIDE 0 	// min X
#define BORDERRIGHTSIDE 8 	// max X
#define WIDTH_MAP (BORDERRIGHTSIDE + 1)
#define BORDERUP 0 		// max Y
#define BORDERDOWN 8 		// min Y
#define HEIGHT_MAP (BORDERDOWN + 1)
#define FIRE_SPREADING 2	// geeft aan hoeveel vakken vuur moet bevatten vanuit de locatie van de bom
#define MAX_BOMBS 2		// geeft maximaal aantal bommen aan dat iedere player mag plaatsen
#define DEFAULT_PLAYER_HEALTH 3

// defines - colors
#define WALL 0X6B8E 		// kleur voor de muren

// defines - tile states
#define BOMB_TILE_1S 10 			// player1 bom startwaarde, onderscheid voor bepalen score
#define BOMB_TILE_1E (BOMB_TILE_1S + 8) 	// player1 bom eindwaarde, bepaalt na welke tijd bom afgaat
#define BOMB_TILE_2S 20 			// player2 bom startwaarde, onderscheid voor bepalen score
#define BOMB_TILE_2E (BOMB_TILE_2S + 8) 	// player2 bom eindwaarde, bepaalt na welke tijd bom afgaat
#define FIRE_TILE_1S 30 			// player1 vuur startwaarde, onderscheid voor bepalen score
#define FIRE_TILE_1E (FIRE_TILE_1S + 4) 	// player1 vuur eindwaarde, bepaalt hoe lang fire blijft staan
#define FIRE_TILE_2S 40 			// player2 vuur startwaarde, onderscheid voor bepalen score
#define FIRE_TILE_2E (FIRE_TILE_2S + 4)  	// player2 vuur eindwaarde, bepaalt hoe lang fire blijft staan
#define EMPTY_TILE 9            		// locatie in array is leeg, >0
#define PLAYER1_TILE 1          		// locatie in array bevat player 1, >0
#define PLAYER2_TILE 2          		// locatie in array bevat player 2, >0
#define TON_TILE 3              		// locatie in array bevat box, >0
#define WALL_TILE 4             		// locatie in array bevat muur, >0
//#define BOMB_TILE 5             		// locatie in array bevat bom, >0
//#define FIRE_TILE 6             		// locatie in array bevat vuur (van explosie), >0

// defines - animations
#define BOMB_FRAMES 2				// aantal frames van de animatie, handmatig toevoegen bij drawBomb()
#define FIRE_FRAMES 2				// aantal frames van de animatie, handmatig toevoegen bij drawFire()

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


// use hardware SPI (on Uno, #13, #12, #11) and #10 and #9 for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


// function prototypes
void nunchuk_init();
void move(void);
void drawGrid();
void drawHeartLeft();
void drawHeartRight();
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
	USART_Init();

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

        drawHeartLeft();
        drawHeartRight();
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
		if (fire_placing(tile-(i*WIDTH_MAP), te_tekenen_tile, FALSE)) { // plaats vuur
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
		if (fire_placing(tile-i, te_tekenen_tile, FALSE)) { // plaats vuur
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
//			tile_array[tile] = fire_type;
			tile_array[tile] = FIRE_TILE_1S;
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


// vervang getekende vakje met een leeg hokje
void clearDraw(uint8_t x, uint8_t y) {
	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
//	tft.fillRect((x * lw) + XUP + OBJOFFSET, (y * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, DARKBROWN);
	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, DARKBROWN);
}


// voor tekenen player 1
void drawPlayer1(uint8_t x, uint8_t y) {
	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
//	tft.fillRect((x * lw) + XUP + OBJOFFSET, (y * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_CYAN);
	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_CYAN);
}


// voor tekenen player 2
void drawPlayer2(uint8_t x, uint8_t y) {
	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
//	tft.fillRect((x * lw) + XUP + OBJOFFSET, (y * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_RED);
	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_RED);
}


// voor tekenen muren (in het midden)
void drawWall(uint8_t x, uint8_t y) {
	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, WALL);
}


// voor tekenen vuur
void drawFire(uint8_t x, uint8_t y) {
	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_ORANGE);
}


// voor tekenen bom
void drawBomb(uint8_t x, uint8_t y) {
	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
//	tft.fillCircle(x * lw + XUP + (0.3 * lw), y * lw + YUP + (0.3 * lw), 5, ILI9341_BLACK);
	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_PURPLE);
}


// voor tekenen ton
void drawTon(uint8_t x, uint8_t y) {
	y = BORDERRIGHTSIDE - y; // snelle fix omdraaien x-as
	tft.fillRect((y * lw) + XUP + OBJOFFSET, (x * lw) + YUP + OBJOFFSET, lw - 2 * OBJOFFSET + 1, lw - 2 * OBJOFFSET + 1, ILI9341_BLUE);
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

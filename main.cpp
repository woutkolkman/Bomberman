
#include "libraries/IR/ir.h" // IR library
#include "config.h"
#include "functions/drawfunctions.cpp"
void init(void);

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
		ir_check_input(); // pas IR ontvangen informatie toe wanneer beschikbaar

		if (screenState == 2) { // is start button is pressed
			selectButtonFlag = 0; // reset flag, op deze manier blijft functionaliteit mainmenu uit
			if (1 == state) { // TIMER1_COMPA_vect
				state = 0; // 1 keer uitvoeren na interrupt
				if(livesleft1 == 0 || livesleft2 == 0) {
	                                if(counttomain == TOMAINMENULENGTH) {
	                                        screenState = 0;
        	                                drawMainMenu();
						selectButtonFlag = 1;
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
				if(livesleft1 && livesleft2) {
					state = 0; // 1 keer uitvoeren na interrupt
					item_updating(); // animaties, en cycle door item states (bomb, fire)
				}
			}
    		}

    		if (selectButtonFlag == 1) {		// in main menu knoppen kunnen selecteren
       			selectButton();					// in het begin staat flag altijd op 1, als spel bezig is op 0
    		}

		if (screenState == 0) {
            if(mainmenuselect != mainmenuselected) {// aan het begin van het spel staat screenState op 0 om menuopties weer te geven
                drawStartButton();
                drawHighScoreButton();
                drawQuitButton();
                mainmenuselected = mainmenuselect;
            }
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


// globale initialisatie functie (ter vervanging van "init")
void game_init(void) {
	IR_prepare(FREQUENCY); // init IR

	init(); // onzichtbare functie
	timer0_init();
	timer1_init(); // gameticks
	init_map(); // map vullen met players, muren, boxes, etc.
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
		displayWinMessage();
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
		livesleft1 = data; // update health player 1
		drawPlayer1Field(); // teken hartjes
	} else if (kopie == UPDATE_HEALTH2_CODE) {
		livesleft2 = data; // update health player 2
		drawPlayer2Field(); // teken hartjes
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


void clearScreen() {
	if (screenState == 2) { // if start button is pressed
		init_map(); // start map
		screen_init();
	} else if (screenState == 1) { // if quit button is pressed
		quitScreen;
		selectButtonFlag = 0;
	}
}


// haal getekende vakje weg en reset tile in tile_array
void clear_tile(uint8_t tile) {
	tile_array[tile] = EMPTY_TILE;
	clearDraw(tile_to_coords_x(tile), tile_to_coords_y(tile));
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
		ir_verzenden(UPDATE_HEALTH1_CODE, livesleft1);
		if (livesleft1 <= 0) {
//			if(PLAYER == 1) {
			displayLoseMessage(); //player 1 lose
			ir_verzenden(LOST_CODE, 0x00); // transmit lose ir
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
		ir_verzenden(UPDATE_HEALTH2_CODE, livesleft2);
		if (livesleft2 <= 0) {
//			if(PLAYER == 1) {
//                                displayWinMessage(); //player 1 wins
//                        } else {
                	displayLoseMessage(); //player 2 loses
			ir_verzenden(LOST_CODE, 0x00); // transmit lose ir
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
//		} else if (tile == PLAYER1_TILE) {
//			// update player1 als PLAYER == 2, teken player1 op player1_locatie
//		} else if (tile == PLAYER2_TILE) {
//			// update player2 als PLAYER == 1, teken player2 op player2_locatie
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

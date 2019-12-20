/* Defines */
#define PLAYER 1                                // 1/2
#if PLAYER == 1                                 // player-specifieke define settings
#define FREQUENCY 38                            // 38/56, geef frequentie aan IR LED
#elif PLAYER == 2
#define FREQUENCY 56                            // 38/56, geef frequentie aan IR LED
#endif

//#define ADC_FREERUNNING                       // als dit defined is werkt de ADC op freerunning
//#define ADC_WAIT                              // als dit defined is wacht de processor totdat de ADC conversie klaar is
#define VAR_TYPE_IR uint16_t                     // variabele type voor IR communicatie
#define ADDRESS 0x52                            // nunchuk adres
#define GAMETICK_FREQUENCY 1                    // gameticks in HZ, max 0,119HZ, min 7812,5HZ
#define FCLK 16000000                           // arduino clock frequency
#define PRESCALER_TIMER1 1024                   // prescaler, zie ook functie timer1_init()
#define OFFSET_VAKJE 24                         // breedte & hoogte van een vakje
#define OFFSET_PLAYER_X 12                      // offset waarop player in vakje zit X
#define OFFSET_PLAYER_Y 20                      // offset waarop player in vakje zit Y
#define TFT_DC 9                                // initialisatie LCD
#define TFT_CS 10                               // initialisatie LCD
#define AANTALLENGTEBREEDTE WIDTH_MAP           // aantal hokjes in lengte en breedte
#define LIGHTBROWN 0x7A00                       // voor tekenen kleur
#define DARKBROWN 0x5980                        // voor tekenen kleur
#define XUP 50  // 10                           // voor tekenen
#define YUP 10  // 50                           // voor tekenen
#define OBJOFFSET 2                             // voor tekenen
#define MAXOBJ 8                                // voor tekenen
#define TRUE 1
#define FALSE 0
#define TOMAINMENULENGTH 20                     //tijd (in gameticks) hoelang het duurt voor mainmenu wordt getoond na einde spel

#define BORDERLEFTSIDE 0                        // min X
#define BORDERRIGHTSIDE 8                       // max X
#define WIDTH_MAP (BORDERRIGHTSIDE + 1)
#define BORDERUP 0                              // max Y
#define BORDERDOWN 8                            // min Y
#define HEIGHT_MAP (BORDERDOWN + 1)
#define FIRE_SPREADING 2                        // geeft aan hoeveel vakken vuur moet bevatten vanuit de locatie van de bom
#define MAX_BOMBS 2                             // geeft maximaal aantal bommen aan dat iedere player mag plaatsen
#define AANTALLENGTEBREEDTE WIDTH_MAP           // aantal hokjes in lengte en breedte
#define DEFAULT_PLAYER_HEALTH 3

// win/lose messages
#define POSITIONX 109                           // message posititon schaduw tekst x
#define POSITIONY 115                           // message posititon schaduw tekst y
#define POSITIONX2 POSITIONX + 2                // message position tekst x
#define POSITIONY2 POSITIONY - 2                // message position tekst y
#define POSITIONRX 75
#define POSITIONRX 75                           // message rechtangle position x
#define POSITIONRY 83                           // message rechtangle position y
#define POSITIONRW 167                          // message rechtangle width
#define POSITIONRH 72                           // message rechtangle heigth
#define YOULOSEMESSAGE ILI9341_RED
#define YOUWINMESSAGE 0x5623
#define YOUWINSHADOW 0x52A9
#define POSITION 120

// defines - colors
#define WALL 0X6B8E             // kleur voor de muren
#define PLAYER1 0x135F          // kleuren van de spelers
#define PLAYER2 0xD9E7
#define SKIN 0xF5D0
#define HEARTCOLOUR ILI9341_RED // kleur voor hartjes
#define GRIDCOLOUR DARKBROWN    // kleur van de gridachtergrond
#define LONT2 0xDC29            // kleur van de lont van de bom
#define FIRE 0xF9E1             // kleur van het vuur van de bom
#define TONBROWN 0x28A0         // kleur van de tonnen

// defines - tile states
#define BOMB_TILE_1S 10                         // player1 bom startwaarde, onderscheid voor bepalen score, >0
#define BOMB_TILE_1E (BOMB_TILE_1S + 12)        // player1 bom eindwaarde, bepaalt na welke tijd bom afgaat, >=BOMB_TILE_1S
#define BOMB_TILE_2S 25                         // player2 bom startwaarde, onderscheid voor bepalen score, >0
#define BOMB_TILE_2E (BOMB_TILE_2S + 12)        // player2 bom eindwaarde, bepaalt na welke tijd bom afgaat, >=BOMB_TILE_2S
#define FIRE_TILE_1S 40                         // player1 vuur startwaarde, onderscheid voor bepalen score, >0
#define FIRE_TILE_1E (FIRE_TILE_1S + 5)         // player1 vuur eindwaarde, bepaalt hoe lang fire blijft staan, >=FIRE_TILE_1S
#define FIRE_TILE_2S 50                         // player2 vuur startwaarde, onderscheid voor bepalen score, >0
#define FIRE_TILE_2E (FIRE_TILE_2S + 5)         // player2 vuur eindwaarde, bepaalt hoe lang fire blijft staan, >=FIRE_TILE_2S
#define EMPTY_TILE 9                            // locatie in array is leeg, >0
#define PLAYER1_TILE 1                          // locatie in array bevat player 1, >0
#define PLAYER2_TILE 2                          // locatie in array bevat player 2, >0
#define TON_TILE 3                              // locatie in array bevat box, >0
#define WALL_TILE 4                             // locatie in array bevat muur, >0
#if PLAYER == 1
#define PLAYER_TILE PLAYER1_TILE
#elif PLAYER == 2
#define PLAYER_TILE PLAYER2_TILE
#endif

// defines - animations
#define BOMB_FRAMES 2                           // aantal frames van de animatie, handmatig toevoegen bij drawBomb(), >0, waarde begint bij 1
#define FIRE_FRAMES 2                           // aantal frames van de animatie, handmatig toevoegen bij drawFire(), >0, waarde begint bij 1

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
volatile uint8_t state = 0; // states om interrupts in de main te laten uitrekenen, 0 = doe niks
volatile uint8_t brightness = 0; // brightness display
volatile unsigned int counter = 0;
volatile uint8_t aantal_geplaatste_bommen = 0;
volatile uint8_t player1_locatie;
volatile uint8_t player2_locatie;
volatile uint8_t tile_array[(WIDTH_MAP * HEIGHT_MAP)]; // bevat players, boxes, muren, bommen, vuur
volatile uint8_t bomb_placed = 0;
volatile uint8_t mainmenuselected;
volatile uint8_t counttomain = 0; //when losing or winning, wait 5 seconds (or 5 gameticks) to return to main menu

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

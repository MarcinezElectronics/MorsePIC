#ifndef MORSE_H
#define MORSE_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "sys_time.h"
#include "i2c_lcd.h"

/*
 * Morse kódolás:
 * "ti" hossza: 1200ms/WPM (Words per Minute) 
 * "tá" hossza: 3 * "ti"
 * Sebesség (WPM)       Egy ti (rövid) hossza	Egy tá (hosszú) hossza	Mit jelent a gyakorlatban?
 * 5  WPM (kezd?)       240 ms (0,24 mp)        720 ms (0,72 mp)        Nagyon lassú, kényelmesen számolható tempó.
 * 12 WPM (alapfok)     100 ms (0,1 mp)         300 ms (0,3 mp)         Itt már kezd összeállni a ritmus.
 * 20 WPM (rádióamat?r)	60 ms (0,06 mp)         180 ms (0,18 mp)        Tempós adás, a fül már nem külön jeleket, hanem dallamot hall.
 * 40 WPM (profi)       30 ms (0,03 mp)         90 ms (0,09 mp)         Rendkívül gyors, gépi adáshoz közeli sebesség.
 */

// --- Morse beállítások ---
#define MAX_MORSE_BUF 8
#define CHAR_TIMEOUT_MS 350 // Ennyi tétlenség után dekódolja a bet?t
#define WORD_TIMEOUT_MS 2100
//#define WORD_TIMEOUT_MS 1050  // Ennyi tétlenség után szóköz kerül az alsó sorba (7 egység)

// --- Globálisan elérhet? állapotváltozók (extern-nel deklarálva) ---
extern uint32_t last_input_time;
extern bool waiting_for_timeout;
extern uint8_t cursor_col;
extern bool space_added;      // Jelzi, hogy az adott szünetben már adtunk-e hozzá szóközt

// --- Publikus függvények prototípusai ---

// Dekódoló függvény
char decode_morse(const char *code);
// Morse pufferhez jel hozzáadása
void add_morse_symbol(char symbol);
// Bet? lezárása és kiírása az alsó sorba
void process_morse_completion();
// Szóköz beszúrása az alsó sorba
void process_word_space(void);

#endif
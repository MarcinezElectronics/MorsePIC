#include "morse.h"

// --- Bels? állapotváltozók (static = csak ebben a .c fájlban láthatóak) ---
static char morse_buffer[MAX_MORSE_BUF] = "";   // Aktuális jelek pl: ".-"
static uint8_t morse_len = 0;

// --- Globális változók tényleges memóriafoglalása ---
uint32_t last_input_time = 0;
bool waiting_for_timeout = false;
uint8_t cursor_col = 0; // Kijelz? oszlop pozíciója (0..15)
bool space_added = false;

// Morse FA struktúra / lookup tábla (Standard ITU Morse)
typedef struct {
    const char *code;
    char letter;
} MorseMap;

//static-al a flashbe teszi, így több RAM marad
static const MorseMap morse_table[] = {
    {".-", 'A'},   {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'},  {".", 'E'},
    {"..-.", 'F'}, {"--.", 'G'},  {"....", 'H'}, {"..", 'I'},   {".---", 'J'},
    {"-.-", 'K'},  {".-..", 'L'}, {"--", 'M'},   {"-.", 'N'},   {"---", 'O'},
    {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'},  {"...", 'S'},  {"-", 'T'},
    {"..-", 'U'},  {"...-", 'V'}, {".--", 'W'},  {"-..-", 'X'}, {"-.--", 'Y'},
    {"--..", 'Z'},
    // ...
    {".--.-", 0}, //Á
    {"..-..", 1}, // É
    {"---.", 2},  // Ö / ?
    {"..--", 3},  // Ü / ?
    // ...
    {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'}, {"....-", '4'},
    {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'},
    {NULL, '?'} // Ismeretlen jelhez
};

// Dekódoló függvény
char decode_morse(const char *code) {
    for (int i = 0; morse_table[i].code != NULL; i++) {
        if (strcmp(morse_table[i].code, code) == 0) {
            return morse_table[i].letter;
        }
    }
    return '?'; // Ha érvénytelen a kombináció
}

// Új szimbólum hozzáadásakor töröljük a szóköz-flaget
void add_morse_symbol(char symbol) {
    space_added = false; // Új gombnyomás történt, nullázzuk a szóköz jelz?t
    
    if (cursor_col >= 16) {
        LCD_Clear();
        cursor_col = 0;
    }

    if (morse_len < (MAX_MORSE_BUF - 1)) {
        morse_buffer[morse_len++] = symbol;
        morse_buffer[morse_len] = '\0';
        
        LCD_SetCursor(0, 0);
        LCD_String(morse_buffer);
        
        last_input_time = millis();
        waiting_for_timeout = true;
    }
}

// Szóköz beszúrása az alsó sorba
void process_word_space(void) {
    if (!space_added && cursor_col < 16) {
        // 1. Az el?z? karakter után lév? '_' jelet felülírjuk egy sima szóközre (' ')
        LCD_SetCursor(1, cursor_col);
        LCD_Char(' ');
        
        // 2. Oszlop léptetése a szóköz miatt
        cursor_col++;
        space_added = true;
        
        // 3. Az új pozícióra kitesszük a szóköz utáni '_' jelet
        if (cursor_col < 16) {
            LCD_SetCursor(1, cursor_col);
            LCD_Char('_');
        }
        
        // 4. Kurzor visszaállítása a fels? sor elejére
        LCD_SetCursor(0, 0);
    }
}

void process_morse_completion(void) {
    if (morse_len > 0) {
        char decoded_char = decode_morse(morse_buffer);
        
        // 1. Alsó sorba írjuk a dekódolt bet?t az aktuális pozícióra
        LCD_SetCursor(1, cursor_col);
        LCD_Char(decoded_char);
        
        // 2. Fels? sor törlése (a gépelt jelek eltüntetése)
        LCD_SetCursor(0, 0);
        for (int i = 0; i < morse_len; i++) {
            LCD_Char(' ');
        }
        
        // 3. Léptetjük a kurzorszámlálót
        cursor_col++;
        
        // 4. ALSÓ SOR KARAKTER-SZÜNET JELZÉS: Kirakjuk az '_' jelet a bet? MÖGÉ
        if (cursor_col < 16) {
            LCD_SetCursor(1, cursor_col);
            LCD_Char('_');
        }
        
        // 5. Puffer ürítése
        morse_buffer[0] = '\0';
        morse_len = 0;
        waiting_for_timeout = false;

        // 6. A hardveres kurzor visszaugrása a fels? sor elejére (0, 0)
        LCD_SetCursor(0, 0);
    }
}
#include "mcc_generated_files/mcc.h"
#include "sys_time.h"
#include "button.h"
#include "i2c_lcd.h"
#include "morse.h"

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    LCD_Init();
    // Töltsük be a mátrixokat a CGRAM 0..3 indexeire
    LCD_CreateChar(0, char_A_ekezet);
    LCD_CreateChar(1, char_E_ekezet);
    LCD_CreateChar(2, char_O_ekezet);
    LCD_CreateChar(3, char_U_ekezet);
    
    LCD_Clear();
    LCD_Command(LCD_CURSOR_BLINK_ON);

    // Id?zít? és gomb objektumok C99 szintaxissal
    Timer blink_timer = timer_create(500);
    timer_start(&blink_timer, 500);

    // Aktív LOW gomb (Internal/External Pull-up), 50 ms prellmentesítés, 1000 ms hosszú id?
    Button btn1 = button_create(true, 50, 180);

    while (1) {
        // --- 1. Gomb frissítése ---
        button_update(&btn1, PORTCbits.RC4);

        // Ha a gomb éppen nyomva van, folyamatosan frissítjük az id?zít?t,
        // így a szünet-id?zít? csak az ELENGEDÉSKOR kezd el ténylegesen ketyegni!
        bool is_pressed = btn1.active_low ? (btn1.debounced_state == 0) : (btn1.debounced_state == 1);
        
         // --- CSIPOGÓ (Buzzer) KEZELÉSE ---
        // A csipogó (LATA2) addig szól, amíg a gomb fizikai nyomva tartása tart!
        LATAbits.LATA2 = is_pressed;
        
        if (is_pressed && waiting_for_timeout) {
          last_input_time = millis();
        }

        // Rövid gombnyomás (elengedéskor) -> PONT (.)
        if (button_was_clicked(&btn1)) {
            add_morse_symbol('.');
        }

        // Hosszú gombnyomás (amikor eléri az 1000 ms-ot) -> KÖT?JEL (-)
        if (button_was_long_pressed(&btn1)) {
            add_morse_symbol('-');
        }

        // --- 2. ID?ZÍT?K (Csak ha a gomb el van engedve) ---
        if (!is_pressed) {
            uint32_t idle_time = millis() - last_input_time;

        // A) Karakter lezárási id?zít? (350 ms szünet után bet? dekódolása)
        if (waiting_for_timeout && (idle_time >= CHAR_TIMEOUT_MS)) {
            process_morse_completion();
            }

        // B) Szóköz beszúrási id?zít? (1050 ms szünet után szóköz az alsó sorba)
        if (!waiting_for_timeout && !space_added && (idle_time >= WORD_TIMEOUT_MS)) {
            process_word_space();
            }
        }

        // --- 3. Egyéb feladatok ---
        if (timer_check_and_reset(&blink_timer)) {
            LATAbits.LATA5 = !LATAbits.LATA5;           
        }
    }
}
#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t pin_state;          // Jelenlegi nyers állapot
    uint8_t debounced_state;    // Sz?rt, pergésmentes állapot
    uint32_t last_debounce_time;// Utolsó állapotváltás ideje (ms)
    uint32_t press_start_time;  // Gombnyomás kezdete (ms)
    bool pressed_event;         // Egyszeri kattintás esemény
    bool long_pressed_event;    // Hosszú nyomás esemény
    bool long_press_handled;    // Kezelve lett-e a hosszú nyomás
    uint16_t debounce_delay_ms; // Debounce id? (pl. 50 ms)
    uint16_t long_press_ms;     // Hosszú nyomás küszöb (pl. 1000 ms)
    bool active_low;            // true ha PULL-UP (0 = megnyomva)
} Button;

// Gomb inicializálása C99 compound literal segítségével
Button button_create(bool active_low, uint16_t debounce_ms, uint16_t long_press_ms);

// Ezt kell hívni folyamatosan a while(1)-ben
void button_update(Button *btn, uint8_t raw_pin_value);

// Esemény lekérdez?k (kiolvasáskor automatikusan törl?dnek)
bool button_is_pressed(Button *btn);
bool button_was_clicked(Button *btn);
bool button_was_long_pressed(Button *btn);

#endif // BUTTON_H
#include "button.h"
#include "sys_time.h"

Button button_create(bool active_low, uint16_t debounce_ms, uint16_t long_press_ms) {
    return (Button){
        .pin_state = active_low ? 1 : 0,
        .debounced_state = active_low ? 1 : 0,
        .last_debounce_time = 0,
        .press_start_time = 0,
        .pressed_event = false,
        .long_pressed_event = false,
        .long_press_handled = false,
        .debounce_delay_ms = debounce_ms,
        .long_press_ms = long_press_ms,
        .active_low = active_low
    };
}

void button_update(Button *btn, uint8_t raw_pin_value) {
    uint32_t now = millis();

    // 1. Állapotváltozás érzékelése a fizikai lábon
    if (raw_pin_value != btn->pin_state) {
        btn->last_debounce_time = now;
        btn->pin_state = raw_pin_value;
    }

    // 2. Sz?rés: Ha eltelt a debounce_delay id?, elfogadjuk az új állapotot
    if ((now - btn->last_debounce_time) > btn->debounce_delay_ms) {
        
        if (raw_pin_value != btn->debounced_state) {
            btn->debounced_state = raw_pin_value;

            bool is_active = btn->active_low ? (btn->debounced_state == 0) : (btn->debounced_state == 1);

            if (is_active) {
                // Gomb megnyomva: elmentjük a kezd? id?t, de eseményt MÉG NEM generálunk!
                btn->press_start_time = now;
                btn->long_press_handled = false;
            } else {
                // Gomb ELENGEDVE:
                // Ha elengedéskor nem történt meg a hosszú nyomás, akkor ez rövid kattintás volt.
                if (!btn->long_press_handled) {
                    btn->pressed_event = true;
                }
            }
        }
    }

    // 3. Hosszú nyomás érzékelése nyomva tartás közben
    bool is_currently_active = btn->active_low ? (btn->debounced_state == 0) : (btn->debounced_state == 1);
    
    if (is_currently_active && !btn->long_press_handled) {
        if ((now - btn->press_start_time) >= btn->long_press_ms) {
            btn->long_pressed_event = true;
            btn->long_press_handled = true; // Megakadályozza a kés?bbi rövid kattintást ÉS az ismételt hosszú nyomást
        }
    }
}

bool button_is_pressed(Button *btn) {
    return btn->active_low ? (btn->debounced_state == 0) : (btn->debounced_state == 1);
}

bool button_was_clicked(Button *btn) {
    if (btn->pressed_event) {
        btn->pressed_event = false; // Töröljük a kiolvasott eseményt
        return true;
    }
    return false;
}

bool button_was_long_pressed(Button *btn) {
    if (btn->long_pressed_event) {
        btn->long_pressed_event = false;
        return true;
    }
    return false;
}
#ifndef MILLIS_H
#define MILLIS_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

// --- Millis Rendszer Keresztmetszete ---

// El?zetes inicializálás (1 ms-os Timer1 megszakítást állít be)
void millis_init(void);

// Visszaadja az indítás óta eltelt milliszekundumokat (atomikusan)
uint32_t millis(void);

// A megszakításkezel?b?l (ISR) meghívandó számláló növel?
void millis_isr(void);


// --- Szoftveres Id?zít? Struktúra (C99) ---

typedef struct {
    uint32_t start_time;
    uint32_t interval;
    bool running;
} Timer;

// Id?zít? inicializálása és indítása
static inline Timer timer_create(uint32_t interval_ms) {
    return (Timer){
        .start_time = millis(),
        .interval = interval_ms,
        .running = true
    };
}

void timer_start(Timer *t, uint32_t interval_ms);
bool timer_expired(Timer *t);
bool timer_check_and_reset(Timer *t);
void timer_stop(Timer *t);

#endif // MILLIS_H

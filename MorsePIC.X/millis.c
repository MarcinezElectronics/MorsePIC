#include "millis.h"

// Megszakításban módosuló számláló
static volatile uint32_t ms_counter = 0;

// Timer1 feltöltési érték 1 ms-hoz (16 MHz / 4 = 4 MHz -> 4000 ciklus 1ms)
// 65536 - 4000 = 61536 (0xF060)
#define TMR1_RELOAD 61536

void millis_init(void) {
    T1CONbits.TMR1CS = 0;  // Bels? órajel (Fosc/4)
    T1CONbits.T1CKPS = 0;  // 1:1 Prescaler
    
    TMR1 = TMR1_RELOAD;
    
    PIR1bits.TMR1IF = 0;   // Megszakítás zászló törlése
    PIE1bits.TMR1IE = 1;   // Timer1 megszakítás engedélyezése
    INTCONbits.PEIE = 1;   // Periféria megszakítások
    INTCONbits.GIE  = 1;   // Globális megszakítások
    
    T1CONbits.TMR1ON = 1;  // Timer1 indítása
}

uint32_t millis(void) {
    uint32_t ms;
    // Atomikussági védelem: GIE lekapcsolása a kiolvasás idejére
    bool gie_state = INTCONbits.GIE;
    INTCONbits.GIE = 0;
    ms = ms_counter;
    INTCONbits.GIE = gie_state;
    return ms;
}

void millis_isr(void) {
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0;
        TMR1 = TMR1_RELOAD;
        ms_counter++;
    }
}

// --- Id?zít? Függvények ---

void timer_start(Timer *t, uint32_t interval_ms) {
    *t = (Timer){
        .start_time = millis(),
        .interval = interval_ms,
        .running = true
    };
}

bool timer_expired(Timer *t) {
    if (!t->running) return false;
    return (millis() - t->start_time >= t->interval);
}

bool timer_check_and_reset(Timer *t) {
    if (timer_expired(t)) {
        t->start_time = millis();
        return true;
    }
    return false;
}

void timer_stop(Timer *t) {
    t->running = false;
}

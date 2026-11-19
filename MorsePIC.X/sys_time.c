#include "sys_time.h"

static volatile uint32_t ms_counter = 0;
static volatile uint16_t timer1ReloadVal;
// 16 MHz Fosc esetén: Instruction cycle = 4 MHz (0.25 us / tick)
// 1 ms = 4000 tick. Timer1 1:1 prescaler-rel:
//#define TMR1_RELOAD 61536 // 65536 - 4000

/*void sys_time_init(void) {
    T1CONbits.TMR1CS = 0;  // Fosc/4
    T1CONbits.T1CKPS = 0;  // 1:1 Prescaler
    TMR1 = timer1ReloadVal;
    //TMR1 = TMR1_RELOAD;
    
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE  = 1;
    
    T1CONbits.TMR1ON = 1;
}*/

void sys_time_isr(void) {
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        PIR1bits.TMR1IF = 0;
        TMR1_Reload();
        //TMR1 = TMR1_RELOAD;
        ms_counter++;
    }
}

uint32_t millis(void) {
    uint32_t ms;
    bool gie_state = INTCONbits.GIE;
    INTCONbits.GIE = 0; // Atomikussági védelem
    ms = ms_counter;
    INTCONbits.GIE = gie_state;
    return ms;
}

uint32_t micros(void) {
    uint32_t ms;
    uint16_t tmr;
    
    bool gie_state = INTCONbits.GIE;
    INTCONbits.GIE = 0;
    ms = ms_counter;
    tmr = TMR1;
    
    // Ha pont most fordult túl a timer, de még nem futott le az ISR:
    if (PIR1bits.TMR1IF) {
        ms++;
        tmr = TMR1;
    }
    INTCONbits.GIE = gie_state;

    // Kiszámoljuk az 1ms-en belüli mikrosecundumpontosságot:
    // TMR1_RELOAD-tól számol felfelé 65535-ig (4000 tick = 1000 us, azaz 4 tick = 1 us)
    //uint16_t elapsed_ticks = tmr - TMR1_RELOAD;
    // 1. Kiszámoljuk a Timer1 tényleges kezd?értékét az MCC 'timer1ReloadVal' változójából:
    uint16_t tmr1_start_val = (uint16_t)(65536UL - timer1ReloadVal);
    // 2. Az utolsó túlcsordulás óta eltelt tikkek (óraciklusok) száma:
    uint16_t elapsed_ticks = tmr - tmr1_start_val;
    // 3. Átváltás mikroszekundumra (16 MHz-es órajel és 1:1 prescaler esetén 4 tikk = 1 us):
    uint32_t us_in_ms = elapsed_ticks / 4;

    return (ms * 1000UL) + us_in_ms;
}

// Timer függvények
void timer_start(Timer *t, uint32_t interval_ms) {
    *t = (Timer){ .start_time = millis(), .interval = interval_ms, .running = true };
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
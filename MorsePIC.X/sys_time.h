#ifndef SYS_TIME_H
#define SYS_TIME_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "mcc_generated_files/tmr1.h"

// I/O és órajel konfigurációhoz igazítva (példa: Fosc = 16 MHz -> Fosc/4 = 4 MHz)
//#define _XTAL_FREQ 16000000UL

void sys_time_init(void);
uint32_t millis(void);
uint32_t micros(void);
void sys_time_isr(void);

// Non-blocking szoftveres id?zít?
typedef struct {
    uint32_t start_time;
    uint32_t interval;
    bool running;
} Timer;

static inline Timer timer_create(uint32_t interval_ms) {
    return (Timer){ .start_time = 0, .interval = interval_ms, .running = false };
}

void timer_start(Timer *t, uint32_t interval_ms);
bool timer_expired(Timer *t);
bool timer_check_and_reset(Timer *t);
void timer_stop(Timer *t);

#endif // SYS_TIME_H
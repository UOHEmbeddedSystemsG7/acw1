
#include <stdint.h>
#include "buzzer.h"

//typedef struct {
//    uint16_t freq;
//    uint16_t duration;
//    uint8_t volume;
//} note;
//
//const note melody_1[] =  {
//    {262, 1, 125},
//    {262, 1, 125},
//    {587, 2, 125},
//    {440, 4, 125}, 
//
//};


void play_midi(const note melody[], uint32_t position) {
    
    const uint16_t len = sizeof(*melody)/sizeof(melody[0]);
    uint16_t note_pos = 0;
    
    for (uint16_t i = 0; i < len; i++) {
        const note n = melody[i];
        
        if (note_pos >= position) {
            set_freq(n.freq);
            set_duty(n.volume);
            return;
        } else {
            note_pos += n.duration;
        }
    }
}

void pwm_reset() {
    CCP1CON = 0x00;
    CCP1CON = 0x0C;
}

void set_duty(uint8_t duty) {
//    CCPR1L = (duty * (PR2 + 1) * 4) / (100);
    

    uint16_t duty_value = ((uint32_t)duty * (PR2 + 1) * 4) / 100;

    CCPR1L = duty_value >> 2;                     // upper 8 bits
    CCP1CON = (CCP1CON & 0b11001111) | ((duty_value & 0b11) << 4); // lower 2 bits
}

void set_freq(uint16_t freq) {
//    PR2 = 100000 / freq;
//    PR2 = 1 / freq;
    
//    PR2 = (1 / _XTAL_FREQ) * 4 * (6 + 1)
    

//    uint32_t psx = _XTAL_FREQ * T2CON;
//    PR2 = (psx / (4 * freq)) -1;
//    PR2 = ( 6 * _XTAL_FREQ ) / (freq * 4) -1;
//    PR2 = freq;
    
    
    
    // pre-scaler 1
    
    uint16_t f = freq;
    uint32_t pr = 0;
    
    // prescaler 1
    pr = (_XTAL_FREQ / (4UL * 1 * f )) - 1;
    if (pr <= 255) {
        PR2 = pr;
        T2CON = 0b00000100 | 0b00000000; // TMR2 on, prescale 1
        return;
    }

    // prescaler 4
    pr = (_XTAL_FREQ / (4UL * 4 * f)) - 1;
    if (pr <= 255) {
        PR2 = pr;
        T2CON = 0b00000100 | 0b00000001; // prescale 4
        return;
    }

    // prescaler 16
    pr = (_XTAL_FREQ / (4UL * 16 * f)) - 1;
    if (pr <= 255) {
        PR2 = pr;
        T2CON = 0b00000100 | 0b00000010; // prescale 16
        return;
    }
    
    PR2 = pr;
    T2CON = 0b00000100 | 0b00000011; // prescale 16
    
}







void PWM() {
    TRISCbits.TRISC2 = 0;
    PR2 = 0;
    CCPR1L = 125;
    CCP1CON = 0b00001100; // PWM mode
    T2CON=0x06;
}
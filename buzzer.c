
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
    CCPR1L = duty;
}

void set_freq(uint16_t freq) {
    PR2 = freq;
//    PR2 = 1000000 / freq;
}







void PWM() {
    TRISCbits.TRISC2 = 0;
    PR2 = 0;
    CCPR1L = 125;
    CCP1CON = 0x0C;
    T2CON=0x06;
}
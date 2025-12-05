
#include <stdint.h>
#include "buzzer.h"

void chirp(const uint16_t freq, const uint8_t duty) {
  const uint16_t freq_half = freq << 1;
  const uint16_t delay = 1000000UL/freq_half;  

  const uint16_t delay_h = delay * duty / 256;
  const uint16_t delay_l = delay * (256-duty) / 256;

//  LATCbits.LATC2 = 1;
//  __delay_us(delay_h);
//  LATCbits.LATC2 = 0;
//  __delay_us(delay_l);
}

void sing(const uint16_t freq, const uint16_t duration, const uint8_t duty) {
  const uint16_t loops = (duration - WAIT_AFTER_SING) * freq / 1000UL;
  for (uint16_t i = 0; i < loops; i++) chirp(freq, duty);
  __delay_ms(WAIT_AFTER_SING);
}


void set_buzzer(const uint16_t freq, const uint8_t duty) {
    PR2 = freq;
    CCPR1L = duty;
}

void set_buzzer_duration(const uint16_t freq, const uint8_t duty) {
    PR2 = freq;
    CCPR1L = duty;
}



//void tune_1() {
//    set_buzzer_duration(262, 125, 150);
//    __delay_ms(150);
//    set_buzzer_duration(262, 125, 150);
//    __delay_ms(150);
//    set_buzzer_duration(587, 125, 300);
//    __delay_ms(300);
//    set_buzzer_duration(440, 125, 375);
//    __delay_ms(375);
//    set_buzzer_duration(415, 125, 300);
//    __delay_ms(300);
//    set_buzzer_duration(392, 125, 250);
//    __delay_ms(250);
//    set_buzzer_duration(345, 125, 300);
//    __delay_ms(300);
//    set_buzzer_duration(294, 125, 150);
//    __delay_ms(150);
//    set_buzzer_duration(349, 125, 150);
//    __delay_ms(150);
//    set_buzzer_duration(392, 125, 150);
//    __delay_ms(150);
//}


void PWM() {
    TRISCbits.TRISC2 = 0;
    PR2 = 0;
    CCPR1L = 125;
    CCP1CON = 0x0C;
    T2CON=0x06;
}
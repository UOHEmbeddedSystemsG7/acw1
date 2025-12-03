
#include <stdint.h>
#include "buzzer.h"

void chirp(uint16_t freq, uint8_t duty) {
  const uint16_t freq_half = freq << 1;
  const uint16_t delay = 1000000UL/freq_half;  

  const uint16_t delay_h = delay * duty / 256;
  const uint16_t delay_l = delay * (256-duty) / 256;

  LATCbits.LATC2 = 1;
  __delay_us(delay_h);
  LATCbits.LATC2 = 0;
  __delay_us(delay_l);
}

void sing(uint16_t freq, uint16_t duration, uint8_t duty) {
  const uint16_t loops = (duration - WAIT_AFTER_SING) * freq / 1000UL;
  for (uint16_t i = 0; i < loops; i++) chirp(freq, duty);
  __delay_ms(WAIT_AFTER_SING);
}
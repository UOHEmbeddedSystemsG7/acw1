//
#include "sevenseg.h"
#include <builtins.h>


const uint8_t digits[11] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F, 0x00};
uint8_t _disp[4] = {0x00, 0x00, 0x00, 0x00};

void xiiseg_init() {
    ANSELD = 0;
    ANSELA = 0;

    TRISD = 0;
    TRISA = 0;

    PORTA = 0;
    PORTD = 0;
}

/// index between 0-3
void xiiseg_display(uint8_t index, uint8_t value) {
    _disp[index] = value;
}

void mult_disp() {
    PORTD = 0;
    for (int i = 0; i < 4; i++) {
        // blank
        PORTA = 0xf;
        PORTD = 0;

        PORTA = (1 << 3-i);
        PORTD = _disp[i];

        __delay_us(700);

    }
}

//void xiiseg_display_temp(uint16_t value) {
//    // TODO: fix c, add decimal between 1 and 2
//    disp[3] = digits[0x6f];
//    disp[2] = digits[raw_adc % 10u];
//    disp[1] = digits[(raw_adc / 10) % 10];
//    disp[0] = digits[(raw_adc / 100) % 10];
//}
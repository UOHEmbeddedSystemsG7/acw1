#include <builtins.h>
#include "adc.h"



uint16_t read_adc() {
    ADCON0 = ADCON0 | (1<<1); // set go bit
    while ((ADCON0 >> 1) & 1<<1); // wait for go to clear
    return (ADRESH << 8)  | (ADRESL);
    
}

void adc_init() {
    TRISE = TRISE | (1<<2);
    ANSELE = 1<<2;
    ADCON0 = 0x19; // set AN6
    ADCON1 = 0; // ?
    ADCON2 = 0xA9; // copied, sets  osccilator 
}

// @ 5v, 4.88mv step
// @ 3v3, 3.22mv step


#include <builtins.h>
#include "adc.h"

uint16_t VREF_mV = 3300u;   // 3300u for if J5 3.3mV and 5000u for if J5 5mV
//uint16_t celcius = 0;


uint16_t read_adc() {
    ADCON0 = ADCON0 | (1<<1); // set go bit
    while ((ADCON0 >> 1) & 1<<1); // wait for go to clear
    return (ADRESH << 8)  | (ADRESL);  
}

uint16_t adc_to_celsius(uint16_t adc_raw) {
    uint32_t temp = adc_raw; // converting to unsigned long prevents overflow and to be multiplied with VREF_mV 
    temp = temp * (uint32_t)VREF_mV; // gives microvolts/step-scaled value
    temp = (temp + 511ul)/1023ul;   // adding 511u then dividing by 1023ul rounds to the nearest millivolt
    //temp = temp/10ul;   // LM35 is 10mV per degree for Celsius
    if (temp>9999ul) temp = 9999ul;
    return temp;
}

void adc_init() {
    TRISE = TRISE | (1<<2); // setting bit 2
    ANSELE = 1<<2;
    ADCON0 = 0x19; // set AN6
    ADCON1 = 0; // ?
    ADCON2 = 0xA9; // copied, sets  osccilator 
}

// @ 5v, 4.88mv step
// @ 3v3, 3.22mv step


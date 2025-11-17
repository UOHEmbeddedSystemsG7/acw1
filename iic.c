#include <builtins.h>
#include "iic.h"

#define FOSC_HZ 8000000ul


static void iic_waitidle(void)
{
    while ((SSP1CON2 & 0x1F) || (SSP1STAT & 0x4)) {
    }
}

void iic_init(uint32_t freq) 
{
    uint32_t brg; //?
    ANSELC &= ~(1<<3);
    ANSELC &= ~(1<<4);
    TRISC |= (1<<3) | (1<<4);
    
    if (freq == 0) {
        freq = 10000;
    }
    
    brg = (FOSC_HZ / (4*freq));
    
    if (brg) {
        brg -= 1;
    }
    if (brg > 255) {
        brg = 255;
    }
    SSP1ADD = brg;
    
    SSP1CON1 = 0x28;
    SSP1STAT = 0x80;
}

void iic_start(void) {
    iic_waitidle();
    
    SSP1CON2 |=0x01;
    while (SSP1CON2 & 0x1) {}
}

void iic_restart() {
    iic_waitidle();
    SSP1CON2 |= 0x02;
    
    while (SSP1CON2 & 0x02) {}
}

void iic_stop() {
    iic_waitidle();
    SSP1CON2 |= 0x04;
    while (SSP1CON2 & 0x4) {}
}


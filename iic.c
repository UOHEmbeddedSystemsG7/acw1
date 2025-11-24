#include <builtins.h>
#include "iic.h"

#define FOSC_HZ 8000000ul


// two serial ports, this uses MSSP1, MSSP1 can be SPI or i2c, but we use iic
// All we use the control reg SSP1CONx, 


static void iic_waitidle(void)
{
    while ((SSP1CON2 & 0x1F) || // start/stop/recive/ack bit set
           (SSP1STAT & 0x4)) // unset when data is read
    
    {
    }
}

void iic_init(uint32_t freq) 
{
    uint32_t brg; //baud rate gen
    ANSELC &= ~(1<<3); // Set digital
    ANSELC &= ~(1<<4); 
    
    TRISC |= (1<<3) | (1<<4);// inputs
    
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
    SSP1ADD = brg; // set baud
    
    
    
    // set the SSP1EN (Enable) 0x20
    // set I2C Host mode, clock = FOSC / (4 * (SSPxADD+1)) 0x8
    SSP1CON1 = 0x20 | 0x8;
    
    
    // disable slew rate control (400khz+)
    SSP1STAT = 0x80;
}

void iic_start(void) {
    iic_waitidle();
    
    SSP1CON2 |=0x01; // set start condition bit
    while (SSP1CON2 & 0x1) {} //wait for unset
}

void iic_restart() {
    iic_waitidle();
    SSP1CON2 |= 0x02; // set repeated start bit
    
    while (SSP1CON2 & 0x02) {} //wait for unset
}

void iic_stop() {
    iic_waitidle();
    SSP1CON2 |= 0x04; // set stop con bit
    while (SSP1CON2 & 0x4) {} // wait for unset
}

uint8_t iic_write(uint8_t data) {
    iic_waitidle();
    SSP1BUF = data; 
    
    // wait till buffer full bit unset
    while (SSP1STAT & 0x1) {}  
    
    iic_waitidle();
    return (SSP1CON2 & 0x40) ? 0 : 1; // determine if ack'd
}

uint8_t iic_read_ack() {
    uint8_t read_byte;
    iic_waitidle();
    SSP1CON2 |= 0x8; // set Rx enable
    
    // wait till buffer full bit set
    while (!(SSP1STAT & 0x1));
    
    read_byte = SSP1BUF;
    
    iic_waitidle();
    SSP1CON2 &= ~(1<<5); // send ack when bit 0
    SSP1CON2 |= (1<<4); // start ack sequence
    while (SSP1CON2 & (1<<4)) {} // wait til done
    
    return read_byte;
}

uint8_t iic_read_nack() {
    uint8_t read_byte;
    iic_waitidle();
    SSP1CON2 |= 0x8; // Rx enable
    
    // wait till buffer full bit set
    while (!(SSP1STAT & 0x1)) {}
    
    read_byte = SSP1BUF;
    iic_waitidle();
    SSP1CON2 |= (1<<5); // no ack when 1
    SSP1CON2 |= (1<<4); // start ack sequence (not needed?)
    while (SSP1CON2 & (1<<4)) {} // wait till unset
    
    return read_byte;
}


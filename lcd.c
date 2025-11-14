#include <builtins.h>
#include "lcd.h"


void lcd_init() {
    // Using the lower half of port b
    // D4-D7 on the chip
    //TRISB = TRISB & ~(0x3<<6); // set B to XXoooooo
    TRISB = 0;
}

void lcd_start_long() {
    __delay_ms(20);
    for(int i = 0; i < 3; i++)
        lcd_send_nibble(0x03);
        __delay_ms(5);
        
    lcd_send_nibble(0x02); // set to 4 bit mode
    __delay_ms(5);
    
    lcd_write_cmd(0x28); // 2lines, 4-bit, 5x8
    lcd_write_cmd(0x0C);
    lcd_write_cmd(0x06);
    lcd_write_cmd(0x01);
    __delay_ms(2);
}

void lcd_disp_char(uint8_t data) {
    // rs to high (data)
    PORTBbits.RB4 = 1;
    lcd_send_nibble(data >> 4); // upper
    lcd_send_nibble(data&0xf); // lower
}

void lcd_write_cmd(uint8_t cmd) {
    // RS to low
    PORTBbits.RB4 = 0;
    lcd_send_nibble(cmd >> 4); // upper
    lcd_send_nibble(cmd&0xf); // lower
}

void lcd_send_nibble(uint8_t data) {
    PORTBbits.RB0 = (data >> 0) & 0x01;
    PORTBbits.RB1 = (data >> 1) & 0x01;
    PORTBbits.RB2 = (data >> 2) & 0x01;
    PORTBbits.RB3 = (data >> 3) & 0x01;
    
    // en to high
    PORTBbits.RB5 = 1;
    
    __delay_ms(1);
    
    // en to low
    PORTBbits.RB5 = 0;
    
}


// RB0 -> D4
// RB1 -> D5
// RB2 -> D6
// RB3 -> D7
// RB4 -> RS
// RB5 -> EN
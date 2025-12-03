#include <builtins.h>
#include "lcd.h"

void init_lcd_display(){
    __delay_ms(40);     // wait for LCD to power up
    
    for(int i = 0; i < 3; i++){
        write_nibble(0x03);
    __delay_ms(5);
    }
    
    // Switch to 4-bit mode
    write_nibble(0x02);
    __delay_ms(5);
    
    // Function set: 2 lines, 4-bits, 5x8 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    write_cmd(0x28);
    __delay_ms(5);
    
    // Display ON, cursor OFF
    write_cmd(0x0C);
    __delay_ms(5);
    
    // Entry mode: increment, no shift
    write_cmd(0x06);
    __delay_ms(5);
    
    // Clears the display
    write_cmd(0x01);
    __delay_ms(5);
}

void set_up_B_port(){
    ANSELB = 0x00;  // make port B digital
    
    // Set B0 to B5 as outputs
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    
    PORTB = 0x00; // Clear port B
}

void write_cmd(char cmd){
    RS = 0;     // Command mode
    write_nibble(cmd >> 4);     // Upper nibble
    write_nibble(cmd & 0x0F);   // Lower nibble
}

void write_data_char(char char_data){
    RS = 1;     //Data mode
    write_nibble(char_data >> 4);   // Upper nibble
    write_nibble(char_data);        // Lower nibble
}

void write_nibble(char nibble) {
    
    // Use RB0, RB1, RB2, and RB3 for the 4 bits
    D4 = (nibble >> 0) & 0x01;
    D5 = (nibble >> 1) & 0x01;
    D6 = (nibble >> 2) & 0x01;
    D7 = (nibble >> 3) & 0x01;
    EN = 1;
    __delay_ms(2);
    EN = 0;
    __delay_ms(2);
}

void set_cursor(char row, char col){
    char address;
    if(row == 1){
        address = 0x80 + (col -1);  // Row 1 address
    }else{
        address = 0xC0 + (col -1);  // Row 2 address
    }
    write_cmd(address);
}

void write_data_string(char *text){
    while (*text){  // converts users input string in to individual characters
        write_data_char(*text++);
    }
}

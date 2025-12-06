#include <builtins.h>
#include "lcd.h"
#include "rtc.h"


void lcd_init(){
    ANSELB = 0x00;  // make port B digital
    
    // Set B0 to B5 as outputs
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    
    PORTB = 0x00; // Clear port B
    
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

void lcd_write_string(char row, char col, char *text){
    char address;
    if(row == 1){
        address = 0x80 + (col -1);  // Row 1 address
    }else{
        address = 0xC0 + (col -1);  // Row 2 address
    }
    write_cmd(address);
    while (*text){
        write_data_char(*text++);
    }
}

void lcd_write_temp(char row, char col, int celsius){
    
    // ADD TRY FOR IF WRONG COL CHOSEN
    set_cursor(row,col);// first character
    write_data_char(((celsius / 100) % 10) + 48);

    set_cursor(row,(col + 1));// second character
    write_data_char(((celsius / 10) % 10) + 48);
    
    set_cursor(row,(col + 2));// third character
    write_data_char(46);

    set_cursor(row,(col + 3));// third character
    write_data_char((celsius % 10u) + 48);
    
    set_cursor(row, (col +4));
    write_data_char(223);
    
    set_cursor(row, (col +5));
    write_data_char(67);
    
}

void lcd_write_time(char row, char col, rtc_time_t *time_now, rtc_time_t *time_previous) {
    
    // only if hour has changed
    if (time_now->hour != time_previous->hour) {
        set_cursor(row,col);
        write_data_char(((time_now->hour / 10) % 10) + 48);

        set_cursor(row,col+1);
        write_data_char(((time_now->hour / 1) % 10) + 48);

        // prints a ":" between chars, move to ui?
        set_cursor(row,col+2);
        write_data_char(58); // :
    }
    
    // only if min has changed
    if (time_now->minute != time_previous->minute) {
        set_cursor(row,col+3);
        write_data_char(((time_now->minute / 10) % 10) + 48);

        set_cursor(row,col+4);
        write_data_char(((time_now->minute / 1) % 10) + 48);

        // prints a ":" between chars, move to ui?
        set_cursor(row,col+5);
        write_data_char(58); 
    }
    
    // only if sec has changed
    if (time_now->second != time_previous->second) {
        set_cursor(row,col+6);
        write_data_char(((time_now->second / 10) % 10) + 48);

        // prints a ":" between chars, move to ui?
        set_cursor(row,col+7);
        write_data_char(((time_now->second / 1) % 10) + 48);
    }
}

void lcd_write_date(char row, char col, rtc_date_t *date_now, rtc_date_t *date_previous) {
    // exit this early 99.99% of the time, only changes daily.
    if (date_now->day != date_previous->day || 
        date_now->month != date_previous->month || 
        date_now->year != date_previous->year) {
    
        // day 
        set_cursor(row,col);
        write_data_char(((date_now->day / 10) % 10) + 48);
        set_cursor(row,col+1);
        write_data_char(((date_now->day / 1) % 10) + 48);
        
        // prints a "/" between chars
        set_cursor(row,col+2);
        write_data_char(47);
    
    
        //day
        set_cursor(row,col+3);
        write_data_char(((date_now->month / 10) % 10) + 48);
        set_cursor(row,col+4);
        write_data_char(((date_now->month / 1) % 10) + 48);

        // prints a "/" between chars
        set_cursor(row,col+5);
        write_data_char(47);
    
        
        //year
        set_cursor(row,col+6);
        write_data_char(((date_now->year / 10) % 10) + 48);
        set_cursor(row,col+7);
        write_data_char(((date_now->year / 1) % 10) + 48);
    }
}
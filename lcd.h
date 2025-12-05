#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#define _XTAL_FREQ 8000000UL
#define D4 PORTBbits.RB0
#define D5 PORTBbits.RB1
#define D6 PORTBbits.RB2
#define D7 PORTBbits.RB3
    
#define RS PORTBbits.RB4
#define EN PORTBbits.RB5

#endif 

#ifndef LCD_H
#define	LCD_H


#ifdef	__cplusplus
extern "C" {
#endif

// Function declarations
void lcd_init();
void write_data_char(char char_data);
void write_cmd(char cmd);
void write_nibble(char nibble);
void set_cursor(char row, char col);
void lcd_write_string(char row, char col, char *text);
void lcd_write_temp(char row, char col, int celsius);


    
    
#ifdef	__cplusplus
}
#endif

#endif	
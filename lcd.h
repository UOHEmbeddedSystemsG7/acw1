#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC

#include "rtc.h"


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
void lcd_write_temp(char row, char col, uint16_t celsius);
void lcd_write_time(char row, char col, rtc_time_t *time_now, rtc_time_t *time_previous);
void lcd_write_date(char row, char col, rtc_date_t *date_now, rtc_date_t *date_previous);

    
    
#ifdef	__cplusplus
}
#endif

#endif	
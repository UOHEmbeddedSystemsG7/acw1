#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

void lcd_init();
void lcd_start_long();
void lcd_disp_char(uint8_t data);
void lcd_write_cmd(uint8_t cmd);
void lcd_send_nibble(uint8_t data);
    
    
#ifdef	__cplusplus
}
#endif

#endif	
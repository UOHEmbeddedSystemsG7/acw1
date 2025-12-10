
#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 

#include <string.h>

#include "sevenseg.h"
#include "adc.h"
#include "iic.h"
#include "rtc.h"
#include "eeprom.h"
#include "ui.h"
#include "lcd.h"
#include "heating.h"



uint16_t filtered_celsius = 0;
uint16_t celsius = 0;
uint16_t prev_celsius = 0;

rtc_time_t time_now;
rtc_time_t time_before;
rtc_date_t date_now;
rtc_date_t date_before;

uint32_t main_loop_count = 0;
uint32_t lcd_last_run_count = 0;
uint32_t rtc_last_fetch_count = 0;
uint32_t eeprom_last_save_count = 0;

// lcd
uint8_t ui_selected_screen = 0;
#define TOP_SCREEN 6
uint8_t counter = 0;
uint8_t screen_swapped = 1;

int main(void)
{
    SYSTEM_Initialize();

    // Keep this ordering of inits
    adc_init();
    iic_init(100000ul);
    rtc_init();
    xiiseg_init();
    lcd_init();
    heating_init();

    
    // button init?
    TRISC |= 0xC3;
    ANSELC &= ~(0xC3);
    
    ui_alarm_sel = eeprom_read_byte(EEPROM_ADDR_ALARM_SEL);
    
    ui_alarm_sel = eeprom_read_byte(EEPROM_ADDR_ALARM_SEL);
            
    ui_temp_upper = eeprom_read_byte(EEPROM_ADDR_TEMP_UPPER)*10;
    ui_temp_lower = eeprom_read_byte(EEPROM_ADDR_TEMP_LOWER)*10;
            
    ui_temp_start.hour = eeprom_read_byte(EEPROM_ADDR_TEMP_START_H);
    ui_temp_start.minute = eeprom_read_byte(EEPROM_ADDR_TEMP_START_M);
            
    ui_temp_end.hour = eeprom_read_byte(EEPROM_ADDR_TEMP_END_H);
    ui_temp_end.minute = eeprom_read_byte(EEPROM_ADDR_TEMP_END_M);
            
    ui_alarm_time.hour = eeprom_read_byte(EEPROM_ADDR_ALARM_H);
    ui_alarm_time.minute = eeprom_read_byte(EEPROM_ADDR_ALARM_M);
    
    
    while(1)
    {
        
        // ------------------- USER INPUTS ------------------- 
        // ------------------- USER INPUTS ------------------- 
        // ------------------- USER INPUTS ------------------- 
        
        // one goes up a menu, other goes back
        if (PORTCbits.RC1 == 0) {
            ui_selected_screen++;
            if (ui_selected_screen > TOP_SCREEN) {
                ui_selected_screen = 0;
            }
            screen_swapped = 1;
            __delay_ms(10);
        }
        if (PORTCbits.RC0 == 0) {
            
            if (ui_selected_screen == 0) {
                ui_selected_screen = TOP_SCREEN;
            } else {
                ui_selected_screen--;
            }
            screen_swapped = 1;
            __delay_ms(10);
        }
        
        if (PORTCbits.RC7 == 0) {
            ui_increment(ui_selected_screen);
            __delay_ms(10);
        }
        if (PORTCbits.RC6 == 0) {
            ui_decrement(ui_selected_screen);
            __delay_ms(10);
        }
        
        
        // -------------------- DISPLAY AND RENDERING --------------------
        // -------------------- DISPLAY AND RENDERING --------------------
        // -------------------- DISPLAY AND RENDERING --------------------
        
        // XII SEG
        // we want this on ISR prob
        xiiseg_multiplex();
        
        
        //celsius = adc_to_celsius(read_adc());
        
        uint16_t temp_celsius = adc_to_celsius(read_adc());

        if (filtered_celsius == 0) {
        // on init
            filtered_celsius = temp_celsius;
        } 
        
        else {
            filtered_celsius = (uint16_t)(((uint32_t)filtered_celsius * 3u + (uint32_t)temp_celsius) / 4u);
        }

        celsius = filtered_celsius;
        
        
        xiiseg_display(3, 0x39); // 0x39 is the hex for C
        xiiseg_display(2, digits[celsius % 10u]);
        xiiseg_display(1, (digits[(celsius / 10) % 10] + 0x80) ); // adding 0x80 turns on RD7 which is the dp
        xiiseg_display(0, digits[(celsius / 100) % 10]);

        // LCDTIME/DATE

        // run this every ~100 loops
        if (main_loop_count - lcd_last_run_count >= 100){
            if (screen_swapped) {
               // clean bottom line, top done in render

               lcd_write_string(2,1, ui_empty_line);
               
               // set both to 0 so they refresh
               memset(&date_before, 0, sizeof(date_before)); 
               memset(&time_before, 0, sizeof(time_before));
               
               
            }

            switch (ui_selected_screen) {
                case 0: // render the default time and date.
                    lcd_write_date(1,9, &date_now, &date_before);
                    lcd_write_time(2,9, &time_now, &time_before);
      
                    date_before = date_now;
                    time_before = time_now;
                    break;
                case 1:
                    ui_render_temp_upper(screen_swapped);
                    break;
                case 2:
                    ui_render_temp_lower(screen_swapped);
                    break;
                case 3:
                    ui_render_heating_start(screen_swapped);
                    break;
                case 4:
                    ui_render_heating_end(screen_swapped);
                    break;
                case 5:
                    ui_render_alarm_time(screen_swapped);
                    break;
                case 6:
                    ui_render_alarm_tone(screen_swapped);
                    break;
           }
            screen_swapped = 0;
        }
        
        // RTC Refresh
        // run every ~500
        if (main_loop_count - rtc_last_fetch_count >= 100) {
            rtc_get_time(&time_now);
            rtc_get_date(&date_now); // can be removed if wanted quicker
            heating_logic(celsius, time_now);
        }

        
        
        // ----------------------- MAIN LOOP LOGIC! ----------------------- 
        // ----------------------- MAIN LOOP LOGIC! ----------------------- 
        // ----------------------- MAIN LOOP LOGIC! ----------------------- 
        
        
        
        
        
       
        
        
         //SAVE to EEPROM every ~10 seconds
        if (main_loop_count - eeprom_last_save_count >= 300) { // we may only want to save if chaganged
            
            eeprom_write_byte(EEPROM_ADDR_ALARM_SEL, ui_alarm_sel);
            
            eeprom_write_byte(EEPROM_ADDR_TEMP_UPPER, ui_temp_upper/10);
            eeprom_write_byte(EEPROM_ADDR_TEMP_LOWER, ui_temp_lower/10);
            
            eeprom_write_byte(EEPROM_ADDR_TEMP_START_H, ui_temp_start.hour);
            eeprom_write_byte(EEPROM_ADDR_TEMP_START_M, ui_temp_start.minute);
            
            eeprom_write_byte(EEPROM_ADDR_TEMP_END_H, ui_temp_end.hour);
            eeprom_write_byte(EEPROM_ADDR_TEMP_END_M, ui_temp_end.minute);
            
            eeprom_write_byte(EEPROM_ADDR_ALARM_H, ui_alarm_time.hour);
            eeprom_write_byte(EEPROM_ADDR_ALARM_M, ui_alarm_time.minute);
            
        }
        
        main_loop_count+= 1;
        prev_celsius = celsius;
    }
}

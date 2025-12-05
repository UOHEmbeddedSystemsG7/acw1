
#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 


#include "sevenseg.h"
#include "adc.h"
#include "iic.h"
#include "rtc.h"
#include "eeprom.h"
#include "ui.h"
#include "lcd.h"




uint16_t celsius = 0;

rtc_time_t time_now;
rtc_time_t time_before;
rtc_date_t date_now;
rtc_date_t date_before;

uint32_t main_loop_count = 0;
uint32_t lcd_last_run_count = 0;
uint32_t rtc_last_fetch_count = 0;

// lcd
uint8_t lcd_counter = 0;

#if (defined(XII_TEMP) && defined(XII_TIME))   || \
    (defined(XII_TEMP) && defined(XII_COUNT)) || \
    (defined(XII_TIME) && defined(XII_COUNT))
    // More than one is defined
#error "Only define XII_TEMP or XII_TIME, not both"
#endif


int main(void)
{
    SYSTEM_Initialize();

    // Keep this ordering of inits
    adc_init();
    iic_init(100000ul);
    rtc_init();
    xiiseg_init();
    lcd_init();

    while(1)
    {
        // we want this on ISR prob
        xiiseg_multiplex();
        
        celsius = adc_to_celsius(read_adc());
        
        xiiseg_display(3, 0x39); // 0x39 is the hex for C
        xiiseg_display(2, digits[celsius % 10u]);
        xiiseg_display(1, (digits[(celsius / 10) % 10] + 0x80) ); // adding 0x80 turns on RD7 which is the dp
        xiiseg_display(0, digits[(celsius / 100) % 10]);
        
        
        
        // LCDTIME/DATE
        // run this every ~100 loops
        if (main_loop_count - lcd_last_run_count >= 100){
            lcd_write_date(1,9, &date_now, &date_before);
            lcd_write_time(2,9, &time_now, &time_before);
            
            date_before = date_now;
            time_before = time_now;
            
        }
       
        
        // RTC Refresh
        // run every ~500
        if (main_loop_count - rtc_last_fetch_count >= 500) {
            main_loop_count=0l;
            rtc_get_time(&time_now);
            rtc_get_date(&date_now); // can be removed if wanted quicker
        }
        
        
        main_loop_count+= 1;
    }
}

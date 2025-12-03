
#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 



#include "iic.h"
#include "sevenseg.h"

#include "iic.h"
#include "rtc.h"
#include "eeprom.h"


//#define XII_TEMP
uint16_t celsius = 0;

//#define XII_TIME
rtc_time_t now;
uint64_t ms = 0;

//#define XII_COUNT
uint8_t counter = 0;


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
    
#ifdef XII_COUNT
    counter = eeprom_read_byte(EEPROM_ADDR_COUNTER);
    TRISC = 0xff;
    ANSELC = 0;
#endif
    
    while(1)
    {
        // we want this on ISR prob
        xiiseg_multiplex();
        
        
        
        
        
    #ifdef XII_COUNT
        if (PORTCbits.RC0 == 0) {
            counter++;
            __delay_ms(10);
        }
        if (PORTCbits.RC1 == 0) {
            counter--;
            __delay_ms(10);
        }
        xiiseg_display(3, digits[counter % 10u]);
        xiiseg_display(2, digits[(counter / 10) % 10]);
        xiiseg_display(1, digits[(counter / 100) % 10]);
        
        ms++;
        if (ms > 500) { // approx every 3 seconds
            ms=0;
            eeprom_write_byte(EEPROM_ADDR_COUNTER, counter);
            
        }
    #endif

    #ifdef XII_TEMP
        celsius = adc_to_celsius(read_adc());
        
      
        xiiseg_display(3, 0x39); // 0x39 is the hex for C
        xiiseg_display(2, digits[celsius % 10u]);
        xiiseg_display(1, (digits[(celsius / 10) % 10] + 0x80) ); // adding 0x80 turns on RD7 which is the dp
        xiiseg_display(0, digits[(celsius / 100) % 10]);
    #endif

    #ifdef XII_TIME
        
        xiiseg_display(3, digits[now.second % 10u]);
        xiiseg_display(2, digits[(now.second / 10) % 10]);
        xiiseg_display(1, digits[now.minute % 10u]);
        xiiseg_display(0, digits[(now.minute / 10) % 10]);
        
        ms+= 1;
        if (ms > 500) {
            ms=0l;
            rtc_get_time(&now);
        }
    #endif

    }
}
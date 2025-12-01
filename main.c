
#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 


#include "sevenseg.h"
#include "adc.h"
#include "iic.h"
#include "rtc.h"
//#include "heating.h"


//#define XII_TEMP
uint16_t celsius = 0;

#define XII_TIME
rtc_time_t now;
uint64_t ms = 0;

#if defined(XII_TEMP) && defined(XII_TIME)
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

    while(1)
    {
        // we want this on ISR prob
        xiiseg_multiplex();

        
        
        
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
    
    
    TRISC = 0x00;
    
    while(1)
    {
    
    TRISC = 0x00;
    
    while(1)
    {
         celsius = adc_to_celsius(read_adc());
        
      
         xiiseg_display(3, 0x39); // 0x39 is the hex for C
         xiiseg_display(2, digits[celsius % 10u]);
         xiiseg_display(1, (digits[(celsius / 10) % 10] + 0x80) ); // adding 0x80 turns on RD7 which is the dp
         xiiseg_display(0, digits[(celsius / 100) % 10]);
        
         mult_disp();
    }    
}
}
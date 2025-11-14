
#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 


#include "sevenseg.h"
#include "adc.h"
#include "lcd.h"


uint16_t adc_count = 0;

int main(void)
{
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 

    xiiseg_init();
    adc_init();
    lcd_init();

    
    
    lcd_start_long();
    
    lcd_disp_char(65);
    
    while(1)
    {
        adc_count = read_adc();
        
        xiiseg_display(3, digits[adc_count % 10u]);
        xiiseg_display(2, digits[(adc_count / 10) % 10]);
        xiiseg_display(1, digits[(adc_count / 100) % 10]);
        xiiseg_display(0, digits[(adc_count / 1000u) % 10u]);
 
        mult_disp();
    }    
}
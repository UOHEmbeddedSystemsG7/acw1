
#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 


#include "sevenseg.h"
#include "adc.h"


uint16_t celsius = 0;

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
    
    while(1)
    {
        celsius = adc_to_celsius(read_adc());
        
        
        xiiseg_display(3, digits[celsius % 10u]);
        xiiseg_display(2, digits[(celsius / 10) % 10]);
        xiiseg_display(1, digits[(celsius / 100) % 10]);
        xiiseg_display(0, digits[(celsius / 1000u) % 10u]);
 
        mult_disp();
    }    
}
#include <builtins.h>
#include "lcd.h"
#include "rtc.h"
#include "heating.h"

rtc_time_t time_now;


void heating_on(){
    LATA |= (0x07<<5);
    
}

void heating_off(){
    // using ~(not) flips the bits so that the LEDs are turned off
    LATA &= ~(0x07<<5);
    
}

void heating_init(){
    ANSELA = 0;
    TRISA = 0;
    PORTA = 0;
    
    // set pin RA5 as output
    TRISAbits.TRISA5 = 0;
    
    heating_off();
}

void heating_logic(uint16_t celsius, uint16_t heating_lower, uint16_t heating_upper){
   
    heating_lower = heating_lower * 10;
    heating_upper = heating_upper * 10;
    
    uint8_t current_hour = time_now.hour;
    uint8_t current_minute = time_now.minute;
    
    // checks hour then minute for whether heating allowed to turn on
    if ((current_hour >= lower_hour) && (current_hour <= upper_hour)){
        
        if ((current_hour == upper_hour) && (current_minute > upper_min)){
            heating_off();
        } else if ((current_hour == lower_hour) && (current_minute < lower_min)){
            heating_off();
        } else {
            // if temp goes lower than bottom threshold then heating turns on
            if (celsius <= heating_lower){
                heating_on();
            }
          
            // if temp in room greater than heating_upper the LED will be off regardless of time
            if(celsius >= heating_upper){
                heating_off();
            }
        }
    } else {heating_off();}   
}


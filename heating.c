#include <builtins.h>
#include "lcd.h"
#include "rtc.h"
#include "heating.h"
#include "ui.h"

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
    
    // set pins RA5:7 as output
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;
    
    heating_off();
}

void heating_logic(uint16_t celsius, rtc_time_t time_now){
    
    uint8_t end_hour = ui_temp_end.hour;
    uint8_t end_min = ui_temp_end.minute;
    
    uint8_t start_hour = ui_temp_start.hour;
    uint8_t start_min = ui_temp_start.minute;
    
   
    // checks hour then minute for whether heating allowed to turn on
    if ((time_now.hour >= start_hour) && (time_now.hour <= end_hour)){
        
        if ((time_now.hour == end_hour) && (time_now.minute > end_min)){
            heating_off();
        } else if ((time_now.hour == start_hour) && (time_now.minute < start_min)){
            heating_off();
        } else {
            // if temp goes lower than bottom threshold then heating turns on
            if (celsius <= ui_temp_lower){
                heating_on();
            }
          
            // if temp in room greater than heating_upper the LED will be off regardless of time
            if(celsius >= ui_temp_upper){
                heating_off();
            }
        }
    } else {heating_off();}   

}


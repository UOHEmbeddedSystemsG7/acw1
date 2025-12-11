#include <builtins.h>
#include "lcd.h"
#include "rtc.h"
#include "heating.h"
#include "ui.h"

rtc_time_t time_now;

void heating_off_LED(uint8_t LED){
    
    switch (LED){
        case 0: // RA7
            LATA &= ~(1<<7);
            break;
        case 1: // RA6
            LATA &= ~(1<<6);
            break;
        case 2: // RA5
            LATA &= ~(1<<5);
            break;
        case 3: // RA4
            LATA &= ~(1<<4);
            break;
    }
}

void heating_on(){
    LATA |= (0x0f<<4);
    
}

void heating_off(){
    // using ~(not) flips the bits so that the LEDs are turned off
    LATA &= ~(0x0f<<4);
    
}

void heating_init(){
    ANSELA = 0;
    TRISA = 0;
    PORTA = 0;
    
    // set pins RA4:7 as output
    TRISAbits.TRISA4 = 0;
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
    if ((time_now.hour >= start_hour) && (time_now.hour <= end_hour) && (!ui_window_disabled)){
        
        if ((time_now.hour == end_hour) && (time_now.minute > end_min)){
            heating_off();
        } else if ((time_now.hour == start_hour) && (time_now.minute < start_min)){
            heating_off();
        } else {
            // if temp goes lower than bottom threshold then heating turns on
            if (celsius <= ui_temp_lower){
                heating_on();
                isHeated = 0;
            } else if ((celsius > ui_temp_lower) && (celsius < ui_temp_upper) && (isHeated == 0)){ // as heating approaches upper threshold LEDs turn off
                
                if(celsius < ui_temp_upper - 40){
                    LATA |= (0x0f<<4);
                } else if((celsius >= ui_temp_upper -40) && (celsius < ui_temp_upper -30)){
                    LATA &= ~(0x01<<4);
                    LATA |= (0x07<<5);
                } else if ((celsius >= ui_temp_upper -30) && (celsius < ui_temp_upper -20)){
                    LATA &= ~(0x03<<4);
                    LATA |= (0x03<<6);
                } else if (celsius < ui_temp_upper -10){
                    LATA &= ~(0x07<<4);
                    LATA |= (0x01<<7);
                }
            }
          
            // if temp in room greater than heating_upper the LED will be off regardless of time
            if(celsius >= ui_temp_upper){
                isHeated = 1;
                heating_off();
            }
        }
    } else {heating_off();}   

}


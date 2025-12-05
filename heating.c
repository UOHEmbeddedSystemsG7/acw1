#include <builtins.h>
#include "lcd.h"
#include "rtc.h"
#include "heating.h"

// 17:37:00
uint8_t upper_hour = 17 ;
uint8_t upper_min = 45 ;
uint8_t upper_sec = 0;

// 07:00:00
uint8_t lower_hour = 7;
uint8_t lower_min = 0;
uint8_t lower_sec = 0;

rtc_time_t time_now;


void heating_on(){
    LATA = LATA | (1<<5);
}

void heating_off(){
    LATA = LATA | 0x00;
}

void heating_init(){
    ANSELA = 0;
    TRISA = 0;
    PORTA = 0;
    
    // set pin RA5 as output
    TRISAbits.TRISA5 = 0;
    
    heating_off();
}

void heating_logic(uint16_t celsius, uint8_t heating_lower, uint8_t heating_upper){
   
    int temp = celsius / 10;
    
    uint8_t hour = time_now.hour;
    uint8_t minute = time_now.minute;
    
    // checks hour then minute then second for whether heating allowed to turn on
    if((hour >= lower_hour) && (hour <= upper_hour)){
        if ((minute >= lower_min) && (minute < upper_min)) {
            
            if ((temp <= heating_lower) || (temp < heating_upper)){ //heating turns on at heating lower and stop when it reaches upper
                    heating_on();
            }

            // if temp in room greater than heating_upper the LED will be off regardless of time
            if(temp >= heating_upper){
                heating_off();
            }
           
        }else {heating_off();}
    } else {heating_off();}
}


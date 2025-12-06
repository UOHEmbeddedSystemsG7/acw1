#include "ui.h"
#include <builtins.h>
#include <stdint.h>
#include "debounce.h"
#include "rtc.h"
#include "lcd.h"
#include "eeprom.h"

uint8_t btn_dec() {
  uint8_t raw = PORTCbits.RC6 ? 1u : 0u;
  return debounce(raw, &state_dec);
}

uint8_t btn_sel() {
  uint8_t raw = PORTCbits.RC1 ? 1u : 0u;
  return debounce(raw, &state_sel);
}

uint8_t btn_inc() {
  uint8_t raw = PORTCbits.RC7 ? 1u : 0u;
  return debounce(raw, &state_inc);
}

uint8_t btn_cyc() {
  uint8_t raw = PORTCbits.RC0 ? 1u : 0u;
  return debounce(raw, &state_cyc);
}

// These are screen spsific.
void ui_increment(uint8_t current_screen) {
    switch (current_screen) {
        case 0: // default
            break;
        case 1: // T upper
            ui_temp_upper++;
            break;
        case 2: // T lower
            ui_temp_lower++;
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;   
        
    }
    
}
void ui_decrement(uint8_t current_screen) {
    switch (current_screen) {
        case 0:
            break;
        case 1:
            ui_temp_upper--;
            break;
        case 2:
            ui_temp_lower--;
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;    
    }
    
}

void ui_render_temp_upper(uint8_t just_entered) {
    char line1[16] = "Temp Upper:     ";
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
    }
    lcd_write_temp(2,1,ui_temp_upper);
    
}

void ui_render_temp_lower(uint8_t just_entered) {
    char line1[16] = "Temp Lower:     ";
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
    }
    lcd_write_temp(2,1,ui_temp_lower);
}

void ui_render_heating_start(uint8_t just_entered) {
    char line1[16] = "Temp Start:     ";
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
    }
}
void ui_render_heating_end(uint8_t just_entered) {
    char line1[16] = "Temp End:     ";
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
    }
}
void ui_render_alarm_time(uint8_t just_entered) {
    char line1[16] = "Alarm Time:     ";
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
    }
}
void ui_render_alarm_tone(uint8_t just_entered) {
    char line1[16] = "Alarm Tone:     ";
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
    }
}
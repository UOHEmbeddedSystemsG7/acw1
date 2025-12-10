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

static void time_increment(rtc_time_t *time) {
    // increments at 1 min per time
    if (time->minute >= 59) { // 59->0
        time->minute = 0;
        
        if (time->hour >= 23) { // loop around
            time->hour = 0;
        }
        else {
            time->hour++;
        }
    }
    else {
        time->minute++;
    }
}

static void time_decrement(rtc_time_t *time) {
    if (time->minute == 0) { // 0->59
        time->minute = 59;
        
        if (time->hour == 0) { // loop around
            time->hour = 23;
        }
        else {
            time->hour--;
        }
    }
    else {
        time->minute--;
    }
}

// These are screen spsific.
void ui_increment(uint8_t current_screen) {
    switch (current_screen) {
        case 0: // default
            break;
        case 1: // T upper
            if (ui_temp_upper > 390) {ui_temp_upper = 0;}
            ui_temp_upper += 10;
            break;
        case 2: // T lower
            if (ui_temp_lower > 390) {ui_temp_lower = 0;}
            ui_temp_lower += 10;
            break;
        case 3:
            time_increment(&ui_temp_start);
            break;
        case 4:
            time_increment(&ui_temp_end);
            break;
        case 5:
            time_increment(&ui_alarm_time);
            break;
        case 6:
            if (ui_alarm_sel != 2) {
                ui_alarm_sel++;
            }
            break;   
        
    }
    
}

void ui_decrement(uint8_t current_screen) {
    switch (current_screen) {
        case 0:
            break;
        case 1:
            if (ui_temp_upper == 0 ) {ui_temp_upper = 410;}
            ui_temp_upper -= 10;
            break;
        case 2:
            if (ui_temp_lower == 0 ) {ui_temp_lower = 410;}
            ui_temp_lower -= 10;
            break;
        case 3:
            time_decrement(&ui_temp_start);
            break;
        case 4:
            time_decrement(&ui_temp_end);
            break;
        case 5:
            time_decrement(&ui_alarm_time);
            break;
        case 6:
            if (ui_alarm_sel != 0) {
                ui_alarm_sel--;
            }
            break;    
    }
    
}

void ui_render_temp_upper(uint8_t just_entered) {
    char line1[16] = "Temp Upper:     ";
    static uint16_t prev_temp = 0;
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
        
        // degree C
        set_cursor(2, 3);
        write_data_char(223);
        set_cursor(2, 4);
        write_data_char(67);
    }
    
    if (ui_temp_upper != prev_temp) {
        set_cursor(2,1);// first character
        write_data_char(((ui_temp_upper / 100) % 10) + 48);

        set_cursor(2,2);// second character
        write_data_char(((ui_temp_upper / 10) % 10) + 48);
    }
    
}

void ui_render_temp_lower(uint8_t just_entered) {
    char line1[16] = "Temp Lower:     ";
    static uint16_t prev_temp = 0;
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
        
        // degree C
        set_cursor(2, 3);
        write_data_char(223);
        set_cursor(2, 4);
        write_data_char(67);
    }
    
    if (ui_temp_lower != prev_temp) {
        set_cursor(2,1);// first character
        write_data_char(((ui_temp_lower / 100) % 10) + 48);

        set_cursor(2,2);// second character
        write_data_char(((ui_temp_lower / 10) % 10) + 48);
    }
}

void ui_render_heating_start(uint8_t just_entered) {
    char line1[16] = "Temp Start:HH:MM";
    static rtc_time_t prev_time;
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
        // make impossible
        prev_time.hour = 99; prev_time.minute = 99; prev_time.second = 99;
        lcd_write_time(2,12, &ui_temp_start, &prev_time);
    }
    lcd_write_time(2,12, &ui_temp_start, &prev_time);
    prev_time = ui_temp_start;
}

void ui_render_heating_end(uint8_t just_entered) {
    char line1[16] = "Temp End:HH:MM";
    static rtc_time_t prev_time;
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
        // make impossible
        prev_time.hour = 99; prev_time.minute = 99; prev_time.second = 99;
        lcd_write_time(2,12, &ui_temp_end, &prev_time);
    }
    lcd_write_time(2,12, &ui_temp_end, &prev_time);
    prev_time = ui_temp_end;
}

void ui_render_alarm_time(uint8_t just_entered) {
    char line1[16] = "Alarm Time:HH:MM";
    static rtc_time_t prev_time;
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
        // make impossible
        prev_time.hour = 99; prev_time.minute = 99; prev_time.second = 99;
        lcd_write_time(2,12, &ui_alarm_time, &prev_time);
    }
    lcd_write_time(2,12, &ui_alarm_time, &prev_time);
    prev_time = ui_alarm_time;
}

void ui_render_alarm_tone(uint8_t just_entered) {
    char line1[16] = "Alarm Tone:     ";
    char line2[] = "0 = Off";
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
        lcd_write_string(2,10, line2);
    }
    set_cursor(2,1);// second character
    write_data_char(ui_alarm_sel + 48);
}


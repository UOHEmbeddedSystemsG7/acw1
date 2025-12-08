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
    
    if (just_entered) {
        lcd_write_string(1,1, line1);
    }
    set_cursor(2,1);// second character
    write_data_char(ui_alarm_sel + 48);
}


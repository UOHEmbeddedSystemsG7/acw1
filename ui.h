

#ifndef UI_H
#define UI_H

#include "debounce.h"
#include "rtc.h"
#include <stdint.h>
#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif

#ifdef __cplusplus
extern "C" {
#endif

static debounce_state_t state_cyc = {0, 0, 0};
static debounce_state_t state_sel = {0, 0, 0};
static debounce_state_t state_inc = {0, 0, 0};
static debounce_state_t state_dec = {0, 0, 0};

uint8_t btn_cyc();
uint8_t btn_sel();
uint8_t btn_inc();
uint8_t btn_dec();

void ui_increment(uint8_t current_screen);
void ui_decrement(uint8_t current_screen);

uint16_t ui_temp_upper;
uint16_t ui_temp_lower;
uint8_t ui_alarm_sel;

rtc_time_t ui_temp_start;
rtc_time_t ui_temp_end;
rtc_time_t ui_alarm_time;

char ui_empty_line[16] = "                ";

void ui_render_temp_upper(uint8_t just_entered);
void ui_render_temp_lower(uint8_t just_entered);
void ui_render_heating_start(uint8_t just_entered);
void ui_render_heating_end(uint8_t just_entered);
void ui_render_alarm_time(uint8_t just_entered);
void ui_render_alarm_tone(uint8_t just_entered);

#ifdef __cplusplus
}
#endif

#endif /* IIC_H */

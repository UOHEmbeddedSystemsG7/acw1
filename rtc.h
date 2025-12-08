#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 


#ifndef RTC_H
#define	RTC_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct { uint8_t second, minute, hour;} rtc_time_t;
typedef struct { uint8_t day, month, year;} rtc_date_t;
    
static uint8_t dec_to_bcd(uint8_t dec);
static uint8_t bcd_to_dec(uint8_t bcd);

void rtc_write_reg(uint8_t addr, uint8_t data);
void rtc_read_reg(uint8_t addr, uint8_t* buf, uint8_t buf_len);

void rtc_init();
void rtc_set_time(rtc_time_t* time);
void rtc_get_time(rtc_time_t* time);

void rtc_set_date(rtc_date_t* date);
void rtc_get_date(rtc_date_t* date);



#ifdef	__cplusplus
}
#endif

#endif

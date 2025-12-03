#include <builtins.h>
#include "iic.h"
#include "rtc.h"

#define RTC_SLAVE_ADDR 0x32
#define REG_SECONDS 0x0
#define REG_MINUTES 0x1
#define REG_HOURS 0x2
#define REG_CTRL1 0xE
#define REG_CTRL2 0xF

#define CMD_CNT_SECONDS 0x24
#define CMD_24H_MODE 0x20
#define CMD_CLOCK_EN 0x00

// slave address is 0x32, but to read/write:
// 0x64 for write (<<1) + 0
// 0x65 for read (<<1) + 1

//binary coded decimal conv methods
static uint8_t dec_to_bcd(uint8_t dec) {
    return ((dec/10) << 4  | (dec%10));
}

static uint8_t bcd_to_dec(uint8_t bcd) {
    return 10*(bcd >> 4) + (bcd & 0xf);
}

void rtc_write_reg(uint8_t addr, uint8_t data){
    iic_start();
    iic_write((RTC_SLAVE_ADDR<<1)|0);
    iic_write(addr<<4);
    iic_write(data);
    iic_stop();   
}

void rtc_read_reg(uint8_t addr, uint8_t* buf, uint8_t buf_len) {
    iic_start();
    iic_write((RTC_SLAVE_ADDR<<1)|0);
    iic_write(addr<<4);
    iic_restart();
    iic_write((RTC_SLAVE_ADDR<<1)|1);
    
    for (uint8_t i=0; i < buf_len; i++) {
        buf[i] = (i<buf_len-1) ? iic_read_ack() : iic_read_nack(); // send no ack on last
    }
    
    iic_stop();
}


void rtc_init() {
    rtc_write_reg(REG_CTRL1, CMD_CNT_SECONDS);
    rtc_write_reg(REG_CTRL2, CMD_24H_MODE|CMD_CLOCK_EN);
}

void rtc_set_time(rtc_time_t* time) {
    uint8_t time_buf[3];
    time_buf[0]=dec_to_bcd(time->second);
    time_buf[1]=dec_to_bcd(time->minute);
    time_buf[2]=dec_to_bcd(time->hour);
    
    iic_start();
    iic_write((RTC_SLAVE_ADDR<<1)|0); // or wont do anything
    iic_write(REG_SECONDS<<4);
    iic_write(time_buf[0]);
    iic_write(time_buf[1]);
    iic_write(time_buf[2]);
    iic_stop();
}

void rtc_get_time(rtc_time_t* time) {
    uint8_t time_buf[3];
    rtc_read_reg(REG_SECONDS, time_buf,3);
    time->second=bcd_to_dec(time_buf[0]);
    time->minute=bcd_to_dec(time_buf[1]);
    time->hour=bcd_to_dec(time_buf[2]);
}

// TODO: GET/SET DATE


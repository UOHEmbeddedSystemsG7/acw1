#include "eeprom.h"
#include "iic.h"

#define M2408_E2 0
#define EEPROM_WRITE_TIMEOUT_MS 7u

// https://www.st.com/resource/en/datasheet/m24c08-r.pdf


// i2c slave addr is 1010EAAR
// A = top two bits on 10 bit addr
// R = read/write bit, 1 for read
// E = E2, must be set to 0 for any operation

// We have an 10 bit address internal address
// the two MSB are put into the address byte
// EEPROM has 1K * 8 bit (1024B) of memory


static uint8_t _M24C08_build_write_addr(uint32_t addr) {
    uint8_t top_two = (addr >> 8) & 0x03;
    
    //                      ADDR |        ENABLE BIT | TOP TWO BITS | WRITE(0)
    return (uint8_t)((0b1010 << 4) | (M2408_E2 << 3) | (top_two<<1) | 0);
}

static uint8_t _M24C08_build_read_addr(uint32_t addr) {
    uint8_t top_two = (addr >> 8) & 0x03;
    
    //                      ADDR    |     ENABLE BIT | TOP TWO BITS | READ(1)
    return (uint8_t)((0b1010 << 4) | (M2408_E2 << 3) | (top_two<<1) | 1);
}

void eeprom_write_byte(uint32_t addr, uint8_t data) {
    uint8_t device_write = _M24C08_build_write_addr(addr);
    uint8_t addr_lsb = (uint8_t)(addr & 0xff); // extract lower byte.
    uint8_t attempts = 0;
    
    // write to address (3 bytes total)
    iic_start();
    iic_write(device_write);
    iic_write(addr_lsb);
    iic_write(data);
    iic_stop();
    
    // After write, EEPROM goes into write cycle, 
    // SDA is disabled, will ignore all,
    // Per datasheet, write should fail after 5ms
    
    // this will break when device acks, or when its write is done.
    while (1) {
        iic_start();
        
        // if ack'd, stop
        if (iic_write(device_write)) {
            iic_stop();
            break;
        }
        iic_stop();
        __delay_ms(1);
        if (attempts > EEPROM_WRITE_TIMEOUT_MS) {
            break;
        }
        attempts++;
         
    }
}

uint8_t eeprom_read_byte(uint32_t addr) {
    uint8_t write_addr = _M24C08_build_write_addr(addr);
    uint8_t read_addr = _M24C08_build_read_addr(addr);
    
    uint8_t addr_lsb = (uint8_t)(addr & 0xff); // extract lower byte
    uint8_t read_byte;
    
    // send address to read from
    iic_start();
    iic_write(write_addr);
    iic_write(addr_lsb);
    iic_restart();
    
    // read
    iic_write(read_addr);
    read_byte = iic_read_nack();
    iic_stop();
    
    return read_byte;
}
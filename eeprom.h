#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 
/* 
 * File:   eeprom.h
 * Author: 719588
 *
 * Created on 24 November 2025, 15:07
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

    
void eeprom_write_byte(uint16_t addr, uint8_t data);
uint8_t eeprom_read_byte(uint16_t addr);


//const uint16_t EEPROM_ADDR_COUNTER = 0x0000;
const uint16_t EEPROM_ADDR_TEMP_UPPER = 0x0001;
const uint16_t EEPROM_ADDR_TEMP_LOWER = 0x0002;
const uint16_t EEPROM_ADDR_ALARM_SEL = 0x0005;
const uint16_t EEPROM_ADDR_HEAT_OFF = 0x0006;


const uint16_t EEPROM_ADDR_TEMP_START_H = 0x0100;
const uint16_t EEPROM_ADDR_TEMP_START_M = 0x0200;

const uint16_t EEPROM_ADDR_TEMP_END_H = 0x0300;
const uint16_t EEPROM_ADDR_TEMP_END_M = 0x0400;

const uint16_t EEPROM_ADDR_ALARM_H = 0x0050;
const uint16_t EEPROM_ADDR_ALARM_M = 0x0060;




#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */


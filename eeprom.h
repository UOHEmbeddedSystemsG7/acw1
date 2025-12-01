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


#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */


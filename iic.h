#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 
/* 
 * File:   iic.h
 * Author: 719588
 *
 * Created on 14 November 2025, 10:28
 */

#ifndef IIC_H
#define	IIC_H

#ifdef	__cplusplus
extern "C" {
#endif

void iic_init(uint32_t freq);
void iic_start();
void iic_restart();
void iic_stop();
uint8_t iic_write(uint8_t data);
uint8_t iic_read_ack();
uint8_t iic_read_nack();

void eeprom_write_byte(uint16_t addr, uint8_t data);
uint8_t eeprom_read_byte(uint16_t addr);


uint8_t press_ra4();
uint8_t press_ra5();

 




#ifdef	__cplusplus
}
#endif

#endif	/* IIC_H */


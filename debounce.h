
/*
 * File:   iic.h
 * Author: 719588
 *
 * Created on 14 November 2025, 10:28
 */

#ifndef DB_H
#define DB_H

#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif

#ifdef __cplusplus
extern "C" {
#endif

uint8_t btn_dec();
uint8_t btn_inc();
uint8_t btn_sel();
uint8_t btn_cyc();
    
//uint8_t press_ra4() {
//  return debounce(PORTBbits.RB4);
//}
//
//uint8_t press_ra5() {
//  return debounce(PORTBbits.RB5);
//}
//
//uint8_t debounce(unsigned char bit);

#ifdef __cplusplus
}
#endif

#endif /* IIC_H */

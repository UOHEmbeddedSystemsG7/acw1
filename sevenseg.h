#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 

/* 
 * File:   sevenseg.h
 * Author: 719588
 *
 * Created on November 5, 2025, 12:48 PM
 */

#ifndef SEVENSEG_H
#define	SEVENSEG_H

#ifdef	__cplusplus
extern "C" {
#endif

const uint8_t digits[11];
uint8_t _disp[4];
void xiiseg_init();
void xiiseg_display(uint8_t index, uint8_t value);
void xiiseg_display_temp(uint16_t value);
void mult_disp();

    


#ifdef	__cplusplus
}
#endif

#endif	/* SEVENSEG_H */


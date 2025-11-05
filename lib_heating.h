#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 

/* 
 * File:   lib_heating.h
 * Author: 719588
 *
 * Created on November 5, 2025, 12:48 PM
 */

#ifndef HEATING_H
#define	HEATING_H

#ifdef	__cplusplus
extern "C" {
#endif

void heating_init() { TRISE = (1<<7) | TRISE; }
void heating_on() { PORTE = PORTE | (1 << 7) }
void heating_off() { PORTE = PORTE | (0 << 7) }
    


#ifdef	__cplusplus
}
#endif

#endif	/* SEVENSEG_H */


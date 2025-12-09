#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 

/* 
 * File:   heating.h
 * Author: 719077
 *
 * Created on 05 December 2025, 12:17
 */

// global variables for limits of heating
// temp accurate to 1 degree

#ifndef HEATING_H
#define	HEATING_H

#ifdef	__cplusplus
extern "C" {
#endif
/*  
const uint16_t EEPROM_ADDR_TEMP_UPPER = 0x0001;
const uint16_t EEPROM_ADDR_TEMP_LOWER = 0x0002;
*/
    

void heating_on(); // turns RA7 - RA4 top 4 bits
void heating_off();
void heating_logic(uint16_t celsius, rtc_time_t time_now);   // method for when the heating turns on and off
void heating_init();

#ifdef	__cplusplus
}
#endif

#endif	/* HEATING_H */


#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif 
/* 
 * File:   adc.h
 * Author: 719588
 *
 * Created on November 5, 2025, 1:43 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif


uint16_t read_adc();
void adc_init();

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */


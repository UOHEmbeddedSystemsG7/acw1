
#include <xc.h>
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

#ifndef BUZZER_H
#define BUZZER_H

#ifdef __cplusplus
extern "C" {
#endif

// TODO: figure out what this does
// #define _XTAL_FREQ 8000000UL
// #pragma config FOSC = HSMP // 4 to 16 MHz crystal
// #pragma config PLLCFG = OFF
// #pragma config PRICLKEN = ON
// #pragma config FCMEN = OFF
// #pragma config IESO = OFF
// #pragma config PWRTEN = OFF
// #pragma config BOREN = OFF
// #pragma config WDTEN = OFF
// #pragma config PBADEN = OFF
// #pragma config MCLRE = INTMCLR
// #pragma config LVP = OFF

#define WAIT_AFTER_SING 5


void chirp(uint16_t freq, uint8_t duty);
void sing(uint16_t freq, uint16_t duration, uint8_t duty);




// unsigned int j;
// // Initialize RC2 as output
// TRISCbits.TRISC2 = 0; // TRISC2_bit = 0;
// LATCbits.LATC2 = 0;   // LATCbits.LATC2 = 0; // Ensure RC2 starts low

#ifdef __cplusplus
}
#endif

#endif /* IIC_H */

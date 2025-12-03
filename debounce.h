
/*
 * File:   iic.h
 * Author: 719588
 *
 * Created on 14 November 2025, 10:28
 */

#ifndef DB_H
#define DB_H

#include <stdint.h>
#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
  uint8_t last;
  uint8_t stable;
  uint8_t count;
} debounce_state_t;

uint8_t debounce(uint8_t raw, debounce_state_t* state);


#ifdef __cplusplus
}
#endif

#endif /* IIC_H */

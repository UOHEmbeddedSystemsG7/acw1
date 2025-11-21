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

#ifndef DB_H
#define DB_H

#ifdef __cplusplus
extern "C" {
#endif

uint8_t press_ra4() {
  return debounce(RA4_bit);
}

uint8_t press_ra5() {
  return debounce(RA5_bit);
}


inline uint8_t debounce(char bit) {
  static unsigned char last = 0;
  static unsigned char stable = 0;
  static unsigned char count = 0;

  unsigned char raw = bit ? 1u : 0u;

  if (raw == stable) { 
    if (count < 5u)  count++;
  }
  
  else { 
    count = 0; 
    stable = 0;
  }

  if (count >= 5u) {
    if (stable && !last) {
      last = 1;
      return 1;
    }
    if (!stable) last = 0;
  }

}

#ifdef __cplusplus
}
#endif

#endif /* IIC_H */

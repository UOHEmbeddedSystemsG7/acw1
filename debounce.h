<<<<<<< HEAD
<<<<<<< HEAD

=======
#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif
>>>>>>> 2f84105 (resolved main)
=======

>>>>>>> c6cd7da (resolved main.c)
/*
 * File:   iic.h
 * Author: 719588
 *
 * Created on 14 November 2025, 10:28
 */

#ifndef DB_H
#define DB_H

<<<<<<< HEAD
<<<<<<< HEAD
#include <stdint.h>
=======
>>>>>>> c6cd7da (resolved main.c)
#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif

<<<<<<< HEAD
=======
>>>>>>> 2f84105 (resolved main)
=======
>>>>>>> c6cd7da (resolved main.c)
#ifdef __cplusplus
extern "C" {
#endif

<<<<<<< HEAD
<<<<<<< HEAD

typedef struct {
  uint8_t last;
  uint8_t stable;
  uint8_t count;
} debounce_state_t;

uint8_t debounce(uint8_t raw, debounce_state_t* state);

=======
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
>>>>>>> 2f84105 (resolved main)
=======
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
>>>>>>> c6cd7da (resolved main.c)

#ifdef __cplusplus
}
#endif

#endif /* IIC_H */

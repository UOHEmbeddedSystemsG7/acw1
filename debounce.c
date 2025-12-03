#include <builtins.h>
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 02f09a5 (resolved iic)
#include <stdint.h>
#include "debounce.h"


uint8_t debounce(uint8_t raw, debounce_state_t* state) {
  if (raw == state->stable) {
      if (state->count < 5u) state->count++;
  }

  else {
    state->count = 0;
    state->stable = raw;
  }

  if (state->count >= 5u) {

    if (state->stable && !state->last) {
      state->last = 1;
      return 1;
    }

    if (!state->stable) state->last = 0;
  }

  return 0;
<<<<<<< HEAD
}
=======
#include "debounce.h"

uint8_t btn_dec() {
  static unsigned char last = 0;
  static unsigned char stable = 0;
  static unsigned char count = 0;

  unsigned char raw = PORTCbits.RC7 ? 1u : 0u;

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

uint8_t btn_sel() {
  static unsigned char last = 0;
  static unsigned char stable = 0;
  static unsigned char count = 0;

  unsigned char raw = PORTCbits.RC1 ? 1u : 0u;

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

uint8_t button_increment() {
  static unsigned char last = 0;
  static unsigned char stable = 0;
  static unsigned char count = 0;

  unsigned char raw = PORTCbits.RC7 ? 1u : 0u;

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

uint8_t button_cyc() {
  static unsigned char last = 0;
  static unsigned char stable = 0;
  static unsigned char count = 0;

  unsigned char raw = PORTCbits.RC0 ? 1u : 0u;

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

// TODO: figure out how to do this so we dont have to copy stuff about
//uint8_t debounce(uint8_t bit) {
//  static unsigned char last = 0;
//  static unsigned char stable = 0;
//  static unsigned char count = 0;
//
//  unsigned char raw = bit ? 1u : 0u;
//
//  if (raw == stable) { 
//    if (count < 5u)  count++;
//  }
//  
//  else { 
//    count = 0; 
//    stable = 0;
//  }
//
//  if (count >= 5u) {
//    if (stable && !last) {
//      last = 1;
//      return 1;
//    }
//    if (!stable) last = 0;
//  }
//
//}
>>>>>>> c6cd7da (resolved main.c)
=======
}
>>>>>>> 02f09a5 (resolved iic)

#include <builtins.h>
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
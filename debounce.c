#include <builtins.h>
#include "debounce.h"

typedef struct {
  unsigned char last;
  unsigned char stable;
  unsigned char count;
} debounce_state_t;


inline uint8_t debounce(unsigned char raw, debounce_state_t state) {
  if (raw == state.stable) { 
      if (state.count < 5u) state.count++;
  } 
  
  else { 
    state.count = 0; 
    state.stable = raw;
  }

  if (state.count >= 5u) {
      
    if (state.stable && !state.last) {
      state.last = 1;
      return 1;
    }
    
    if (!state.stable) state.last = 0;
  }

  return 0;
}

uint8_t btn_dec() {
  static debounce_state_t state = {0, 0, 0};
  unsigned char raw = PORTCbits.RC7 ? 1u : 0u;
  return debounce(raw, state);
}

uint8_t btn_sel() {
  static debounce_state_t state = {0, 0, 0};
  unsigned char raw = PORTCbits.RC1 ? 1u : 0u;
  return debounce(raw, state);
}

uint8_t button_increment() {
  static debounce_state_t state = {0, 0, 0};
  unsigned char raw = PORTCbits.RC7 ? 1u : 0u;
  return debounce(raw, state);
}

uint8_t button_cyc() {
  static debounce_state_t state = {0, 0, 0};
  unsigned char raw = PORTCbits.RC0 ? 1u : 0u;
  return debounce(raw, state);
}

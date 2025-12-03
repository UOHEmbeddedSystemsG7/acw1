#include <builtins.h>
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
}
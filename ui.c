#include "ui.h"
#include <builtins.h>
#include <stdint.h>
#include "debounce.h"

uint8_t btn_dec() {
  uint8_t raw = PORTCbits.RC6 ? 1u : 0u;
  return debounce(raw, &state_dec);
}

uint8_t btn_sel() {
  uint8_t raw = PORTCbits.RC1 ? 1u : 0u;
  return debounce(raw, &state_sel);
}

uint8_t btn_inc() {
  uint8_t raw = PORTCbits.RC7 ? 1u : 0u;
  return debounce(raw, &state_inc);
}

uint8_t btn_cyc() {
  uint8_t raw = PORTCbits.RC0 ? 1u : 0u;
  return debounce(raw, &state_cyc);
}

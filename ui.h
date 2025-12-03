

#ifndef UI_H
#define UI_H

#include "debounce.h"
#include <stdint.h>
#ifndef MCC
#include "mcc_generated_files/system/system.h"
#define MCC
#endif

#ifdef __cplusplus
extern "C" {
#endif

static debounce_state_t state_cyc = {0, 0, 0};
static debounce_state_t state_sel = {0, 0, 0};
static debounce_state_t state_inc = {0, 0, 0};
static debounce_state_t state_dec = {0, 0, 0};

uint8_t btn_cyc();
uint8_t btn_sel();
uint8_t btn_inc();
uint8_t btn_dec();


#ifdef __cplusplus
}
#endif

#endif /* IIC_H */

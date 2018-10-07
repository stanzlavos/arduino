#ifndef __UTILS_GEN__
#define __UTILS_GEN__

#include <Arduino.h>
#include "utils_defs.h"
#include <pins_arduino.h>

static inline void blink_led(uint8_t cnt) {
  for (int i = 0; i < cnt; i++) {
    digitalWrite(2, LOW);
    delay(500);
    digitalWrite(2, HIGH);
    delay(500);
  }
}

static inline void fast_blink_led(uint8_t cnt) {
  for (int i = 0; i < cnt; i++) {
    digitalWrite(2, LOW);
    delay(200);
    digitalWrite(2, HIGH);
    delay(200);
  }
}

static inline void dev_reset(void) {
  blink_led(3);
  ESP.restart();
}

uint8_t get_op_mode(void);
void set_op_mode(uint8_t);

#endif // __UTILS_GEN__

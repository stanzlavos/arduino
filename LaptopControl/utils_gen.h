#ifndef __UTILS_GEN__
#define __UTILS_GEN__

#include <Arduino.h>
#include "utils_defs.h"
#include "utils_rgb.h"
#include <pins_arduino.h>

#define ON_BOARD_LED

static inline void blink_led(uint8_t cnt) {

#ifdef ON_BOARD_LED
  for (int i = 0; i < cnt; i++) {
    digitalWrite(2, LOW);
    delay(500);
    digitalWrite(2, HIGH);
    delay(500);
  }
#else
    rgb_blink(LED_GREEN, 500, cnt);
#endif

}

static inline void fast_blink_led(uint8_t cnt) {
  
#ifdef ON_BOARD_LED
  for (int i = 0; i < cnt; i++) {
    digitalWrite(2, LOW);
    delay(200);
    digitalWrite(2, HIGH);
    delay(200);
  }
#else
  rgb_blink(LED_RED, 200, cnt);
#endif

}

static inline void dev_reset(void) {
  /*blink_led(3);*/
  rgb_blink(LED_RED, 500, 3);
  ESP.restart();
}

uint8_t get_op_mode(void);
void set_op_mode(uint8_t);

#endif // __UTILS_GEN__

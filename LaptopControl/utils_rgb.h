#ifndef __UTILS_RGB__
#define __UTILS_RGB__

#include "config.h"

#ifdef RGB_IN_USE

#include <stdint.h>
#include "Arduino.h"
#include <pins_arduino.h>

#define LED_R   D5
#define LED_G   D6
#define LED_B   D7

typedef enum {
  LED_RED,
  LED_GREEN,
  LED_BLUE,
  /* Add new below */

  LED_BLACK,
  
  LED_MAX
} led_colour_t;

void setup_rgb(void);
void rgb_cntrl(led_colour_t led, bool on_off);
void rgb_blink(led_colour_t led, uint16_t delay_time_ms, uint16_t cnt);
void rgb_cycle(uint8_t cnt, uint16_t delay_time_ms);

#endif // RGB_IN_USE

#endif // __UTILS_RGB__

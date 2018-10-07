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

void setup_rgb(void);
void rgb_r_cntrl(bool);
void rgb_g_cntrl(bool);
void rgb_b_cntrl(bool);
void rgb_test();

#endif // RGB_IN_USE

#endif // __UTILS_RGB__

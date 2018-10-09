#include "utils_laptop.h"
#include "utils_rgb.h"

bool laptop_status = false;

bool is_laptop_on(void) {
  return laptop_status;
}

led_colour_t get_laptop_power_status(void) {
  led_colour_t led = LED_MAX;
/*
  if (is_black()) {
    led = LED_BLACK;
    laptop_status = false;
  } 
  else if (is_green()) {
    led = LED_BLACK;
    laptop_status = true;
  } 
*/

  return led;
}

void handle_laptop(void) {
  led_colour_t led = get_laptop_power_status();

  if (led != LED_MAX)
    rgb_cntrl(led, true);
  else
    rgb_blink(LED_RED, 200, 1);
}

void turn_on_laptop(void) {
  
}

void turn_off_laptop(void) {
  
}

void hard_reset_laptop(void) {
  
}


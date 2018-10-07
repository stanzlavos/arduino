#include "utils_tv.h"
#include "utils_rgb.h"
#include "utils_colour.h"

bool tv_status = false;

bool is_tv_on(void) {
  return tv_status;
}

led_colour_t get_tv_led_status(void) {
  led_colour_t led = LED_MAX;

  if (is_black()) {
    led = LED_BLACK;
    tv_status = true;
  } 
  else if (is_blue()) {
    led = LED_BLUE;
    tv_status = false;
  } 
  /*else if (is_red()) {
    led = LED_RED;
  }*/

  return led;
}

void handle_tv(void) {
  led_colour_t led = get_tv_led_status();

  if (led != LED_MAX)
    rgb_cntrl(led, true);
  else
    rgb_blink(LED_RED, 200, 1);
}

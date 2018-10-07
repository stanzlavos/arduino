#include "utils_speaker.h"
#include "utils_rgb.h"
#include "utils_colour.h"

bool speaker_status = false;

bool is_speaker_on(void) {
  return speaker_status;
}

led_colour_t get_speaker_led_status(void) {
  led_colour_t led = LED_MAX;

  if (is_black()) {
    led = LED_BLACK;
    speaker_status = false;
  } 
  else if (is_green()) {
    led = LED_BLACK;
    speaker_status = true;
  } 
  /*else if (is_red()) {
    led = LED_RED;
  }*/

  return led;
}

void handle_speaker(void) {
  led_colour_t led = get_speaker_led_status();

  if (led != LED_MAX)
    rgb_cntrl(led, true);
  else
    rgb_blink(LED_RED, 200, 1);
}

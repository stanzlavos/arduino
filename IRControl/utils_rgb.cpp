#include "utils_rgb.h"

#ifdef RGB_IN_USE

void setup_rgb(void) {
  pinMode(LED_R, OUTPUT);
  digitalWrite(LED_R, HIGH);

  pinMode(LED_G, OUTPUT);
  digitalWrite(LED_G, HIGH);

  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_B, HIGH);
}

void rgb_r_cntrl(bool val) {
  if (val)
    digitalWrite(LED_R, LOW);
  else
    digitalWrite(LED_R, HIGH);  
}

void rgb_g_cntrl(bool val) {
  if (val)
    digitalWrite(LED_G, LOW);
  else
    digitalWrite(LED_G, HIGH);
}

void rgb_b_cntrl(bool val) {
  if (val)
    digitalWrite(LED_B, LOW);
  else
    digitalWrite(LED_B, HIGH);
}

void rgb_test(void) {
  uint8_t i = 3;
  
  while(i > 0) {

    rgb_r_cntrl(true);
    delay(200);
    rgb_r_cntrl(false);
    delay(200);

    rgb_g_cntrl(true);
    delay(200);
    rgb_g_cntrl(false);
    delay(200);

    rgb_b_cntrl(true);
    delay(200);
    rgb_b_cntrl(false);
    delay(200);
    
    i--;
  }
}

#endif // RGB_IN_USE

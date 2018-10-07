#include "utils_rgb.h"

#ifdef RGB_IN_USE

led_colour_t led_status = LED_BLACK;

void setup_rgb(void) {
  pinMode(LED_R, OUTPUT);
  digitalWrite(LED_R, HIGH);

  pinMode(LED_G, OUTPUT);
  digitalWrite(LED_G, HIGH);

  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_B, HIGH);

  rgb_cycle(3, 200);
}

led_colour_t get_led_status(void) {
	return led_status;
}

void rgb_bl_cntrl(void);

void rgb_r_cntrl(bool val) {
  rgb_bl_cntrl();
  if (val) {
    digitalWrite(LED_R, LOW);
    led_status = LED_RED;
  }
  else
    rgb_bl_cntrl();
}

void rgb_g_cntrl(bool val) {
  rgb_bl_cntrl();
  if (val) {
    digitalWrite(LED_G, LOW);
    led_status = LED_GREEN;
  }
  else
    rgb_bl_cntrl();
}

void rgb_b_cntrl(bool val) {
  rgb_bl_cntrl();
  if (val) {
    digitalWrite(LED_B, LOW);
    led_status = LED_BLUE;
  }
  else
	  rgb_bl_cntrl();
}

void rgb_bl_cntrl(void) {
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, HIGH);
  led_status = LED_BLACK;
}

void rgb_cntrl(led_colour_t led, bool val) {
    switch(led) {
      case LED_RED:
        rgb_r_cntrl(val);
        break;
          
      case LED_GREEN:
        rgb_g_cntrl(val);
        break;
        
      case LED_BLUE:
        rgb_b_cntrl(val);
        break;

      case LED_BLACK:
    	  rgb_bl_cntrl();
    	break;
    }
}

void rgb_cycle(uint8_t cnt, uint16_t delay_time_ms) {
  led_colour_t prev = get_led_status();
  rgb_bl_cntrl();

  for(uint8_t i=0; i<cnt; i++) {
    for(uint8_t led=LED_RED; led<=LED_BLUE; led++) {
      rgb_cntrl((led_colour_t)led, true);
      delay(delay_time_ms);
      rgb_cntrl((led_colour_t)led, false);
      delay(delay_time_ms);  
    }
  }

  rgb_cntrl(prev, true);
}

void rgb_blink(led_colour_t led, uint16_t delay_time, uint16_t cnt) {
	led_colour_t prev = get_led_status();
	bool forever = (cnt == 0);
	rgb_bl_cntrl();

	while(true) {
		rgb_cntrl((led_colour_t)led, true);
		delay(delay_time);
		rgb_cntrl((led_colour_t)led, false);
		delay(delay_time);

		if(!forever) {
			if(--cnt == 0)
				break;
		}
	}

	rgb_cntrl(prev, true);
}

#endif // RGB_IN_USE

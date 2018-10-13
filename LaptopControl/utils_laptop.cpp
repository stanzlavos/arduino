#include "utils_laptop.h"
#include "utils_rgb.h"
#include "utils_debug.h"

#define LAPTOP_CNTRL_PIN      D1
#define LAPTOP_ON_OFF_DELAY   100
#define LAPTOP_RESET_DELAY    10000
#define LAPTOP_STATUS_INTRVL  1000

bool laptop_status = false;
unsigned long prev_check_time = 0;

bool is_laptop_on(void) {
  return laptop_status;
}

void setup_laptop(void) {
  prev_check_time = millis();
  pinMode(A0, INPUT);

  digitalWrite(LAPTOP_CNTRL_PIN, LOW);
  pinMode(LAPTOP_CNTRL_PIN, OUTPUT);
  digitalWrite(LAPTOP_CNTRL_PIN, LOW);
}

led_colour_t get_laptop_power_status(void) {
  led_colour_t led = LED_MAX;

  int raw = analogRead(A0);
  float voltage = raw * (1 / 1023.0);

  T_PRINT("Analog read : ")
  T_PRINTLN(voltage)
    
  if (voltage < 0.3) {
    led = LED_BLACK;
    laptop_status = false;
  } 
  else {
    led = LED_BLACK;
    laptop_status = true;
  } 

  return led;
}

void handle_laptop(void) {
  unsigned long curr_time = millis();
  if((curr_time - prev_check_time) > LAPTOP_STATUS_INTRVL) {
    prev_check_time = curr_time;
    
    led_colour_t led = get_laptop_power_status();
  
    if (led != LED_MAX)
      rgb_cntrl(led, true);
    else
      rgb_blink(LED_RED, 200, 1);
  }
}

void turn_on_laptop(void) {
  if(!is_laptop_on()) {
    digitalWrite(LAPTOP_CNTRL_PIN, HIGH);
    delay(LAPTOP_ON_OFF_DELAY);
    digitalWrite(LAPTOP_CNTRL_PIN, LOW);  
  }
}

void turn_off_laptop(void) {
  if(is_laptop_on()) {
    digitalWrite(LAPTOP_CNTRL_PIN, HIGH);
    delay(LAPTOP_ON_OFF_DELAY);
    digitalWrite(LAPTOP_CNTRL_PIN, LOW);  
  }
}

void hard_reset_laptop(void) {
  digitalWrite(LAPTOP_CNTRL_PIN, HIGH);
  delay(LAPTOP_RESET_DELAY);
  digitalWrite(LAPTOP_CNTRL_PIN, LOW);  
}


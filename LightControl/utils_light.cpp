#include "utils_light.h"

#ifdef LIGHT_IN_USE

#include <stdint.h>
#include <pins_arduino.h>
#include "utils_debug.h"
#include "utils_rtc.h"

#define DEV_TYPE      "light"
#define DEV_NAME      "front"

#define LIGHT_PIN           D7
#define TIME_INVALID        61
#define TIME_INVALID_RETRY  2

typedef enum {
  LIGHT_ON,
  LIGHT_OFF,
  LIGHT_AUTO
} light_status_t;

light_status_t light_status = LIGHT_AUTO;

uint8_t on_time_hour  = 0;
uint8_t on_time_min   = 0;
uint8_t off_time_hour = 0;
uint8_t off_time_min  = 0;

uint8_t curr_min = TIME_INVALID;

static bool is_valid_time(uint8_t time_hour, uint8_t time_min) {
  bool is_valid_hour = (time_hour <= 23);
  bool is_valid_min = (time_min <= 59);

  return (is_valid_hour && is_valid_min);
}

static bool is_auto_on_time(void) {
  bool ret = false;
  static uint8_t time_invalid_cnt = 0;
  
  uint8_t tmp_hour = rtc_get_hours();
  uint8_t tmp_min = rtc_get_minutes();

  if(!is_valid_time(tmp_hour, tmp_min)) {
    if(TIME_INVALID_RETRY == ++time_invalid_cnt) {
      T_PRINTLN("Invalid RTC time.... Restarting !!!")
      ESP.restart();  
    }
  }

  //T_PRINT(tmp_hour);
  //T_PRINT(" : ");
  //T_PRINTLN(tmp_min);

  uint16_t tmp_tot_min = (tmp_hour * 60) + tmp_min;
  uint16_t on_tot_min = (on_time_hour * 60) + on_time_min;
  uint16_t off_tot_min = (off_time_hour * 60) + off_time_min;

  if((tmp_tot_min >= on_tot_min) && (tmp_tot_min <= off_tot_min))
    ret = true;

  //T_PRINTLN(tmp_tot_min);
  //T_PRINTLN(on_tot_min);
  //T_PRINTLN(off_tot_min);
  
  return ret;
}

bool accept_msg(char *dev_type, char *dev_name) {
  if((dev_type == NULL) || (dev_name == NULL))
    return false;
    
  return((strcmp(dev_type, DEV_TYPE) == 0) && (strcmp(dev_name, DEV_NAME) == 0));
}

void setup_light(void)
{
  pinMode(LIGHT_PIN, OUTPUT);
  digitalWrite(LIGHT_PIN, HIGH);

  curr_min = TIME_INVALID;
}

void turn_light_on(void) {
  digitalWrite(LIGHT_PIN, LOW);
}

void turn_light_off(void) {
  digitalWrite(LIGHT_PIN, HIGH);
}

void set_light_status(bool onoff) {
  if(onoff)
    light_status = LIGHT_ON;
  else
    light_status = LIGHT_OFF;
}

void turn_light_auto(void) {
  light_status = LIGHT_AUTO;
  curr_min = TIME_INVALID;  
}

void handle_light(void) {
  if(light_status == LIGHT_AUTO) {
    uint8_t tmp_min = rtc_get_minutes();
    
    if(curr_min != tmp_min) {
      curr_min = tmp_min;

      if(is_auto_on_time()) {
        turn_light_on();        
      } else {
        turn_light_off();
      }
    }
  }
}

#endif

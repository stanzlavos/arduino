#include "utils_rtc.h"

#ifdef RTC_IN_USE

#include <Wire.h>
#include "DS3231.h"

RTClib RTC;
DS3231 Clock;

void setup_rtc(void) {
  Wire.begin();
}

uint8_t rtc_get_hours(void) {
  DateTime now = RTC.now();

  return (now.hour());
}

uint8_t rtc_get_minutes(void) {
  DateTime now = RTC.now();

  return (now.minute());
}

uint8_t rtc_get_seconds(void) {
  DateTime now = RTC.now();

  return (now.second());
}

#endif

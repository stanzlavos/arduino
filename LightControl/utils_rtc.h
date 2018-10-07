#ifndef __UTILS_RTC__
#define __UTILS_RTC__

#include "config.h"

#ifdef RTC_IN_USE

#include <stdint.h>

void setup_rtc(void);

uint8_t rtc_get_hours(void);
uint8_t rtc_get_minutes(void);
uint8_t rtc_get_seconds(void);

#endif // RTC_IN_USE

#endif // __UTILS_RTC__

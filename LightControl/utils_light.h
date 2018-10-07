#ifndef __UTILS_LIGHT__
#define __UTILS_LIGHT__

#include "config.h"

#ifdef LIGHT_IN_USE

typedef enum
{
  DEV_TV                  = 0,
  DEV_TV_MUTE,
  DEV_TV_VOL_UP,
  DEV_TV_VOL_DOWN,
  
  DEV_SPEAKER             = 16,
  DEV_SPEAKER_MUTE,
  DEV_SPEAKER_VOL_UP,
  DEV_SPEAKER_VOL_DOWN,

  DEV_LAPTOP              = 32,
  DEV_ENTRTNMNT_UNIT,
  
  DEV_LIGHT_ON            = 48,
  DEV_LIGHT_OFF,
  DEV_LIGHT_AUTO,

  DEV_RESET               = 8192,
  DEV_UPDATE_SKETCH,
  DEV_UPDATE_DATA,
  
  DEV_MAX
};

void setup_light(void);
void handle_light(void);
bool accept_msg(char *dev_type, char *dev_name);

void turn_light_on(void);
void turn_light_off(void);
void turn_light_auto(void);
void set_light_status(bool onoff);

#endif // LIGHT_IN_USE

#endif // __UTILS_LIGHT__

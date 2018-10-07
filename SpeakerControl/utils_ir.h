
#ifndef __UTILS_IR__
#define __UTILS_IR__

#include "config.h"

#ifdef IR_IN_USE

typedef enum
{
  DEV_SPEAKER_ON               = 0,
  DEV_SPEAKER_OFF,
  DEV_SPEAKER_MUTE,
  DEV_SPEAKER_UNMUTE,
  DEV_SPEAKER_VOL_UP,
  DEV_SPEAKER_VOL_DOWN,
  DEV_SPEAKER_VOL_MAX,
  DEV_SPEAKER_VOL_MIN,
  
  DEV_RESET               = 8192,
  DEV_UPDATE_SKETCH,
  DEV_UPDATE_DATA,
  
  DEV_MAX
};

void setup_ir(void);
void handle_ir_recv(void);

void turn_on_speaker(void);
void turn_off_speaker(void);
void speaker_mute(void);
void speaker_unmute(void);
void speaker_vol_up(void);
void speaker_vol_down(void);
void speaker_vol_min(void);
void speaker_vol_max(void);


#endif // IR_IN_USE

#endif // __UTILS_IR__

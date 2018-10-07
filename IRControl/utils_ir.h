#ifndef __UTILS_IR__
#define __UTILS_IR__

#include "config.h"

#ifdef IR_IN_USE

typedef enum
{
  DEV_TV_ON               = 0,
  DEV_TV_OFF,
  DEV_TV_MUTE,
  DEV_TV_UNMUTE,
  DEV_TV_VOL_UP,
  DEV_TV_VOL_DOWN,
  
  DEV_RESET               = 8192,
  DEV_UPDATE_SKETCH,
  DEV_UPDATE_DATA,
  
  DEV_MAX
};

void setup_ir(void);
void handle_ir_recv(void);

void turn_on_tv(void);
void turn_off_tv(void);
void tv_mute(void);
void tv_unmute(void);
void tv_vol_up(void);
void tv_vol_down(void);


#endif // IR_IN_USE

#endif // __UTILS_IR__

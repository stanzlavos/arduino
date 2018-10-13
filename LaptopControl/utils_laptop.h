#ifndef __UTILS_LAPTOP__
#define __UTILS_LAPTOP__

typedef enum
{
  DEV_LAPTOP_ON           = 0,
  DEV_LAPTOP_OFF,
  DEV_LAPTOP_HARD_RESET,
  
  DEV_RESET               = 8192,
  DEV_UPDATE_SKETCH,
  DEV_UPDATE_DATA,
  
  DEV_MAX
};

void setup_laptop(void);
void handle_laptop(void);
bool is_laptop_on(void);
void turn_on_laptop(void);
void turn_off_laptop(void);
void hard_reset_laptop(void);

#endif // __UTILS_LAPTOP__

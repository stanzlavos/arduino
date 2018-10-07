#ifndef __UTILS_DEVICES__
#define __UTILS_DEVICES__

typedef enum {
  DEV_FIRST,
  DEV_SPEAKER = DEV_FIRST,
  DEV_LAPTOP,

  DEV_MAXX
} devices_t;

bool handle_attached_devices(char *cmd, char *dev_type, char *dev_name);

bool entrtnmnt_unit_on(void);
bool entrtnmnt_unit_off(void);

#endif // __UTILS_DEVICES__

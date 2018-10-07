#ifndef __UTILS_FAUXMO__
#define __UTILS_FAUXMO__

#include "config.h"

#ifdef FAUXMO_IN_USE

typedef enum
{
  ID_TELEVISION,
  ID_TV,
  ID_SPEAKER,
  ID_LAPTOP,
  ID_ENTERTNMNT_UNIT
} fauxmo_dev_id_t;

void setup_fauxmo(void);
void handle_fauxmo(void);

#endif // FAUXMO_IN_USE

#endif // __UTILS_FAUXMO__

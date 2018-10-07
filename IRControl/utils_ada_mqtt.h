#ifndef __UTILS_ADA_MQTT__
#define __UTILS_ADA_MQTT__

#include "config.h"

#ifdef ADA_MQTT_IN_USE

#define DEV_TYPE      "tv"
#define DEV_NAME      "living"

void setup_adamqtt(void);
void handle_adamqtt(void);
void stop_adamqtt(void);

#endif // ADA_MQTT_IN_USE

#endif // __UTILS_ADA_MQTT__

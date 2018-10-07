#ifndef __UTILS_COLOUR__
#define __UTILS_COLOUR__

#include "config.h"

#ifdef COLOUR_IN_USE

void setup_colour(void);
void dump_colour_info(void);
bool is_black(void);
bool is_blue(void);
bool is_red(void);
bool is_green(void);

#endif // COLOUR_IN_USE

#endif // __UTILS_COLOUR__

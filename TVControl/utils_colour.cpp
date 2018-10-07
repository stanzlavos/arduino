#include "utils_colour.h"

#ifdef COLOUR_IN_USE

#define BLACK_LEVEL   5
#define ACCEPT_DIFF   20

#include "utils_debug.h"
#include "utils_rgb.h"
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup_colour(void) {
	if (!tcs.begin()) {
		T_PRINTLN("Colour sensor not deteted !!!");
		rgb_blink(LED_RED, 200, 0);
	} else {
    rgb_blink(LED_GREEN, 200, 3);
	}
}

void dump_colour_info(void){
  uint16_t r, g, b, c, colorTemp, lux;
  
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.println(" - ");Serial.println(" ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.println(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.println(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.println(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.println(" ");
  Serial.println(" ");    
}

bool is_black(void) {
  bool ret = false;
  uint16_t r, g, b, c;
  
  tcs.getRawData(&r, &g, &b, &c);
  
  T_PRINT("R : ");T_PRINT(r);
  T_PRINT(" G : ");T_PRINT(g);
  T_PRINT(" B : ");T_PRINTLN(b);
  T_PRINTLN("");

  if((r <= BLACK_LEVEL) && (g <= BLACK_LEVEL) && (b <= BLACK_LEVEL))
    ret = true;

  return ret;
}

bool is_blue(void) {
  bool ret = false;
  uint16_t r, g, b, c;

  if(!is_black()) {
    tcs.getRawData(&r, &g, &b, &c);  

    int16_t diff = b - r;
    if(diff >= ACCEPT_DIFF) {
      diff = b - g;
      if(diff >= ACCEPT_DIFF) {
        ret = true;  
      }
    }
  }

  return ret;
}

bool is_red(void) {
  bool ret = false;
  uint16_t r, g, b, c;

  if(!is_black()) {
    tcs.getRawData(&r, &g, &b, &c);  

    int16_t diff = r - b;
    if(diff >= ACCEPT_DIFF) {
      diff = r - g;
      if(diff >= ACCEPT_DIFF) {
        ret = true;  
      }
    }
  }

  return ret;
}

bool is_green(void) {
  bool ret = false;
  uint16_t r, g, b, c;

  if(!is_black()) {
    tcs.getRawData(&r, &g, &b, &c);  

    int16_t diff = g - r;
    if(diff >= ACCEPT_DIFF) {
      diff = g - b;
      if(diff >= ACCEPT_DIFF) {
        ret = true;  
      }
    }
  }

  return ret;
}

#endif // COLOUR_IN_USE

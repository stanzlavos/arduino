#ifndef __UTILS_DEBUG__
#define __UTILS_DEBUG__

#include "config.h"
#include <ESP8266WiFi.h>
#include "Arduino.h"

#ifdef TFT_IN_USE
#include "utils_tft.h"
#endif

#define T_PRINT(x)
#define T_PRINTLN(x)
#define PRINT(x)
#define PRINTLN(x)
  
#ifdef DEBUG_PRINT
  #ifdef TFT_IN_USE
    #define T_PRINT(x)    tft_print(x);
    #define T_PRINTLN(x)  {tft_println(x);tft_scroll();}
    #define PRINT(x)      Serial.print(x);
    #define PRINTLN(x)    Serial.println(x);
  #else
    #define PRINT(x)      Serial.print(x);      // For Startup logs
    #define PRINTLN(x)    Serial.println(x);    // For startup logs
    #define T_PRINT(x)    Serial.print(x);
    #define T_PRINTLN(x)  Serial.println(x);

    #ifdef DEBUG_TELNET
      extern WiFiServer  TelnetServer;
      extern WiFiClient  Telnet;
      
      #define T_PRINT(x)    Telnet.print(x);
      #define T_PRINTLN(x)  Telnet.println(x);
    
      void setup_telnet(void);
      void handle_telnet(void);
    #endif
  #endif
#endif

#endif //__UTILS_DEBUG__



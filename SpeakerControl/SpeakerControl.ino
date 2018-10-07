#include "config.h"

extern "C" {
#include "user_interface.h"
}

#ifdef TFT_IN_USE
#include "utils_ui.h"
#include "utils_touch.h"

#ifdef SCREEN_SERVER
#include "utils_screenserver.h"
#endif
#endif

#include "utils_debug.h"

#ifdef BLYNK_IN_USE
#include "utils_blynk.h"
#endif

#ifdef ADA_MQTT_IN_USE
#include "utils_ada_mqtt.h"
#endif

#if defined(ARDUINO_OTA) || defined(HTTP_OTA) || defined(HTTP_SPIFFS_OTA)
#include "utils_ota.h"
#endif

#ifdef NTP_IN_USE
#include "utils_ntp.h"
#endif

#ifdef IR_IN_USE
#include "utils_ir.h"
#endif

#ifdef FAUXMO_IN_USE 
#include "utils_fauxmo.h"
#endif

#ifdef RGB_IN_USE
#include "utils_rgb.h"
#endif

#ifdef COLOUR_IN_USE
#include "utils_colour.h"
#endif

#include "utils_config.h"
#include "utils_gen.h"
#include "utils_wifi.h"
#include "utils_defs.h"
#include "utils_timer.h"
#include "utils_speaker.h"
#include "utils_tcpserver.h"

void setup() {
#ifdef DEBUG_PRINT
  Serial.flush();
  Serial.begin(115200);
  //Serial.setDebugOutput(true);
#endif

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  
#ifdef RGB_IN_USE
  setup_rgb();
#endif

  blink_led(3);

#ifdef COLOUR_IN_USE
  setup_colour();
#endif
  
  init_timer_ring();

#ifdef TFT_IN_USE
  setup_tft();
#endif

#ifdef TOUCH_IN_USE
  setup_TOUCH();
#endif

  add_wifi_dependent_func(setup_tcpserver,    stop_tcpserver,   handle_tcpserver);

#ifdef BLYNK_IN_USE
  add_wifi_dependent_func(setup_blynk, 			  stop_blynk,       handle_blynk);
#endif
#ifdef ADA_MQTT_IN_USE
  add_wifi_dependent_func(setup_adamqtt,      stop_adamqtt,     handle_adamqtt);
#endif
#ifdef DEBUG_TELNET
  add_wifi_dependent_func(setup_telnet, 		  NULL, 			      handle_telnet);
#endif
#ifdef ARDUINO_OTA
  add_wifi_dependent_func(setup_arduino_ota, 	NULL, 			      handle_arduino_ota);
#endif  
#ifdef HTTP_OTA
  add_wifi_dependent_func(NULL, 				      NULL, 			      handle_http_update_loop);
#endif
#ifdef HTTP_SPIFFS_OTA
  add_wifi_dependent_func(NULL, 				      NULL, 			      handle_http_spiffs_update_loop);
#endif
#ifdef FAUXMO_IN_USE  
  add_wifi_dependent_func(setup_fauxmo,       NULL,             handle_fauxmo);
#endif

  SPIFFS.begin();
  if (read_json_cfg())
    setup_wifi();

#ifdef IR_IN_USE
  setup_ir();
#endif

  bool ret = system_update_cpu_freq(160);
  if (ret)
  {
    T_PRINT("CPU Freq : ") 
    T_PRINTLN(system_get_cpu_freq())
  }

  T_PRINTLN("Ready")
  blink_led(3);

#ifdef TFT_IN_USE
  tft_clear();
  setup_ui();
#endif
}

void loop()
{
  handle_speaker();
  
  handle_timer_events();
  
  handle_wifi_funcs();

#ifdef TFT_IN_USE

  handle_touch();

  handle_ui();

#ifdef SCREEN_SERVER

  handle_screen_server();
  
#endif // SCREEN_SERVER

#endif // TFT_IN_USE
}

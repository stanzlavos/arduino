#include "utils_ada_mqtt.h"

#ifdef ADA_MQTT_IN_USE

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "utils_debug.h"
#include "utils_config.h"
#include "utils_gen.h"
#include "utils_timer.h"
#include "utils_light.h"

#define AIO_USERNAME    "stanzlavos"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  8883               // 8883 for https

//#define ADAMQTT_TRIGGER_INTERVAL    5     // in s
#define ADAMQTT_TIMEOUT             4000  // in ms
#define ADAMQTT_RETRIES             5

bool  ada_mqtt_enabled = false;
char  ada_mqtt_key[CONFIG_PARAM_LEN_MAX] = "\0";

#define CMD_STR_LEN     64
#define CMD_TOKENS_MAX  5

#define CMD_IDX         0
#define CMD_DEV_IDX     1
#define CMD_DEV_NAME    2

WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, ada_mqtt_key);

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Subscribe DevOps = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/DevOps", MQTT_QOS_1);

/**************************** Callbacks *************************************/

void DevOpsCallback(char *str, uint16_t len)
{
  char cmd_str[CMD_STR_LEN] = { "\0" };
  char *cmd_tokens[CMD_TOKENS_MAX] = { NULL };
  uint32_t cmd = 0;
  uint8_t cnt = 0;

  strncpy(cmd_str, str, len);
  //T_PRINTLN(cmd_str)

  cmd_tokens[cnt] = strtok(cmd_str, " ");
  cmd = (uint32_t)atol(cmd_tokens[CMD_IDX]);
   
  /* walk through other tokens */
  while(cmd_tokens[cnt] != NULL ) {
    if (cnt == (CMD_TOKENS_MAX - 1))
      break;
    
    cmd_tokens[++cnt] = strtok(NULL, " ");
  }

  if(!accept_msg(cmd_tokens[CMD_DEV_IDX], cmd_tokens[CMD_DEV_NAME]))
    return;
   
  switch(cmd)
  {
    case DEV_LIGHT_ON :
      turn_light_on();
      set_light_status(true);
      break;
      
    case DEV_LIGHT_OFF :
      turn_light_off();
      set_light_status(false);
      break;
      
    case DEV_LIGHT_AUTO:
      turn_light_auto();
      break;

    case DEV_RESET :
      dev_reset();
      break;
      
    case DEV_UPDATE_SKETCH :
      set_op_mode(MODE_OTA);
      blink_led(5);
      break;
      
    case DEV_UPDATE_DATA :
      set_op_mode(MODE_SPIFFS_OTA);
      blink_led(5);
      break;
  }
  
  blink_led(1);
  T_PRINTLN("DevOpsCallback!!!")
}

bool is_adamqtt_connected(void)
{
  return mqtt.connected();
}

static inline void handle_adamqtt_setup(void *)
{
  setup_adamqtt();
}

void stop_adamqtt(void)
{
  mqtt.disconnect();
}

void adamqtt_subscribe(void)
{
  DevOps.setCallback(DevOpsCallback);
  mqtt.subscribe(&DevOps);
}

void setup_adamqtt(void)
{
  static uint8_t reconnect_attempts = 0;
  
  if (ada_mqtt_enabled && !is_adamqtt_connected())
  {
    int8_t ret;
    
    adamqtt_subscribe();

    blink_led(1);
    T_PRINT("Connecting to ADA MQTT...")
    
    if ((ret = mqtt.connect(AIO_USERNAME, ada_mqtt_key)) != 0)
    {
      T_PRINT("ADA MQTT connect failed : ")
      T_PRINTLN(mqtt.connectErrorString(ret));
      
      if(ADAMQTT_RETRIES == reconnect_attempts++) {
        T_PRINTLN("Restarting !!!")
        ESP.restart();      
      }
      
      //T_PRINTLN(AIO_USERNAME);
      //T_PRINTLN(ada_mqtt_key);
      //T_PRINTLN(" ");
      
      stop_adamqtt();

      fast_blink_led(3);
      //add_timer(handle_adamqtt_setup, NULL, ADAMQTT_TRIGGER_INTERVAL, false);
    }
    else
    {
      reconnect_attempts = 0;
      T_PRINTLN("Connected !!!")
    }
  }
}

void handle_adamqtt(void)
{
  mqtt.processPackets(ADAMQTT_TIMEOUT);
  
  // ping the server to keep the mqtt connection alive
  if(!mqtt.ping()) {
    stop_adamqtt();
    
    setup_adamqtt();
  }   
}

#endif // ADA_MQTT_IN_USE

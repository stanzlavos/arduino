#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "utils_tcpserver.h"
#include "utils_debug.h"
#include "utils_rgb.h"
#include "utils_gen.h"
#include "utils_laptop.h"

#define CMD_STR_LEN     64
#define CMD_TOKENS_MAX  5

#define CMD_IDX         0
#define CMD_DEV_IDX     1
#define CMD_DEV_NAME    2

#define SERVER_PORT     1234
#define CLIENT_TIMEOUT  5000  // 2 Sec

#define MSG_OK          "OK"
#define MSG_NOK         "NOK"

WiFiServer server(SERVER_PORT);
WiFiClient client;

void setup_tcpserver(void) {
  server.begin();
  server.setNoDelay(1);  
}

bool accept_msg(char *dev_type, char *dev_name) {
  if((dev_type == NULL) || (dev_name == NULL))
    return false;

  T_PRINT(dev_type);
  T_PRINT(" ");
  T_PRINTLN(strlen(dev_type));
  T_PRINT(dev_name);
  T_PRINT(" ");
  T_PRINTLN(strlen(dev_name));

  return((strcmp(dev_type, DEV_TYPE) == 0) && (strcmp(dev_name, DEV_NAME) == 0));
}

void send_msg(char *msg) {
  client.println(msg);
  client.flush();  
}

void handle_tcpserver(void) {
  char      cmd_str[CMD_STR_LEN] = {"\0"};
  char      *cmd_tokens[CMD_TOKENS_MAX] = { NULL };
  uint32_t  cmd = 0;
  uint8_t   cnt = 0;
  
  client = server.available();
  
  if (client) {
    if (client.connected()) {
      //T_PRINTLN("Connected to client");    
      rgb_cycle(1, 50);

      uint64_t  start_time = millis();
      while(client.available() == 0) {
        if((millis() - start_time) > CLIENT_TIMEOUT)
          break;
      }

      if (client.available() > 0) {
        client.read((uint8_t *)cmd_str, CMD_STR_LEN);
        //T_PRINTLN(cmd_str);

        cmd_tokens[cnt] = strtok(cmd_str, " \n\r");
        cmd = (uint32_t)atol(cmd_tokens[CMD_IDX]);
   
        /* walk through other tokens */
        while(cmd_tokens[cnt] != NULL ) {
          if (cnt == (CMD_TOKENS_MAX - 1))
            break;
    
          cmd_tokens[++cnt] = strtok(NULL, " \n\r");
        }

        if(!accept_msg(cmd_tokens[CMD_DEV_IDX], cmd_tokens[CMD_DEV_NAME])) {
          send_msg(MSG_NOK);
          rgb_blink(LED_RED, 200, 1);
          return;
        }

        switch(cmd)
        {
          case DEV_LAPTOP_ON :
            turn_on_laptop();
            break;
      
          case DEV_LAPTOP_OFF :
            turn_off_laptop();
            break;
        
          case DEV_LAPTOP_HARD_RESET :
            hard_reset_laptop();
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

          default :
            send_msg(MSG_NOK);
            rgb_blink(LED_RED, 200, 1);
            return;
        }

        // Send ACK to client
        send_msg(MSG_OK);
        rgb_blink(LED_GREEN, 500, 1);
      }
    }
  }  
}

void stop_tcpserver(void) {
  server.close();
  server.stop();  
}


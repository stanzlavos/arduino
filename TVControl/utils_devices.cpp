#include "utils_devices.h"
#include "utils_rgb.h"
#include "utils_debug.h"
#include "utils_ir.h"

#define DEV_NAME_LEN        16
#define DEV_IP_LEN          24

#define SERVER_PORT         1234
#define SERVER_CNCT_WAIT    1000
#define SERVER_CNCT_RETRY   3
#define SERVER_MSG_TIMEOUT  10000
#define SERVER_RESP_LEN     8

#define MSG_RETRY           2
#define MSG_OK              "OK"
#define MSG_OK_LEN          2

WiFiClient tcp_client;

typedef struct {
  char dev_type[DEV_NAME_LEN];
  char dev_name[DEV_NAME_LEN];
  char ip[DEV_IP_LEN];
} attached_devices_t;

attached_devices_t devices[DEV_MAXX] = { {"speaker", "living", "192.168.1.104"},
                                         {"laptop",  "living", "192.168.1.105"}
                                       };

uint8_t find_attached_device(char *dev_type, char *dev_name) {
  uint8_t dev = DEV_FIRST;
  for( ; dev < DEV_MAXX; dev++) {
    if((strcmp(devices[dev].dev_type, dev_type) == 0) && (strcmp(devices[dev].dev_name, dev_name) == 0))
      break;
  }

  return dev;
}

void send_msg(char *msg) {
  tcp_client.println(msg);
  tcp_client.flush();
}

bool forward_cmd_to_device(uint8_t dev, char *cmd) {
  bool    ret = false;
  uint8_t retry_cnt = 0;

  tcp_client.setNoDelay(1);

  for( ; retry_cnt < SERVER_CNCT_RETRY; retry_cnt++) {
    if (!tcp_client.connect(devices[dev].ip, SERVER_PORT)) {
        rgb_blink(LED_RED, 200, 1);
        T_PRINTLN("connection failed");
        delay(SERVER_CNCT_WAIT);
    } else {
      break;
    }
  }

  if(retry_cnt != SERVER_CNCT_RETRY) {
    char resp[SERVER_RESP_LEN] = {"\0"};
    
    send_msg(cmd);

    uint64_t  start_time = millis();
    while(tcp_client.available() == 0) {
      if((millis() - start_time) > SERVER_MSG_TIMEOUT) {
        break;
      }
    }

    if (tcp_client.available() > 0) {
      tcp_client.read((uint8_t *)resp, SERVER_RESP_LEN);
      T_PRINTLN(resp);

      if(!strncmp(resp, MSG_OK, MSG_OK_LEN)) {
        ret = true;
      }
    }
  }

  tcp_client.stop();

  return ret;
}

bool handle_attached_devices(char *cmd, char *dev_type, char *dev_name) {
  bool ret = false;
  uint8_t dev = find_attached_device(dev_type, dev_name);

  if(dev != DEV_MAXX) {
    for(int i = 0; i < MSG_RETRY; i++) {
      if((ret = forward_cmd_to_device(dev, cmd)) == true)
        break;
    }
  }

  return ret;
}

#define CMD_STR_LEN             64
#define ENTRTNMNT_UNIT_DEVICES  2

typedef struct {
  uint8_t dev;
  char cmd[CMD_STR_LEN];
} dev_grp_t;

dev_grp_t entrtnmnt_devs_on[ENTRTNMNT_UNIT_DEVICES]   = { {DEV_SPEAKER, "0 speaker living"},
                                                          {DEV_LAPTOP, "0 laptop living"}
                                                        };

dev_grp_t entrtnmnt_devs_off[ENTRTNMNT_UNIT_DEVICES]  = { {DEV_SPEAKER, "1 speaker living"},
                                                          {DEV_LAPTOP, "1 laptop living"}
                                                        };

bool entrtnmnt_unit_on(void) {
  bool ret = true;

  turn_on_tv();

  for(int i = 0; i < ENTRTNMNT_UNIT_DEVICES; i++) {
    bool result;
    for(int j = 0; j < MSG_RETRY; j++) {
      if((result = forward_cmd_to_device(entrtnmnt_devs_on[i].dev, entrtnmnt_devs_on[i].cmd)) == true) {
        rgb_cycle(1, 50);
        break;
      }
    }

    if(!result)
      ret = result;
  }

  return ret;
}

bool entrtnmnt_unit_off(void) {
  bool ret = true;

  turn_off_tv();

  for(int i = 0; i < ENTRTNMNT_UNIT_DEVICES; i++) {
    bool result;
    for(int j = 0; j < MSG_RETRY; j++) {
      if((result = forward_cmd_to_device(entrtnmnt_devs_off[i].dev, entrtnmnt_devs_off[i].cmd)) == true) {
        rgb_cycle(1, 50);
        break;
      }
    }

    if(!result)
      ret = result;
  }

  return ret;
}


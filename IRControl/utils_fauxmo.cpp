#include "utils_fauxmo.h"

#ifdef FAUXMO_IN_USE

#include <Arduino.h>
#include <fauxmoESP.h>
#include "utils_ir.h"
#include "utils_debug.h"

#define INVALID_DEV 0xFF

fauxmoESP fauxmo;
volatile unsigned char device_id = INVALID_DEV;

void handle_devices(void)
{
  if(device_id != INVALID_DEV)
  {
    switch (device_id)
    {
    	case ID_TELEVISION :
    	case ID_TV :
    		turn_on_off_tv();
    		break;

    	case ID_SPEAKER :
    		turn_on_off_speaker();
    		break;

    	case ID_LAPTOP :
    		turn_on_off_laptop();
			break;

    	case ID_ENTERTNMNT_UNIT :
    		turn_on_off_entertainment_unit();
    		break;

    	default :
    		PRINTLN("Unknown device !!!");
    		break;
    }

    device_id = INVALID_DEV;
  }
}

void callback(unsigned char id, const char * device_name, bool state)
{
  Serial.printf("[MAIN] Device #%d (%s) state: %s\n", id, device_name, state ? "ON" : "OFF");
  device_id = id;
}

void setup_fauxmo(void)
{
  fauxmo.addDevice("television");
  fauxmo.addDevice("tv");
  fauxmo.addDevice("speaker");
  fauxmo.addDevice("laptop");
  fauxmo.addDevice("entertainment unit");

  fauxmo.onMessage(callback);
}

void handle_fauxmo(void)
{
  fauxmo.handle();
  handle_devices();
}

#endif

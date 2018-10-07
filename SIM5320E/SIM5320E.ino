#include <ESP8266WiFi.h>
#include "SoftwareSerial.h"

#define RX_PIN  D1
#define TX_PIN  D2

SoftwareSerial sim5320e(RX_PIN, TX_PIN, false, 256);

void setup() {
  delay(5000);

  Serial.begin(9600);
  sim5320e.begin(9600);
        
  Serial.println("\nBegin!!!\n");
}

void loop() {
  while(sim5320e.available()) {
    Serial.write(sim5320e.read());    
  }

  while(Serial.available()) {
    //Serial.write(Serial.read());
    sim5320e.write(Serial.read());  
  }
}


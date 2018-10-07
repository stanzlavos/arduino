/*
    BLE!!!
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define CHARACTERISTIC_DESC     BLEUUID((uint16_t)0x2901)     // User description
#define CHARACTERISTIC_CONFIG   BLEUUID((uint16_t)0x2902)     // Enable/Disable notifications/indications

#define MY_SERVICE_UUID         BLEUUID((uint16_t)0x18FF)     // New service UUID
#define MY_CHARACTERISTIC_UUID  BLEUUID((uint16_t)0x2AE0)     // New characteristics UUID

bool _BLEClientConnected = false;
BLEDescriptor characteristicDescriptor(CHARACTERISTIC_DESC);

static inline void blink_led(uint8_t cnt) {
  for (int i = 0; i < cnt; i++) {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }
}

static inline void fast_blink_led(uint8_t cnt) {
  for (int i = 0; i < cnt; i++) {
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
  }
}

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("onConnect...");
      _BLEClientConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      Serial.println("onDisconnect...");
      _BLEClientConnected = false;
    }
};

class MyCharacteristicCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      Serial.println("onWrite...");
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

bool is_ble_client_connected(void) {
  return _BLEClientConnected;
}

void init_ble(void) {
  Serial.println("Starting BLE work...");

  BLEDevice::init("MyNavigator");
  
  BLEServer   *pServer  = BLEDevice::createServer();
  BLEService  *pService = pServer->createService(MY_SERVICE_UUID);

  pServer->setCallbacks(new MyServerCallbacks());

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                            MY_CHARACTERISTIC_UUID,
                                            BLECharacteristic::PROPERTY_READ |
                                            BLECharacteristic::PROPERTY_WRITE);

  pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

  characteristicDescriptor.setValue("Send Command");
  pCharacteristic->addDescriptor(&characteristicDescriptor);

  pServer->getAdvertising()->addServiceUUID(MY_SERVICE_UUID);

  pService->start();

  pServer->getAdvertising()->start();

  Serial.println("BLE ready...");
}

void setup() {
  Serial.flush();
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  blink_led(5);

  init_ble();

  fast_blink_led(5);
}

void loop() {
}


/* NodeMCU */
#include <ESP8266WiFi.h>

/* Servo */
#define servo1Pin D1

#include <Servo.h>

Servo servo1;

int servo1Angle = 0;

void setup()
{
  Serial.begin(115200);
  delay(10);
  servo1.attach(servo1Pin);
}

void loop()
{                    
  servo1.write(servo1Angle);                      // Move the servo to a position
  
  Serial.println(servo1Angle);
  
  delay(2000);                                    // Delay to prevent errors

  if(servo1Angle)
    servo1Angle = 0;
  else
    servo1Angle = 180;  
}

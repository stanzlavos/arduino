// now.pde
// Prints a snapshot of the current date and time along with the UNIX time
// Modified by Andy Wickert from the JeeLabs / Ladyada RTC library examples
// 5/15/11

#include <Wire.h>
#include "DS3231.h"

RTClib RTC;
DS3231 Clock;

void setup () {
    Serial.begin(115200);
    Wire.begin();
}

void loop () {
  
    delay(1000);
  
    DateTime now = RTC.now();

    /*
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    */

    Serial.print("Temperature : ");
    Serial.println(Clock.getTemperature());   
    Serial.println("-------------------");
}


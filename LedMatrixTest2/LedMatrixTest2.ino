#include "LedControl.h"

LedControl lc=LedControl(D1,D2,D3,4);  // Pins: DIN,CLK,CS, # of Display connected

unsigned long delayTime=200;  // Delay between Frames
int devices = 0;

// Put values in arrays
byte invader1a[] =
{
   B00011000,  // First frame of invader #1
   B00111100,
   B01111110,
   B11011011,
   B11111111,
   B00100100,
   B01011010,
   B10100101
};

byte invader1b[] =
{
  B00011000, // Second frame of invader #1
  B00111100,
  B01111110,
  B11011011,
  B11111111,
  B00100100,
  B01011010,
  B01000010
};

byte invader2a[] =
{
  B00100100, // First frame of invader #2
  B00100100,
  B01111110,
  B11011011,
  B11111111,
  B11111111,
  B10100101,
  B00100100
};

byte invader2b[] =
{
  B00100100, // Second frame of invader #2
  B10100101,
  B11111111,
  B11011011,
  B11111111,
  B01111110,
  B00100100,
  B01000010
};

void setup()
{
  Serial.begin(115200);
  
  devices=lc.getDeviceCount();

  for(int address=0;address<devices;address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    lc.shutdown(address,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(address,4);
    /* and clear the display */
    lc.clearDisplay(address);
  }

  delay(5000);

  Serial.println("Ready !!!");
  Serial.println(devices);
}


//  Take values in Arrays and Display them
void sinvader1a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,invader1a[i]);
  }
}

void sinvader1b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,invader1b[i]);
  }
}

void sinvader2a()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(1,i,invader2a[i]);
  }
}

void sinvader2b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(1,i,invader2b[i]);
  }
}

void sinvader3a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,invader1a[i]);
  }
}

void sinvader3b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(2,i,invader1b[i]);
  }
}

void sinvader4a()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(3,i,invader2a[i]);
  }
}

void sinvader4b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(3,i,invader2b[i]);
  }
}

void loop()
{
// Put #1 frame on all Displays
    sinvader1a();
    delay(delayTime);
    sinvader2a();
    delay(delayTime);
    sinvader3a();
    delay(delayTime);
    sinvader4a();
    delay(delayTime);


// Put #2 frame on all Displays
    sinvader1b();
    delay(delayTime);
    sinvader2b();
    delay(delayTime);
    sinvader3b();
    delay(delayTime);
    sinvader4b();
    delay(delayTime);
}

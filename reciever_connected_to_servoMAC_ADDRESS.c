// the address of the esp32 connected to servo
#include "WiFi.h"
void setup() { 
 
 Serial.begin(115200);
 WiFi.mode(WIFI_MODE_STA);     Serial.println(WiFi.macAddress());
 
}

void loop()
{
 
}

// use this address for the address which is asked in other programs


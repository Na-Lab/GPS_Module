#include <Arduino.h>
#include "GPS_Module.h"

GPS gps(9600);

void setup() {
  Serial.begin(9600);
}

void loop() {
  gps.update();

  Serial.print("Latitude = ");
  Serial.print(gps.getLatitude());
  Serial.print(", Longitude = ");
  Serial.println(gps.getLongitude());
}

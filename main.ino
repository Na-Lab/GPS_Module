#include "GPS_Module.h"
#define SERIAL_BAUDRATE 9600  // シリアルモニタビューレート

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  gps_init();
}

void loop() {
  position_t pos = {0};
  get_position(&pos);

  Serial.print("Latitude = ");
  Serial.print(pos.latitude);
  Serial.print(", Longitude = ");
  Serial.println(pos.longitude);
}

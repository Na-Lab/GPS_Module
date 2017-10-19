#include <SoftwareSerial.h>

#define PIN_GPS_RX 10
#define PIN_GPS_TX 11

#define SERIAL_BAUDRATE 9600
#define GPS_BAUDRATE 9600

#define BUFFER_SIZE 256

SoftwareSerial gps(PIN_GPS_RX, PIN_GPS_TX);

void setup(){
    Serial.begin(SERIAL_BAUDRATE);
    gps.begin(GPS_BAUDRATE);
}

void loop(){
    if (gps.available()) {
        Serial.write(gps.read());
    }
}

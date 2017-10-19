#include <SoftwareSerial.h>

#define PIN_GPS_RX 10
#define PIN_GPS_TX 11

#define SERIAL_BAUDRATE 9600
#define GPS_BAUDRATE 9600

#define BUFFER_SIZE 256

SoftwareSerial gps(PIN_GPS_RX, PIN_GPS_TX);

// NMEAフォーマット読み取り関数
void rcv_nmea(char *buf){
    char c;
    int count = 0;

    do {
        if (gps.available()) {
            buf[count] = gps.read();
            count++;
        }
        if (count > BUFFER_SIZE - 2) break; // バッファ溢れを監視する
    } while (buf[count - 1] != 0x0a);
    buf[count] = '\0';
}

void setup(){
    Serial.begin(SERIAL_BAUDRATE);
    gps.begin(GPS_BAUDRATE);
}

void loop(){
    char buf[BUFFER_SIZE];

    rcv_nmea(buf);

    if (!strncmp("$GPGGA", buf, 6)) {
        Serial.print(buf);
    }
}

#include <SoftwareSerial.h>

#define PIN_GPS_RX 10
#define PIN_GPS_TX 11

#define SERIAL_BAUDRATE 9600
#define GPS_BAUDRATE 9600

#define BUFFER_SIZE 256

#define DELIMITER (",")

SoftwareSerial gps(PIN_GPS_RX, PIN_GPS_TX);

typedef struct position
{
    double latitude;  // 緯度
    double longitude; // 軽度
} position_t;

// NMEAフォーマット読み取り関数
void rcv_nmea(char *buf)
{
    char c;
    int count = 0;

    do
    {
        if (gps.available())
        {
            buf[count] = gps.read();
            count++;
        }
        if (count > BUFFER_SIZE - 2)
            break; // バッファ溢れを監視する
    } while (buf[count - 1] != 0x0a);
    buf[count] = '\0';
}

// DEG表記変換関数
double dmm_2_deg(char *data)
{
    double temp, deg, min;

    temp = atof(data);
    deg = (int)(temp / 100);
    min = temp - deg * 100;
    return (double)(deg + min / 60.0);
}

// 位置情報取得関数
void get_position(position_t *pos)
{
    char buf[BUFFER_SIZE];
    char *lat_p, *long_p;

    // NMEAの取得
    do
    {
        rcv_nmea(buf);
    } while (strncmp("$GPGGA", buf, 6));

    // 位置情報の抽出
    strtok(buf, DELIMITER);           // $GPGGA
    lat_p = strtok(NULL, DELIMITER);  // 緯度
    strtok(NULL, DELIMITER);          // 南北
    long_p = strtok(NULL, DELIMITER); // 経度

    // データの加工
    pos->latitude = dmm_2_deg(lat_p);
    pos->longitude = dmm_2_deg(long_p);
}

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);
    gps.begin(GPS_BAUDRATE);
}

void loop()
{
    position_t pos = {0};

    get_position(&pos);

    Serial.print("Latitude = ");
    Serial.print(pos.latitude);
    Serial.print(", Longitude = ");
    Serial.println(pos.longitude);
}

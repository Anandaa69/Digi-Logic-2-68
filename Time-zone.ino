#include <WiFi.h>
#include <time.h>

WiFiClient client;
const int LED = 32;
const char* ssid = "xxxxxxxxxxxx";
const char* password = "xxxxxxxx";

// กำหนดเวลาในรูปแบบ UTC (เช่น UTC+9 = 9 * 3600)
const long utcOffsetInSeconds = 7 * 3600; // UTC+9 สำหรับ Japan

// กำหนด NTP server
const char* ntpServer = "pool.ntp.org";

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  
  // เชื่อมต่อ WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not CONNECTED");
    delay(1000);
  }
  digitalWrite(LED, LOW);

  // เริ่มการใช้งานเวลา NTP
  configTime(utcOffsetInSeconds, 0, ntpServer);  // ตั้งค่า NTP server และ UTC+9 สำหรับ Japan
}

void loop() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {  // รับเวลาจาก NTP server
    Serial.println("Failed to obtain time");
    return;
  }

  // แสดงเวลาปัจจุบัน
  Serial.print("Current time: ");
  Serial.print(timeinfo.tm_hour);
  Serial.print(":");
  Serial.print(timeinfo.tm_min);
  Serial.print(":");
  Serial.println(timeinfo.tm_sec);

  // แสดงวันเดือนปี
  Serial.print("Date: ");
  Serial.print(timeinfo.tm_mday);
  Serial.print("/");
  Serial.print(timeinfo.tm_mon + 1);  // เดือนจะเริ่มจาก 0 (มกราคม = 0)
  Serial.print("/");
  Serial.println(timeinfo.tm_year + 1900);  // ปีจะเริ่มจาก 1900

  delay(1000); // รอ 1 วินาที
}

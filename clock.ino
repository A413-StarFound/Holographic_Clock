/*
    The code depends on the oled , according to the IIC.
    THE adafruit_GFX and adafruit_SSD1306 is the head file to drive the oled screen
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// OLED 显示屏的 I2C 地址（通常为 0x3C 或 0x3D）
#define OLED_ADDRESS 0x3C
// OLED 显示屏的宽度和高度（以像素为单位）
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "YOUR_SSID";  
const char* password = "YOUR_PASSWAED";  

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");

  // 初始化 OLED 显示屏
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  timeClient.setTimeOffset(28800);  // 设置北京时间偏移 8 小时

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}

void loop() {
  timeClient.update();

  int hour = timeClient.getHours();
  int minute = timeClient.getMinutes();
  int second = timeClient.getSeconds();

  display.clearDisplay();

  display.setCursor(0, 0);
  display.print(hour);
  display.print(":");
  if (minute < 10) {
    display.print("0");
  }
  display.print(minute);
  display.print(":");
  if (second < 10) {
    display.print("0");
  }
  display.print(second);

  display.display();

  delay(1000);
}

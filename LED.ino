#include <MD_MAX72xx.h>
#include <SPI.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// 定义 MAX7219 的相关参数
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 5

// 创建 MD_MAX72XX 对象
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// 数字 0 - 9 的点阵数据
const uint8_t digitSegments[10][8] = {
  {0x3E, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3E}, // 0
  {0x08, 0x18, 0x28, 0x08, 0x08, 0x08, 0x08, 0x3E}, // 1
  {0x3E, 0x01, 0x01, 0x3E, 0x20, 0x20, 0x20, 0x3E}, // 2
  {0x3E, 0x01, 0x01, 0x3E, 0x01, 0x01, 0x01, 0x3E}, // 3
  {0x41, 0x41, 0x41, 0x3E, 0x01, 0x01, 0x01, 0x01}, // 4
  {0x3E, 0x20, 0x20, 0x3E, 0x01, 0x01, 0x01, 0x3E}, // 5
  {0x3E, 0x20, 0x20, 0x3E, 0x41, 0x41, 0x41, 0x3E}, // 6
  {0x3E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}, // 7
  {0x3E, 0x41, 0x41, 0x3E, 0x41, 0x41, 0x41, 0x3E}, // 8
  {0x3E, 0x41, 0x41, 0x3E, 0x01, 0x01, 0x01, 0x3E}  // 9
};

// 替换为你的网络信息
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// NTP 客户端设置
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 28800); // 28800 偏移量为北京时间（UTC+8）

void setup() {
  Serial.begin(115200);
  // 初始化 MAX7219
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 0x08);
  Serial.println("Intensity set");
  mx.control(MD_MAX72XX::SCANLIMIT, 0x07);
  Serial.println("Scan limit set");
  mx.control(MD_MAX72XX::DECODE, 0x00);
  Serial.println("Decode mode set");
  mx.control(MD_MAX72XX::SHUTDOWN, 0x01);
  Serial.println("Shutdown mode disabled");

  // 连接 WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // 初始化 NTP 客户端
  timeClient.begin();
}

void loop() {
  // 更新时间
  timeClient.update();

  // 获取当前时间
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int hours = ptm->tm_hour;
  int minutes = ptm->tm_min;

  // 显示小时的十位
  int digit1 = hours / 10;
  displayDigit(0, digit1);
  // 显示小时的个位
  int digit2 = hours % 10;
  displayDigit(1, digit2);
  // 显示分钟的十位
  int digit3 = minutes / 10;
  displayDigit(2, digit3);
  // 显示分钟的个位
  int digit4 = minutes % 10;
  displayDigit(3, digit4);

  delay(1000); // 每秒更新一次显示
}

void displayDigit(int device, int digit) {
  for (int row = 0; row < 8; row++) {
    mx.setRow(device, row, digitSegments[digit][row]);
  }
}
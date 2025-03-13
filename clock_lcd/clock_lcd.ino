#include "MD_Parola.h"
#include "MD_MAX72xx.h"
#include "SPI.h"
#include <WiFi.h>
#include "time.h"

// 替换为你的网络信息
const char* ssid = "loong的电子节点";
const char* password = "shijinjia";

// NTP 服务器设置
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 28800; // 北京时间，东八区，偏移 8 * 3600 秒
const int   daylightOffset_sec = 0;

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// 每个点阵屏的片选引脚定义
#define CS_PIN_1 15
#define CS_PIN_2 2
#define CS_PIN_3 4
#define CS_PIN_4 5

#define MAX_DEVICES 1  // 每个点阵屏设备数量为 1

MD_Parola disp1 = MD_Parola(HARDWARE_TYPE, CS_PIN_1, MAX_DEVICES);
MD_Parola disp2 = MD_Parola(HARDWARE_TYPE, CS_PIN_2, MAX_DEVICES);
MD_Parola disp3 = MD_Parola(HARDWARE_TYPE, CS_PIN_3, MAX_DEVICES);
MD_Parola disp4 = MD_Parola(HARDWARE_TYPE, CS_PIN_4, MAX_DEVICES);

void setup() {
  Serial.begin(115200);

  // 初始化点阵屏
  disp1.begin();
  disp1.setIntensity(0);
  disp1.displayClear();

  disp2.begin();
  disp2.setIntensity(0);
  disp2.displayClear();

  disp3.begin();
  disp3.setIntensity(0);
  disp3.displayClear();

  disp4.begin();
  disp4.setIntensity(0);
  disp4.displayClear();

  // 连接 Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // 初始化 NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    delay(1000);
    return;
  }

  // 获取小时和分钟
  int hour = timeinfo.tm_hour;
  int minute = timeinfo.tm_min;

  // 提取小时和分钟的每一位数字
  int hourDigit1 = hour / 10;
  int hourDigit2 = hour % 10;
  int minuteDigit1 = minute / 10;
  int minuteDigit2 = minute % 10;

  // 将数字转换为字符串
  char hourDigit1Str[2];
  char hourDigit2Str[2];
  char minuteDigit1Str[2];
  char minuteDigit2Str[2];

  itoa(hourDigit1, hourDigit1Str, 10);
  itoa(hourDigit2, hourDigit2Str, 10);
  itoa(minuteDigit1, minuteDigit1Str, 10);
  itoa(minuteDigit2, minuteDigit2Str, 10);

  // 设置文本居中显示
  disp1.setTextAlignment(PA_CENTER);
  disp2.setTextAlignment(PA_CENTER);
  disp3.setTextAlignment(PA_CENTER);
  disp4.setTextAlignment(PA_CENTER);

  // 在四个点阵屏上显示数字
  disp1.print(hourDigit1Str);
  disp2.print(hourDigit2Str);
  disp3.print(minuteDigit1Str);
  disp4.print(minuteDigit2Str);

  delay(1000); // 每秒更新一次显示
}
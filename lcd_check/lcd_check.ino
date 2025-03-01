#include "MD_Parola.h"
#include "MD_MAX72xx.h"
#include "SPI.h"

SPIClass spi(VSPI); // 使用VSPI总线

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 1  // 一位8x8 LED点阵，所以设备数量为1
#define CS_PIN 4

MD_Parola disp = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  Serial.begin(115200); // 初始化串口通信
  disp.begin();
  disp.setIntensity(0);  // 设置显示亮度
  pinMode(CS_PIN, OUTPUT);
  disp.displayClear();   // 清空显示

  // 重置 MAX72xx 芯片
  digitalWrite(CS_PIN, LOW);
  spi.transfer(0x09); // 译码模式寄存器
  spi.transfer(0x00); // 不使用译码
  digitalWrite(CS_PIN, HIGH);

  digitalWrite(CS_PIN, LOW);
  spi.transfer(0x0A); // 亮度寄存器
  spi.transfer(0x0F); // 最大亮度
  digitalWrite(CS_PIN, HIGH);

  digitalWrite(CS_PIN, LOW);
  spi.transfer(0x0B); // 扫描限制寄存器
  spi.transfer(0x07); // 扫描所有 8 行
  digitalWrite(CS_PIN, HIGH);

  digitalWrite(CS_PIN, LOW);
  spi.transfer(0x0C); // 关机模式寄存器
  spi.transfer(0x01); // 正常工作模式
  digitalWrite(CS_PIN, HIGH);

  spi.begin(18, -1, 23, -1); // SCK=18, MISO=-1（不使用）, MOSI=23, SS=-1（不使用）
  Serial.println("SPI initialized"); // 打印调试信息
}
void loop() {
  for (int i = 0; i <= 9; i++) {
    disp.displayClear();  // 清除之前的显示内容
    disp.setTextAlignment(PA_CENTER);  // 设置文本居中显示
    // 将数字转换为字符串进行显示
    char numStr[2];
    itoa(i, numStr, 10);
    Serial.print("Sending data: ");
    Serial.println(numStr);

    // 手动控制 CS 引脚
    digitalWrite(CS_PIN, LOW);
    Serial.println("CS pin pulled low");
    disp.print(numStr);
    digitalWrite(CS_PIN, HIGH);
    Serial.println("CS pin pulled high");

    Serial.println("Data sent");
    delay(2000);  // 每个数字显示2秒
  }
}
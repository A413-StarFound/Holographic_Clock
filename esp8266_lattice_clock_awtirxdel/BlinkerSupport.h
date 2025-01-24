#ifndef BLINKER_SUPPORT_H
#define BLINKER_SUPPORT_H

#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT

#include "Main.h"
#include <Blinker.h>

char auth[] = ""; // 这里设置你自己的点灯秘钥

// 新建组件对象
BlinkerButton powerBtn("btn-power");         // 开关按键
BlinkerButton directBtn("btn-direction");    // 方向按键
BlinkerNumber temperNum("num-temperature");  // 温度回调
BlinkerSlider brightSlider("slider_bright"); //亮度滑动条
BlinkerSlider powerSlider("slider_power");   //功能滑动条

/**
 * @brief 设置方向回调
 *
 * @param state
 */
void directionCallback(const String &state)
{
    Serial.print("设置时钟方向:");
    Serial.println(state);
    uint8_t direction = 0;
    if (state == BLINKER_CMD_ON)
    {
        direction = 0;
        directBtn.print("on"); // 反馈开关状态
    }
    else if (state == BLINKER_CMD_OFF)
    {
        direction = 1;
        directBtn.print("off"); // 反馈开关状态
    }
    lattice.setDirection(direction); // 是否启用点阵屏幕
}

/**
 * @brief 设置亮度的回调
 *
 * @param value
 */
void brightCallback(int32_t value)
{
    lattice.setBrightness(value, true); // 设置亮度
    brightSlider.print(value);          // 将数据回调给组件
}

/**
 * @brief 功能切换的回调
 *
 * @param value
 */
void powerCallback(int32_t value)
{
    functions.setPowerAndMode(value, 0); // 切换功能
    initStatus();                        // 重置状态
    powerSlider.print(value);            // 将数据回调给组件
}


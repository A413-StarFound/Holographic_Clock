#ifndef HTTP_TOOL_H
#define HTTP_TOOL_H

#include "EEPROMTool.h"
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecureBearSSL.h>


const uint8_t fingerprint[20] = {0x40, 0xaf, 0x00, 0x6b, 0xec, 0x90, 0x22, 0x41, 0x8e, 0xa3, 0xad, 0xfa, 0x1a, 0xe8, 0x25, 0x41, 0x1d, 0x1a, 0x54, 0xb3};

class HttpTool
{
private:
  /**
   * http客户端
   */
  HTTPClient espClient;
  /**
   * WiFiMulti
   *
   */
  ESP8266WiFiMulti WiFiMulti;

  
public:
  HttpTool();

  
};

#endif

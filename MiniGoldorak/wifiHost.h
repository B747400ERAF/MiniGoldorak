#ifndef wifiHost_h
#define wifiHost_h

//Libraries
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

void handleRoot();
void initWifiHost();
void startServer();
int GetSensorValue();
void ArgsPage();



#endif

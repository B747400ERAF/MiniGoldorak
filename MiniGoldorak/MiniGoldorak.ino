#include "wifiHost.h"
#include "actionneurs.h"

void setup() {
  initActionneurs();
  handleRoot();
  initWifiHost();
}


void loop() {
  startServer();
  ArgsPage();
  Serial.print("Serveur started ");
  if (GetSensorValue() == true ) {
    algoActionneurs();
  }
}

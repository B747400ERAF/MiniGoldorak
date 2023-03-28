#include "wifiHost.h"
#include "actionneurs.h"

void setup() {
  initActionneurs();
  handleRoot();
  //handlePost();
  initWifiHost();
  ArgsPage();
}


void loop() {
  startServer();
  if (GetSensorValue() == true ) {
    algoActionneurs();
  }
}

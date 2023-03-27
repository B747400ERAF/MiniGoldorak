#include "wifiHost.h"
//#include "actionneurs.h"

void setup() {
  //initActionneurs();
  handleRoot();
  //handlePost();
  initWifiHost();
}


void loop() {
  startServer();
  //algoActionneurs();  
}

#include "wifiHost.h"
#include "actionneurs.h"

void setup() {
  initActionneurs();
  handleRoot();
  //handlePost();
  initWifiHost();
  //initServer();
  //algoActionneurs();
}


void loop() {
 // if(initServer()) 
 //   algoActionneurs();     
 // }
}

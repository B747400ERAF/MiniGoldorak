//#include "wifiHost.h"
#include "actionneurs.h"

void setup() {
  initActionneurs();
  //handleRoot();
  //handlePost();
  //initWifiHost();
}


void loop() {
  algoActionneurs();  
  //startServer();
}

  
 // if(initServer()) 
 //   algoActionneurs();     
 // }

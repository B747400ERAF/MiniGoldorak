/*#include "wifiHost.h"

const char* ssid = "Mini-Goldorak";   // Nom du réseau WiFi
const char* password = "Club_Dorothee01@";  // Mot de passe du réseau WiFi

bool detectionValue = false;

ESP8266WebServer server(80);

//Adresse IP: 192.168.4.1


void handleRoot() {
  String html = "index";
  String css = "style";
  String js = "script";
  
  File file = SPIFFS.open("/index.html", "r");
  if (file) {
    while (file.available()) {
      html += (char) file.read();
    }
    file.close();
  }
  
  file = SPIFFS.open("/style.css", "r");
  if (file) {
    while (file.available()) {
      css += (char) file.read();
    }
    file.close();
  }
  
  file = SPIFFS.open("/script.js", "r");
  if (file) {
    while (file.available()) {
      js += (char) file.read();
    }
    file.close();
  }
  
  
  html.replace("%CSS%", css);
  html.replace("%JS%", js);
  server.send(200, "text/html", html);
}

/*
void handlePost() {
  if (server.hasArg("action")) {
    String action = server.arg("action");
    if (action == "Activer") {
      sensorEnabled = true;
      sensor.init();
    } else if (action == "Désactiver") {
      sensorEnabled = false;
    }
  }
  handleRoot();
}

void initWifiHost() {
  Serial.begin(115200);
  SPIFFS.begin();
  
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Adresse IP du point d'accès: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  //server.on("/", handlePost);
  //server.on("/args", ArgsPage);
  server.begin();
}

void startServer() {
  server.handleClient();
}*/

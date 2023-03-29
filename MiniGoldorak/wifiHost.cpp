#include "wifiHost.h"

const char* ssid = "Mini-Goldorak";   // Nom du réseau WiFi
const char* password = "Club_Dorothee01@";  // Mot de passe du réseau WiFi

bool sensorValue;
int GetSensorValue() {
  return sensorValue;
}

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

void ArgsPage() { 
  if(server.arg("sensor") != "on"){
    sensorValue = server.arg("sensor").toInt(); 
    Serial.print("Valeur de la detection: "); Serial.println(sensorValue); 
    sensorValue = true;
  } else {
    sensorValue = false;
  }
  server.send(200, "text/plain", "ok"); 
}

void initWifiHost() {
  Serial.begin(115200);
  SPIFFS.begin();
  
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Adresse IP du point d'accès: ");
  Serial.println(myIP);
  server.serveStatic("/", SPIFFS, "/index.html"); 
  server.on("/args", ArgsPage);
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
}

void startServer() {
  server.handleClient();
}

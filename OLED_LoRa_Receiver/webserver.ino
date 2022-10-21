#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "nome wifi";
const char* password = "senha wifi";

WebServer server(80);

void handleRoot() {

  server.send(200, "text/plain", packet);

}

void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
 
}

String IP = "10.240.12.99";
IPAddress local_IP(10,240,12,99); // ip fixo do de rede
IPAddress gateway(10,240,12,30);
IPAddress subnet(255,255,0,0);
IPAddress primaryDNS(8,8,8,8);
IPAddress secondaryDNS(8,8,4,4);

void setup(void) {
  setupReceiverLora();
  
    if(!WiFi.config(local_IP,gateway,subnet,primaryDNS,secondaryDNS)){
    Serial.println("Failed Configure WiFi" );
  }
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  int contSetupWifi = 0;
  while (WiFi.status() != WL_CONNECTED) {
    msgDisplay("Connecting WiFi...");
    if(contSetupWifi == 50){
      ESP.restart();
      }
    delay(500);
    Serial.print(".");
    contSetupWifi++;
  }
  msgDisplay(IP);
  delay(2000);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");

  
  Serial.println(WiFi.localIP());
  
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}
int cont = 0;
void loop(void) {
  if(WiFi.status() != WL_CONNECTED){
    msgDisplay("Connecting WiFi...");
    if(cont == 500){
      ESP.restart();
      }
    cont++;
    }
   else{
    int packetSize = LoRa.parsePacket();
     if (packetSize) { 
      cbk(packetSize);  
      Serial.println(packet);
    }
    server.handleClient();
   // delay(.1);//allow the cpu to switch to other tasks
    
    }
   
 delay(1);
}

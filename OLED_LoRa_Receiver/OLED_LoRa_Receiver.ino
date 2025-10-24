#include "heltec.h" 


#define BAND    915E6
String rssi = "RSSI --";
String packSize = "--";
String packet ;

void logo(){
  Heltec.display->clear();

  Heltec.display->display();
}

void LoRaData(){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);

  Heltec.display->drawStringMaxWidth(0 , 26 , 128, packet);
  Heltec.display->drawString(0, 0, rssi);  
  Heltec.display->display();
}

void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) { packet += (char) LoRa.read(); }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC) ;
  LoRaData();
}

void msgDisplay(String frase){
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0, 0, frase);
  Heltec.display->display();
  }

void setupReceiverLora() { 
  
  Heltec.begin(true, true, true, true, BAND);
 
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_24);
  //logo();
  delay(1500);

  Heltec.display->clear();
  
  Heltec.display->drawString(25, 0, "Ambev");
  Heltec.display->setFont(ArialMT_Plain_16);
  
  
  
  Heltec.display->drawString(25, 43, "Cerberu X");
  Heltec.display->display();
  delay(1500);
  Heltec.display->clear();
  LoRa.receive();
}

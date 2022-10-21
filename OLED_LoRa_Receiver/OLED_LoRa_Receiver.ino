#include "heltec.h" 
//#include "images.h"

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6
String rssi = "RSSI --";
String packSize = "--";
String packet ;

void logo(){
  Heltec.display->clear();
 // Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
}

void LoRaData(){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  //Heltec.display->drawString(0 , 15 , "Received "+ packSize + " bytes");
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
   //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
 
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
//  Heltec.display->drawString(0, 0, "Connected: "+ String(IP));
//  delay(1000);
  //LoRa.onReceive(cbk);
  LoRa.receive();
}

//void LoraReceiver() {
//  int packetSize = LoRa.parsePacket();
//  if (packetSize) { 
//    cbk(packetSize);  
//    Serial.println(packet);
//  }
//  delay(10);
//}

#include "heltec.h"

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6

unsigned int counter = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;


void setup()
{
  
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
}

String lcd_lora = "";

void loop()
{
  lcd_lora = "Enviando: ";
  lcd_lora += String(Temperatura());
  lcd_lora += " °C";
  
  
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  
  Heltec.display->drawString(0, 0, lcd_lora);

  Heltec.display->display();

  // send packet
  LoRa.beginPacket();
  
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print("Celsius: ");
  LoRa.print(Temperatura());
  LoRa.print(" °C");
  LoRa.endPacket();

  lcd_lora = "";
}

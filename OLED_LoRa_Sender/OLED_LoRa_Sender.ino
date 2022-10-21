#include "heltec.h"
//#include "images.h"

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6

unsigned int counter = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;

//void logo()
//{
//  Heltec.display->clear();
//  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
//  Heltec.display->display();
//}

void setup()
{
  
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
  
/*
 * LoRa.setTxPower(txPower,RFOUT_pin);
 * txPower -- 0 ~ 20
 * RFOUT_pin could be RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
 *   - RF_PACONFIG_PASELECT_PABOOST -- LoRa single output via PABOOST, maximum output 20dBm
 *   - RF_PACONFIG_PASELECT_RFO     -- LoRa single output via RFO_HF / RFO_LF, maximum output 14dBm
*/
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print("Celsius: ");
  LoRa.print(Temperatura());
  LoRa.print(" °C");
  LoRa.endPacket();

  lcd_lora = "";

 
//  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                       // wait for a second
}

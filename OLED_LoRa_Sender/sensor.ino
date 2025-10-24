#include <OneWire.h>  
#include <DallasTemperature.h>


#define dados 22 /*o pino de dados do sensor está ligado na porta 2 do Arduino*/

OneWire oneWire(dados); 

DallasTemperature sensors(&oneWire); 

void setupSensor() 
{ 
 sensors.begin();
} 
String Temperatura()
{ 

 sensors.requestTemperatures();
 String temp = String(sensors.getTempCByIndex(0));
 return temp;
}

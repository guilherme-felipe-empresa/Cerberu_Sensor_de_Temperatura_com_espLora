/*inclusão das bibliotecas necessárias*/
#include <OneWire.h>  
#include <DallasTemperature.h>
/********************************************************************/

#define dados 22 /*o pino de dados do sensor está ligado na porta 2 do Arduino*/

OneWire oneWire(dados);  /*Protocolo OneWire*/
/********************************************************************/
DallasTemperature sensors(&oneWire); /*encaminha referências OneWire para o sensor*/
/********************************************************************/ 
void setupSensor() /*laço de configuração*/
{ 
 
 sensors.begin(); /*inicia biblioteca*/
} 
String Temperatura() /*laço de repetição*/
{ 

 sensors.requestTemperatures(); /* Envia o comando para leitura da temperatura */

  String temp = String(sensors.getTempCByIndex(0));
  return temp; /* Endereço do sensor */
}

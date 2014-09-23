/*
Autor: Weuller Marcos
Lendo latitude e Longitude
Usando Tx =0 e Rx = 1
FUNCIONANDO PARA O MEGA 2560
*/
 
#include <SD.h>
#include <nmea.h>

NMEA gps(GPRMC);

void setup()
{
  Serial.begin(38400);
  Serial.println("start");
}
 
void loop()
{
  
  if (Serial.available() > 0 ) {
    
    //  Lê caracteres vindos do GPS
    char leitura = Serial.read();
    Serial.println(leitura);
    //  Verifica se o valor recebido e uma sentença GPS valida
    if (gps.decode(leitura)) {
       Serial.println("Decodificou");
      
      
      if (gps.gprmc_status() == 'A') { //  Verifica se o posicionamento GPS esta ativo
        Serial.print("Latitude: ");
        Serial.println(gps.gprmc_latitude(), DEC); //Recupera Latitude
        
        Serial.print("Longitude: ");
        Serial.println(gps.gprmc_longitude(), DEC);//Recupera Longitude
      }
    }
  }
}

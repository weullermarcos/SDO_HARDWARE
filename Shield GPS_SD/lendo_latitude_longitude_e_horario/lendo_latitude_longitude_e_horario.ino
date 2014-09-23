/*
Autor: Weuller Marcos
Lendo latitude e Longitude
Usando Tx =0 e Rx = 1
FUNCIONANDO PARA O MEGA 2560
*/
 
#include <SD.h>
#include <nmea.h>

NMEA gps(ALL);

float latitude;
float longitude;
float hora;
float velocidade;

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
        
        latitude = gps.gprmc_latitude();
        longitude = gps.gprmc_longitude();
        hora = gps.gprmc_utc();
        velocidade = gps.gprmc_speed(KMPH);
        
        Serial.print("Latitude: ");
        Serial.println(latitude, DEC); //Recupera Latitude
        
        Serial.print("Longitude: ");
        Serial.println(longitude, DEC);//Recupera Longitude
        
        Serial.print("Hora: ");
        Serial.println(hora);//Recupera hora
        
        Serial.print("Velocidade: ");
        Serial.println(velocidade );//Recupera velocidade
        
      }
    }
  }
}

/*
Autor: Weuller Marcos
Lendo latitude e Longitude
FUNCIONANDO PARA O MEGA 2560
*/
 
#include <nmea.h>

NMEA gps(ALL);

float latitude;
float longitude;
float hora;
float velocidade;
String data;

void setup()
{
  Serial.begin(38400); 
  Serial2.begin(38400);
  Serial.println("start");
}

boolean isGPRMC = false;
byte commaNumber = 0;
byte countGPRMC = 0;
byte formatDate = 0;

void getDate(char leitura)
{
  //$GPRMC,225446.000,A,4916.45,N,12311.12,W,000.5,054.7,191194,020.3,E*68
  
  if(leitura == '$')
    {
      countGPRMC ++;
    }
    else if (leitura == 'G')
    {
      countGPRMC ++;
    }
    else if (leitura == 'P')
    {
      countGPRMC ++;
    }
    else if (leitura == 'R')
    {
      countGPRMC ++;
    }
    else if (leitura == 'M')
    {
      countGPRMC ++;
    }
    else if (leitura == 'C')
    {
      countGPRMC ++;
    }
    else
    {
      countGPRMC = 0;
    }
    
    if(countGPRMC == 6) //encontrou o cabeçalho $GPRMC
    {
       data = "";
       isGPRMC = true;
       commaNumber = 0;
    }
    
    if(leitura == ',' && isGPRMC) //contando o numero de virgulas para achar a data apos a nona virgula
    {
      commaNumber++;
    }
      
    if(commaNumber == 9) // a data se encontra após a nona virgula
    {
      if(leitura != ',') //para não pegar a virgula que antecede a data
      {  
        if(formatDate == 2)
          data += "/";
        if(formatDate == 4)
          data += "/";
          
        data += leitura;
        formatDate ++;
      }
    }
    
    if(commaNumber == 10) //para de coletar data quando achar a próxima virgula
    {
      commaNumber = 0;
      isGPRMC = false;
      countGPRMC = 0;
      formatDate = 0;
    }
}

void loop()
{
  if (Serial2.available() > 0 ) {
    
    //  Lê caracteres vindos do GPS
    char leitura = Serial2.read();
    
    getDate(leitura);
    
    //  Verifica se o valor recebido e uma sentença GPS valida
    if (gps.decode(leitura)) {
       Serial.println("Decodificou");
      
      
      if (gps.gprmc_status() == 'A') { //  Verifica se o posicionamento GPS esta ativo
        
        latitude = gps.gprmc_latitude();
        longitude = gps.gprmc_longitude();
        hora = gps.gprmc_utc(); //hora no formato flutuante
        velocidade = gps.gprmc_speed(KMPH);
        
        char novahora[6];
        dtostrf(hora, 6, 0, novahora);
        String horaFormatada;
        horaFormatada+= String(novahora[0]) + String(novahora[1]) + ":" + String(novahora[2]) + String(novahora[3]) + ":" + String(novahora[4]) + String(novahora[5]);
                
        Serial.print("Latitude: ");
        Serial.println(latitude, DEC); //Recupera Latitude
        
        Serial.print("Longitude: ");
        Serial.println(longitude, DEC);//Recupera Longitude
        
        Serial.print("Data: ");
        Serial.println(data);//Recupera data
        
        Serial.print("Hora: ");
        Serial.println(horaFormatada);//Recupera hora
        
        Serial.print("Data Hora: ");
        Serial.println(data+" "+horaFormatada);//Recupera hora
        
        Serial.print("Velocidade: ");
        Serial.println(velocidade );//Recupera velocidade
      }
    }
  }
}



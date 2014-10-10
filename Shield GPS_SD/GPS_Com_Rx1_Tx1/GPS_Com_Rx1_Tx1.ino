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
String horaFormatada;

void setup()
{
  Serial.begin(38400); 
  Serial1.begin(38400);
  Serial.println("start");
}

boolean isGPRMC = false;
boolean isDot = false;
byte commaNumber = 0;
byte countGPRMC = 0;
byte formatDate = 0;
byte formatHour = 0;

void getDateHour(char leitura)
{
    //$GPRMC,225446.000,A,4916.45,N,12311.12,W,000.5,054.7,191194,020.3,E*68
    
  if(leitura == '$' && isGPRMC == false)
    {
      countGPRMC ++;
    }
    else if (leitura == 'G' && isGPRMC == false)
    {
      countGPRMC ++;
    }
    else if (leitura == 'P' && isGPRMC == false)
    {
      countGPRMC ++;
    }
    else if (leitura == 'R' && isGPRMC == false)
    {
      countGPRMC ++;
    }
    else if (leitura == 'M' && isGPRMC == false)
    {
      countGPRMC ++;
    }
    else if (leitura == 'C' && isGPRMC == false)
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
       horaFormatada = "";
       isGPRMC = true;
    }
    
    if(leitura == ',' && isGPRMC) //contando o numero de virgulas para achar a data apos a nona virgula
    {
      commaNumber++;
    }
    
    
    if(commaNumber == 1) // a hora se encontra após a primeira virgula
    {
      if(leitura == '.') //verificação para não receber milessimos no momento de coletar hora
      {
        isDot = true;
      }
      
      if(leitura != ',' && isDot == false) //para não pegar a virgula que antecede a hora
      { 
        if(formatHour == 2)
          horaFormatada += ":";
        if(formatHour == 4)
          horaFormatada += ":";
          
        horaFormatada += leitura;
        formatHour ++;
      }
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
      isDot = false;
      countGPRMC = 0;
      formatDate = 0;
      formatHour = 0;
    }
}

void loop()
{
  if (Serial1.available() > 0 ) {
    
    //  Lê caracteres vindos do GPS
    char leitura = Serial1.read();
    
    getDateHour(leitura);
    
    //  Verifica se o valor recebido e uma sentença GPS valida
    if (gps.decode(leitura)) {
       Serial.println("Decodificou");
      
      
      if (gps.gprmc_status() == 'A') { //  Verifica se o posicionamento GPS esta ativo
        
        latitude = gps.gprmc_latitude();
        longitude = gps.gprmc_longitude();
        //hora = gps.gprmc_utc(); //hora no formato flutuante
        velocidade = gps.gprmc_speed(KMPH);
                
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

//Programa : GPS Logger
//Alteracoes e adaptacoes : FILIPEFLOP
 
#include <SD.h>
#include <SPI.h>

void setup()
{
  Serial.begin(38400);
  Serial1.begin(38400);
  pinMode(SS, OUTPUT);
  if (!SD.begin(10, 11, 12, 13))
  {
    Serial.println("Erro ao abrir cartao SD");  
    return;
  }
  else
  {
    Serial.println("Sucesso ao abrir cartao SD");
    /*
    if (SD.exists("gps_log.txt"))
    {    
      Serial.println("Apagando Arquivo ");
      SD.remove("gps_log.txt");
    }
    */
  }
}
 
void loop()
{
  // make a string for assembling the data to log:
  char index = 0;
  char temp = 0;
  String dataString = "";
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  /*
    while(Serial.available())
    {
      File dataFile = SD.open("datalog.txt", FILE_WRITE);
      if(dataFile)
      {
        temp = Serial.read();
        dataString += String(temp);
        dataFile.print(dataString);
        dataString = "";
        dataFile.close();
      }
    }
  */ 
File dataFile = SD.open("eu_log.txt", FILE_WRITE);
 if(dataFile)
 {
   while(Serial1.available() > 0)
   {
     temp = Serial1.read();
     dataString += String(temp);
     index++;
     if(index>200)
       break;
   }
   dataFile.print(dataString);
   Serial.println(dataString); 
   dataFile.close();
 }
}

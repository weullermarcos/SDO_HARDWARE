
/*
Fonte: https://learn.adafruit.com/adafruit-data-logger-shield/for-the-mega-and-leonardo
*/
#include <SPI.h> 
#include <SD.h>

File myFile;
const int chipSelect = 10;

void setup()
{
  Serial.begin(38400);
  pinMode(10, OUTPUT);
  if (!SD.begin(10, 11, 12, 13))
  {
    Serial.println("Erro ao abrir cartao SD");  
    return;
  }
  else
  {
    Serial.println("Sucesso ao abrir cartao SD");
    
    myFile = SD.open("test.txt", FILE_WRITE);
    if(myFile)
    {
      Serial.println("Arquivo Aberto com sucesso"); 
      
      myFile.println("testing 1, 2, 3.");
      myFile.close();
    }
    else
    {
      Serial.println("Erro ao abrir Arquivo"); 
    }
  }
}
 
void loop()
{
   Serial.println("teste");
  delay(3000); 
}

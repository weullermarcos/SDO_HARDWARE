
 
#include <SPI.h>
#include <SD.h>

File myFile;

String placa;
String nOnibus;
String nPassageiros;

void removeCharacters() //função para remover os caracteres de nova linha e tabulação
{
  myFile.read(); //remove /n
  myFile.read();// remove /r
}

void setup()
{
   /*
  Formato dos dados no cartão SD:
  WWW-2577; --->Placa
  12345678; --->Numero do Ônibus
  150;      --->Número de passageiros
  */
  
  Serial.begin(38400);
  pinMode(SS, OUTPUT);
   
  if (!SD.begin(10, 11, 12, 13)){
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("inicializado com sucesso.");
  
  char aux;
  
  myFile = SD.open("CONF.TXT");
  if (myFile) 
  {
    while (myFile.available()) {
      //Serial.write(myFile.read());
      
      while(1)//capturando placa
      {
        aux = (char) myFile.read();
        if(aux == ';')
          break;
        placa += aux;
      }
      
      removeCharacters();
      
      while(1)//capturando numero do onibus
      {
        aux = (char) myFile.read();
        if(aux == ';')
          break;
        nOnibus += aux;
      }
      
      removeCharacters();
      
      while(1)//capturando numero de passageiros
      {
        aux = (char) myFile.read();
        if(aux == ';')
          break;
        nPassageiros += aux;
      }
      
      break;
    }

    myFile.close();
  } 
  else 
  {
    Serial.println("erro ao ler arquivo");
  }
}

void loop()
{
  Serial.println("Placa:");
  Serial.println(placa);
  
  Serial.println("Numero do Onibus:");
  Serial.println(nOnibus);
  
  Serial.println("Numero de Passageiros:");
  Serial.println(nPassageiros);
  
  delay(1000);
}



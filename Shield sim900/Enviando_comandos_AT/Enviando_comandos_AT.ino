void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("vamos comecar...");
}
char aux;
void loop ()
{
  //Serial.println(Serial1.read());
  
  //if(Serial.available())
  {     
      Serial.println("Comando: AT+CPIN?");
      Serial1.println("AT+CPIN?");
      delay(1000);
      Serial.println("Resposta:"); //Resultado esperado: +CPIN:READY OK
      ShowSerialData();
      Serial.println("");
      
      Serial.println("Comando: AT+CSQ"); //Resultado esperado: CSQ: 20,0 OK
      Serial1.println("AT+CSQ");
      delay(1000);
      Serial.println("Resultado:");  
      ShowSerialData();
      Serial.println("");
      
      Serial.println("Comando: AT+CREG?");
      Serial1.println("AT+CREG?"); //Resultado esperado: +CREG: 0,1 OK
      delay(1000);
      Serial.println("Resultado:");  
      ShowSerialData();
      Serial.println("");
      
      Serial.println("Comando: AT+CGATT?");
      Serial1.println("AT+CGATT?"); //Resultado esperado: +CREG: 0,1 OK
      delay(1000);
      Serial.println("Resultado:");  
      ShowSerialData();
      Serial.println("");
      
      //Define APN, usuáro e senha
      Serial.println("Comando: AT+CSTT");
      Serial1.println("AT+CSTT=\"claro.com.br\",\"claro\",\"claro\""); //Resultado esperado: +CREG: 0,1 OK
      delay(1000);
      Serial.println("Resultado:");  
      ShowSerialData();
      Serial.println("");
  }
}

void ShowSerialData()
{
  while(Serial1.available()!=0)
    Serial.write(Serial1.read());
}

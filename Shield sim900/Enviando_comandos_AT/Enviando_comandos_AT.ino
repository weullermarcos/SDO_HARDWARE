      //Serial1.println("AT+CSTT=\"java.claro.com.br\",\"claro\",\"claro\"");
      //Serial1.println("AT+CSTT=\"wap.claro.com.br\",\"claro\",\"claro\"");
      //Serial1.println("AT+CSTT=\"streaming.claro.com.br\",\"claro\",\"claro\"");
      //Serial1.println("AT+CSTT=\"mms.claro.com.br\",\"claro\",\"claro\"");
      //Serial1.println("AT+CSTT=\"bandalarga.claro.com.br\",\"claro\",\"claro\"");

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("vamos comecar...");
}
char aux;
void loop ()
{
  testeSite();
  //APN();
  //comandos();
}

void comandos()
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
      Serial1.println("AT+CGATT?"); //Resultado esperado: +CGATT:1 OK
      delay(1000);
      Serial.println("Resultado:");  
      ShowSerialData();
      Serial.println("");
      
      //APN();
}

void APN()
{
  /**/
      //Define APN, usuáro e senha
      Serial.println("Comando: AT+CSTT");
      Serial1.println("AT+CSTT=\"claro.com.br\",\"claro\",\"claro\"");      
      delay(10000);
      Serial.println("Resultado:");  
      ShowSerialData();
      Serial.println("");
      
     
      Serial.println("Comando: AT+CIICR");
      Serial1.println("AT+CIICR"); 
      delay(1000);
      Serial.println("Resultado:");  
      ShowSerialData();
      Serial.println("");

       
      //PEGANDO IP LOCAL
      Serial.println("Comando: AT+CIFSR"); 
      Serial1.println("AT+CIFSR"); 
      delay(1000);
      Serial.println("Resultado:");  
      ShowSerialData();
      Serial.println(""); 
  
  /**/ 
      Serial.println("Comando: AT+CIPSTART");
      Serial1.println("AT+CIPSTART=\"TCP\",\"116.228.221.51\",\"8500\""); 
      delay(1000);
      Serial.println("Resultado:");  
      ShowSerialData();
      Serial.println("");  
    
      Serial.println("Comando: AT+CIPSEND");
      Serial1.println("AT+CIPSEND"); 
      delay(1000);
      Serial.println("Resultado:");  
      ShowSerialData();
      Serial.println("");  
 
}

void testeSite()
{
//Fonte: http://vsblogs.wordpress.com/2013/11/28/tcp-connection-over-gprs-using-sim900-and-at-commands/
  
    Serial.println("Comando: AT+CIPSHUT"); //Fechando possivel conexão antiga
    Serial1.println("AT+CIPSHUT");  
    delay(5000); //
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT");
    Serial1.println("AT"); 
    delay(1000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+CPIN?"); //verifica se o chip está desbloqueado
    Serial1.println("AT+CPIN?"); 
    delay(1000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+CREG?"); //verifica se chip está registrado
    Serial1.println("AT+CREG?"); 
    delay(1000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+CGATT?"); //verifica se GPRS está ligado ou não
    Serial1.println("AT+CGATT?"); 
    delay(1000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+CIPSHUT"); //Reseta a sessão do IP, se existir
    Serial1.println("AT+CIPSHUT"); 
    delay(1000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
        
    Serial.println("Comando: AT+CIPSTATUS"); //Verifica se a pilha IP está inicializada
    Serial1.println("AT+CIPSTATUS"); 
    delay(1000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+CIPMUX=0"); //Setando uma conexão simples
    Serial1.println("AT+CIPMUX=0"); 
    delay(1000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    //PRECISA CONFIGURAR O MODO (TRANSPARENTE OU NÃO) ????
    
    Serial.println("Comando: AT+CSTT"); //Conectando a APN
    Serial1.println("AT+CSTT=\"claro.com.br\",\"claro\",\"claro\""); 
    delay(5000); //5s
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");

    Serial.println("Comando: AT+CIICR"); //Conectando a wireless (**PODE DEMORAR UM TEMPO**)
    Serial1.println("AT+CIICR"); 
    delay(30000); //
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");

    Serial.println("Comando: AT+CIFSR"); //Recebendo endereço IP
    Serial1.println("AT+CIFSR"); 
    delay(5000); //
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+CIPSTART"); //conectando ao site
    //Serial1.println("AT+CIPSTART=\"TCP\",\"papeldasilva123.com.br\",\"80\"");      //-------- URL não existente
    //Serial1.println("AT+CIPSTART=\"TCP\",\"sdo-server.herokuapp.com\",\"80\"");  //-------- URL SDO Server
    Serial1.println("AT+CIPSTART=\"TCP\",\"www.vishnusharma.com\",\"80\"");      //-------- URL de exemplo do site
    delay(10000); // talvez tenhamos que almentar este tempo
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+CIPSEND"); //Requisição inicial para envio de dados
    Serial1.println("AT+CIPSEND"); 
    delay(5000); //
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("ENVIANDO DADOS.."); //ENVIANDO DADOS
    Serial1.println("latitude=10.456");
    Serial1.println("longitude=-10.456");
    Serial1.println("data=25/05/1992"); 
    delay(3000); //
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Fechando envio de dados"); //ENVIANDO DADOS
    //Serial1.println("#026");  //enviando Ctrl + Z para fechar o envio de dados
    Serial1.println("0x1A");  //enviando para fechar o envio de dados
    delay(1000); //
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
}

void ShowSerialData()
{
  while(Serial1.available()!=0)
    Serial.write(Serial1.read());
}

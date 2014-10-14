

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("vamos comecar...");
  Serial.println("**********************************************************************************************");
  
  //conexaoHTTPPOST();
  conexaoHTTPGET();
}
char aux;
void loop ()
{
  //conexaoTCP();
}

void conexaoHTTPPOST()
{
    Serial.println("---------POST---------");
    
    Serial.println("Comando: AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
    Serial1.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\""); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+SAPBR=3,1,\"APN\",\"yourAPN\""); 
    Serial1.println("AT+SAPBR=3,1,\"APN\",\"claro.com.br\""); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+SAPBR=3,1,\"USER\",\"yourUser\"");
    Serial1.println("AT+SAPBR=3,1,\"USER\",\"claro\""); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");

    Serial.println("Comando: AT+SAPBR=3,1,\"PWD\",\"YourPWD\"");
    Serial1.println("AT+SAPBR=3,1,\"PWD\",\"claro\""); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");

    Serial.println("Comando: AT+SAPBR=1,1"); 
    Serial1.println("AT+SAPBR=1,1"); 
    delay(10000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
 
    Serial.println("Comando: AT+SAPBR=2,1"); 
    Serial1.println("AT+SAPBR=2,1"); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");

    /*INIcia requisição HTTP*/
    Serial.println("Comando: AT+HTTPINIT"); 
    Serial1.println("AT+HTTPINIT"); 
    delay(7000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+HTTPPARA"); 
    Serial1.println("AT+HTTPARA=\"CID,1\""); 
    delay(5000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+HTTPPARA"); 
    //Serial1.println("AT+HTTPPARA=\"URL\",\"www.sim.com\"");
    Serial1.println("AT+HTTPPARA=\"URL\",\"sdo-server.herokuapp.com/save/bus/position\"");  
    delay(10000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");    

    Serial.println("Comando: AT+HTTPPARA");  
    Serial1.println("AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"");
    //Serial1.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");   
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println(""); 
    
    Serial.println("Comando: AT+HTTPDATA"); 
    Serial1.println("AT+HTTPDATA=100,10000"); 
    delay(10000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("MANDANDO JSON:");  
    Serial1.println("json={\"latitude\":\"-16.694177\", \"longitude\":\"-48.790577\", \"date\":\"07/10/2014 03:51:00\", \"speed\":\"55\", \"positionSense\":\"TO_END_POINT | TO_START_POINT\", \"bus\": {\"licensePlate\": \"OVR-5555\", \"busNumber\":\"55577777\", \"capacity\":\"55\", \"itinerary\": { \"routeNumber\": \"921\", \"startPoint\": \"Setor Q\", \"endPoint\": \"W3 Sul\"}}}");   
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println(""); 
    
    
    /*Define CACTION da requisição HTTP como POST*/
    Serial.println("Comando: AT+HTTPACTION=1"); 
    Serial1.println("AT+HTTPACTION=1"); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    /*verificando status da conexão HTTP*/
    Serial.println("Comando: AT+HTTPSTATUS?");  
    Serial1.println("AT+HTTPSTATUS?"); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    /*Encerra conexão HTTP*/
    Serial.println("Comando: AT+HTTPTERM"); 
    Serial1.println("AT+HTTPTERM"); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
   
}

void conexaoHTTPGET()
{  
    Serial.println("---------GET---------");
    

    Serial.println("Comando: AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
    Serial1.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\""); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+SAPBR=3,1,\"APN\",\"yourAPN\""); 
    Serial1.println("AT+SAPBR=3,1,\"APN\",\"claro.com.br\""); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+SAPBR=3,1,\"USER\",\"yourUser\"");
    Serial1.println("AT+SAPBR=3,1,\"USER\",\"claro\""); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");

    Serial.println("Comando: AT+SAPBR=3,1,\"PWD\",\"YourPWD\"");
    Serial1.println("AT+SAPBR=3,1,\"PWD\",\"claro\""); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
  
    Serial.println("Comando: AT+SAPBR=1,1"); 
    Serial1.println("AT+SAPBR=1,1"); 
    delay(10000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");

    Serial.println("Comando: AT+SAPBR=2,1"); 
    Serial1.println("AT+SAPBR=2,1"); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");

    Serial.println("Comando: AT+HTTPINIT"); 
    Serial1.println("AT+HTTPINIT"); 
    delay(5000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+HTTPPARA"); 
    Serial1.println("AT+HTTPARA=\"CID,1\""); 
    delay(5000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+HTTPPARA"); 
    //Serial1.println("AT+HTTPPARA=\"URL\",\"sdo-server.herokuapp.com/find/bus/position/byLicensePlate/JFJ-1593\""); //Buscar localizações por placa
    //Serial1.println("AT+HTTPPARA=\"URL\",\"sdo-server.herokuapp.com/find/bus/position/byLineItinerary/813.1\""); //Buscar localizações por Linha
    //Cadastra dados
    Serial1.println("AT+HTTPPARA=\"URL\",\"sdo-server.herokuapp.com/save/bus/position?latitude=-52.694177&longitude=-62.790577&date=11/10/2014%2012:59:00&speed=80&positionSense=TO_START_POINT&licensePlate=WWW-2525&busNumber=12345678&capacity=100&routeNumber=0.809&startPoint=Recanto%20das%20Emas&endPoint=Rod%20P%20Piloto\""); 
    
    delay(10000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
   
    Serial.println("Comando: AT+HTTPACTION=0"); 
    Serial1.println("AT+HTTPACTION=0"); 
    delay(10000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    /*verificando status da conexão HTTP*/
    Serial.println("Comando: AT+HTTPSTATUS?");  
    Serial1.println("AT+HTTPSTATUS?"); 
    delay(2000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
   
    Serial.println("Comando: AT+HTTPREAD"); 
    Serial1.println("AT+HTTPREAD"); 
    delay(10000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Comando: AT+HTTPTERM"); 
    Serial1.println("AT+HTTPTERM"); 
    delay(5000);
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
}


void conexaoTCP()
{
//Fonte: http://vsblogs.wordpress.com/2013/11/28/tcp-connection-over-gprs-using-sim900-and-at-commands/
     
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
    delay(10000); //
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
    delay(3000); //
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
    
    Serial.println("Fechando envio de dados"); //Fechando conexão
    //Serial1.println("#026");  //enviando Ctrl + Z para fechar o envio de dados
    Serial1.println("0x1A");  //enviando para fechar o envio de dados
    delay(10000); //
    Serial.println("Resultado:");  
    ShowSerialData();
    Serial.println("");
        
}

void ShowSerialData()
{
  while(Serial1.available()!=0)
    Serial.write(Serial1.read());
}

/*
Projedo SDO - Sistema Detector de Ônibus
Autores: Eduardo, Weuller
Data Inicio: 13/08/2014
Data Fim: XX/XX/2014


Arquivo de Integração dos Módulos
*/

#include <Keypad.h>          //Biblioteca para manipulação de teclado númerico
#include <LiquidCrystal.h>   //Biblioteca para manipulação de display LCD
#include <SPI.h>             //Biblioteca para configurar pinos para leitura de dados do cartão SD
#include <SD.h>              //Biblioteca para uso de cartão SD
#include <nmea.h>            //Biblioteca para decodificar informações lidas do GPS

NMEA gps(ALL); //Instancia da classe nmea para leitura de dadod do Módulo GPS
File myFile;   //Criando objeto File para leitura/gravação de dados no cartão SD

#define LINE_NUMBER_LENGHT 6 //NUMERO DE ELEMENTOS DO VETOR QUE GUARDA A LINHA - DECLARAR COM UM INDICE A MAIS QUE O NECESSARIO POR CAUSA DO \0 FINAL
#define GET_GPS_DATA_WITH_SUCESS_LED 25
#define GET_GPS_DATA_WITH_ERROR_LED  23

/************ INICIO - BLOCO DE CONFIGURAÇÃO DE VARIÁVEIS PARA TECLADO NÚMERICO ***********************/
/*
Fonte:http://abedulengenharia.blogspot.com.br/2011/07/arduino-y-teclado-3x4.html

       Coluna 1    Coluna 2    Coluna 3
Linha 1    1          2            3
Linha 2    4          5            6
Linha 3    7          8            9
Linha 4    .          0            back-space


Pinos:

Pino 1 do teclado: Corresponde à Coluna 2
Pino 2 do teclado: Corresponde à Linha 1
Pino 3 do teclado: Corresponde à Coluna 1
Pino 4 do teclado: Corresponde à Linha 4
Pino 5 do teclado: Corresponde à Coluna 3
Pino 6 do teclado: Corresponde à Linha 3
Pino 7 do teclado: Corresponde à Linha 2

Disposição dos Pinos:
------------------------------->
NULL  1  2  3  4  5  6  7  NULL
*/

const byte coluna_1 = 41; //Pino 3 do teclado na porta 41 do Arduino
const byte coluna_2 = 39; //Pino 1 do teclado na porta 39 do Arduino
const byte coluna_3 = 37; //Pino 5 do teclado na porta 37 do Arduino

const byte linha_1 = 35;// Pino 2 do teclado na porta 35 do Arduino
const byte linha_2 = 33;// Pino 7 do teclado na porta 33 do Arduino
const byte linha_3 = 31;// Pino 6 do teclado na porta 31 do Arduino
const byte linha_4 = 29;// Pino 4 do teclado na porta 29 do Arduino
 
const byte ROWS = 4; // Quatro linhas
const byte COLS = 3; // Quatro colunas

char numberKeys[ROWS][COLS] = {
    { '1','2','3' },
    { '4','5','6' },
    { '7','8','9' },
    { '.','0','#' }
};

const byte BTN_OK = 27; //Botão para confimar linha digitada

//Pinos do Arduino correspondentes as linhas
byte rowPins[ROWS] = {linha_1, linha_2, linha_3, linha_4}; //connect to the row pinouts of the keypad

//Pinos do Arduino correspondentes as Colunas
byte colPins[COLS] = {coluna_1, coluna_2, coluna_3}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(numberKeys), rowPins, colPins, ROWS, COLS); 

/********** FIM - BLOCO DE CONFIGURAÇÃO DE VARIÁVEIS PARA TECLADO NÚMERICO ****************************/


/************ INICIO - BLOCO DE CONFIGURAÇÃO DE VARIÁVEIS PARA DISPLAY LCD ***********************/

/*
Pinos utilizados:
Display  Significado  Arduino
01-------Vss------------>GND
02-------VCC------------>5V
03-------VO------------->Resistor de 330 Ohms + GND
04-------RS------------->53
05-------R/W------------>GND
06-------ENABLE--------->51
07-------DB0------------>Não Utilizado
08-------DB1------------>Não Utilizado
09-------DB2------------>Não Utilizado
10-------DB3------------>Não Utilizado
11-------DB4------------>49
12-------DB5------------>47
13-------DB6------------>45
14-------DB7------------>43
15-------ANODO---------->5V
16-------CATODO--------->GND


Disposição dos Pinos:
------------------------------------------------>
14 13 12 11 10 09 08 07 06 05 04 03 02 01 15 16
*/

const byte RS     = 53; //Pino 04 do Display na porta 53 do Arduino
const byte ENABLE = 51; //Pino 06 do Display na porta 51 do Arduino
const byte DB4    = 49; //Pino 11 do Display na porta 49 do Arduino
const byte DB5    = 47; //Pino 12 do Display na porta 47 do Arduino
const byte DB6    = 45; //Pino 13 do Display na porta 45 do Arduino
const byte DB7    = 43; //Pino 14 do Display na porta 43 do Arduino

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(RS, ENABLE, DB4, DB5, DB6, DB7);

char lineNumber[LINE_NUMBER_LENGHT];//Variável para guardar a linha do onibus digitada LEMBRAR QUE ELE COLOCA UM \0 NO FINAL
byte lineNumberIndex = 0; //variavel auxiliar para guardar o indice da linha do onibus

/************ FIM - BLOCO DE CONFIGURAÇÃO DE VARIÁVEIS PARA DISPLAY LCD ***********************/

float latitude;
float longitude;
float hora;
float velocidade;

String placa;
String nOnibus;
String nPassageiros;

/************ INICIO - BLOCO DE CONFIGURAÇÃO DE VARIÁVEIS PARA CARTÃO SD ***********************/
String dataString = "";
int nmeaStringCount = 0;
/************ FIM - BLOCO DE CONFIGURAÇÃO DE VARIÁVEIS PARA CARTÃO SD ***********************/

/************ ASSINATURA DAS FUNÇÕES ***********************/
void initialDisplayMessage();//Mostra msg inicial no Display LCD
void fixedDisplayMessage();  //Mensagem com a linha que está sendo feita
void insertLineNumber(char receivedNumber); //Inserir linha
void backSpace(); //Função para apagar caracteres
void removeCharacters(); //função para remover caracteres /n e /t na leitura dos dados do cartão SD
void getLocalSDData(); //pega os dados gravados no cartão SD
void saveNmeaFile(String data); //função para salvar arquivo nmea
void blinkSucessLed();
void blinkErrorLed();

void setup(){
  
  Serial.begin(38400);
  Serial1.begin(38400); //habilitando serial1 para ler dados do GPS
  lcd.begin(16, 2); //Setando número de colunas e linhas do Display LCD --- 16 colunas, 2 linhas
  initialDisplayMessage();
  
  pinMode(SS, OUTPUT); //Configura pino para leitura de dados do cartão SD
  if (!SD.begin(10, 11, 12, 13))
  {
    Serial.println("Erro ao iniciar cartão SD!");
    return;
  }
  
  /*Configurando botão para confirmar linha digitada*/
  pinMode(BTN_OK,INPUT);
  digitalWrite(BTN_OK,HIGH);
  
  Serial.println("Esperando digitar a linha...");
  while(digitalRead(BTN_OK) != LOW) //enquanto botão de confirmar a linha não for precionado
  {
    char customKey = customKeypad.getKey();
    if(customKey){
      
      switch(customKey){
        case '#':
          backSpace();
          break;   
        default:
          insertLineNumber(customKey); //Escreve no Display
          break;
      }
    }
  }
  
  fixedDisplayMessage();
  
  Serial.println(lineNumber);
  
  getLocalSDData();//Após pegar a linha busca dados armazenados no cartão SD
  
  pinMode(GET_GPS_DATA_WITH_SUCESS_LED,OUTPUT);
  digitalWrite(GET_GPS_DATA_WITH_SUCESS_LED, LOW);
  
  pinMode(GET_GPS_DATA_WITH_ERROR_LED,OUTPUT);
  digitalWrite(GET_GPS_DATA_WITH_ERROR_LED, LOW);
  
}
void loop(){
  
  /*******************COLETANDO DADOS DO GPS***********************************/
  if (Serial1.available() > 0 ) {
    
    // Lê caracteres vindos do GPS na porta Serial 1
    char leitura = Serial1.read();
    //Serial.println(leitura);
    
    dataString += String(leitura);
    nmeaStringCount ++;
    
    if(nmeaStringCount > 200) //mandar um bloco de dados para serem gravados
    {
      saveNmeaFile(dataString);
      dataString = "";
      nmeaStringCount = 0;
    }
    
    //  Verifica se o valor recebido e uma sentença GPS valida
    if (gps.decode(leitura)) 
    {
      Serial.println("Decodificou");
      
      if (gps.gprmc_status() == 'A') //  Verifica se o posicionamento GPS esta ativo
      { 
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
        
        Serial.print("Linha do onibus: ");
        Serial.println(lineNumber);
        
        Serial.print("Placa:");
        Serial.println(placa);
  
        Serial.print("Numero do Onibus:");
        Serial.println(nOnibus);
  
        Serial.print("Numero de Passageiros:");
        Serial.println(nPassageiros);
        
        Serial.println("");
        
        blinkSucessLed();
       }
       else
       {
         blinkErrorLed();
       }
     }
  }
  /**********************************************************************************/
}

void initialDisplayMessage(){
  
  lcd.print("Bem Vindo..."); 
  lcd.setCursor(0, 1); 
  lcd.print("Carregando SDO..");
  delay(4000); //delay de 4 segundos
  lcd.clear(); //Limpando Display
  lcd.setCursor(0, 0);
  lcd.print("Digite a Linha:"); //Escrevendo no LCD
}

void fixedDisplayMessage(){
  lcd.clear(); //Limpando Display
  lcd.setCursor(0, 0); 
  lcd.print("Linha:"); 
  lcd.setCursor(0, 1);
  lcd.print(lineNumber);
}

void insertLineNumber(char receivedNumber){
  
   if(lineNumberIndex < LINE_NUMBER_LENGHT -1){ //Inserindo número digitado //UM INDICE A MENOS PARA COLOCAR O \0
     
     lineNumber[lineNumberIndex] = receivedNumber;
     lcd.setCursor(0, 1); //setando o cursor na posição inicial (0) da segunda linha do display (1 - começa a contar de 0)
     lcd.print(lineNumber); //Escrevendo no LCD
     Serial.println(lineNumber);
     lineNumberIndex++;
   }
}

void backSpace(){

  if(lineNumberIndex > 0){ //Back-space (#)
   
   lineNumberIndex--; 
   lineNumber[lineNumberIndex] = NULL;
   
    lcd.clear(); //Limpando Display
    lcd.setCursor(0, 0);
    lcd.print("Digite a Linha:"); //Escrevendo no LCD
    lcd.setCursor(0, 1);
    
    lcd.print(lineNumber); //Escrevendo no LCD  
 } 
}

void removeCharacters() //função para remover os caracteres de nova linha e tabulação
{
  myFile.read(); //remove /n
  myFile.read();// remove /r
}

void getLocalSDData() //pega os dados gravados no cartão SD
{
  /*
  Formato dos dados no cartão SD:
  WWW-2577; --->Placa
  12345678; --->Numero do Ônibus
  150;      --->Número de passageiros
  */
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

void saveNmeaFile(String data) //função para salvar arquivo nmea
{
  myFile = SD.open("nmea.txt", FILE_WRITE);
  if(myFile)
  {
    myFile.print(data);
    myFile.close();
    Serial.println("Gravou nmea..");
  }
  else
  {
    Serial.println("Erro ao Gravar nmea..");
  }
}

void blinkSucessLed()
{
  digitalWrite(GET_GPS_DATA_WITH_SUCESS_LED, HIGH);
  delay(100); 
  digitalWrite(GET_GPS_DATA_WITH_SUCESS_LED, LOW); 
}

void blinkErrorLed()
{
  digitalWrite(GET_GPS_DATA_WITH_ERROR_LED, HIGH);
  delay(100);
  digitalWrite(GET_GPS_DATA_WITH_ERROR_LED, LOW);
}




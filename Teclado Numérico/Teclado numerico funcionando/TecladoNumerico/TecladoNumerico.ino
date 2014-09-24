/* 
Autores: Eduardo/Weuller
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
#include <Keypad.h>

const byte coluna_1 = 41; //Pino 3 do teclado na porta 41 do Arduino
const byte coluna_2 = 39; //Pino 1 do teclado na porta 39 do Arduino
const byte coluna_3 = 37; //Pino 5 do teclado na porta 37 do Arduino

const byte linha_1 = 35;// Pino 2 do teclado na porta 35 do Arduino
const byte linha_2 = 33;// Pino 7 do teclado na porta 33 do Arduino
const byte linha_3 = 31;// Pino 6 do teclado na porta 31 do Arduino
const byte linha_4 = 29;// Pino 4 do teclado na porta 29 do Arduino
 
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns

//define the cymbols on the buttons of the keypads
char numberKeys[ROWS][COLS] = {
    { '1','2','3' },
    { '4','5','6' },
    { '7','8','9' },
    { '.','0','#' }
};

//Pinos do Arduino correspondentes as linhas
byte rowPins[ROWS] = {linha_1, linha_2, linha_3, linha_4}; //connect to the row pinouts of the keypad

//Pinos do Arduino correspondentes as Colunas
byte colPins[COLS] = {coluna_1, coluna_2, coluna_3}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(numberKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}

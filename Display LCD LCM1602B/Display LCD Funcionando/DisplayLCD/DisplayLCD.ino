/*
Autor: Weuller Marcos da Silva Santos
Data : 05/08/2014

Display utilizado: LCM1602B
Esquemático deligações para Arduino Mega 2560

Pinos utilizados:
Display  Significado  Arduino
01-------Vss------------>GND
02-------VCC------------>5V
03-------VO------------->Resistor de 330 Ohms + GND
04-------RS------------->53 | 2
05-------R/W------------>GND
06-------ENABLE--------->51 | 3
07-------DB0------------>Não Utilizado
08-------DB1------------>Não Utilizado
09-------DB2------------>Não Utilizado
10-------DB3------------>Não Utilizado
11-------DB4------------>49 | 4
12-------DB5------------>47 | 5
13-------DB6------------>45 | 6
14-------DB7------------>43 | 7
15-------ANODO---------->5V
16-------CATODO--------->GND


Disposição dos Pinos:
------------------------------------------------>
14 13 12 11 10 09 08 07 06 05 04 03 02 01 15 16
 */

// include the library code:
#include <LiquidCrystal.h>

/*Configuração para Arduino MEGA 2560
byte RS     = 53;
byte ENABLE = 51;
byte DB4    = 49;
byte DB5    = 47;
byte DB6    = 45;
byte DB7    = 43;

//*/

//*Configuração para Arduino UNO/DUEMILANOVE
byte RS     = 2;
byte ENABLE = 3;
byte DB4    = 4;
byte DB5    = 5;
byte DB6    = 6;
byte DB7    = 7;

//*/

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(RS, ENABLE, DB4, DB5, DB6, DB7);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
}


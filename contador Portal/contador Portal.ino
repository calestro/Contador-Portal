#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <string.h>

#define b 256 // Representation of max int value in 1 byte  => (0xFF) ([11111111])

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int entrada = EEPROM.read("entrada");
int saida = EEPROM.read("saida");
int one = 7;
int two = 8;

void saveValue(unsigned int value, string address[4]){

  unsigned char bytes[4];

  bytes[0] = (value >> 24) & 0xFF;
  bytes[1] = (value >> 16) & 0xFF;
  bytes[2] = (value >> 8) & 0xFF; 
  bytes[3] = value & 0xFF;   

  for(int i = 0; i < 4; i++){
    EEPROM.write(address[i], bytes[i]);
  }
  
}

unsigned int getValue(string address[4]){

  unsigned char bytes[4];

  for(int i = 0; i < 4; i++){
    bytes[i] = EEPROM.read(address[i]);
  }

  unsigned int reconvert = bytes[3] + (bytes[2] * b) + ((bytes[1] * b) * b) + (((bytes[0] * b) * b) * b);

  return reconvert;

}

void setup()
{
pinMode(1,INPUT_PULLUP);
pinMode(0,INPUT_PULLUP);
lcd.setCursor(0,0);
lcd.print("RFID BRASIL");
lcd.setCursor(0,1);
lcd.print("Vesão 1.0.3");
lcd.setCursor(0,3);
lcd.print("Iniciando");
delay(1000);
lcd.clear();
}

void loop(){


  if(EEPROM.read("entrada") == 250){
    EEPROM.write("entrada",0);
  }

  
  if(EEPROM.read("saida") == 255){
    EEPROM.write("saida",0);  
  }
  
  
  
  lcd.begin(20, 4);

  for(;;){
    reset();
    lcd.setCursor(0,0);
    lcd.print("Entrada: ");
    lcd.setCursor(10,0);
    lcd.print(entrada);
    lcd.setCursor(0,3);
    lcd.print("Saida: ");
    lcd.setCursor(10,3);
    lcd.print(saida);

    int i = 0;


    
    if(digitalRead(one) && digitalRead(two)){
      delay(500);
    }
    
  

    
    else if(digitalRead(one)){
      while (true){
        reset();
        delay(200);
        if(digitalRead(two)){
          entrada++;
          EEPROM.write("entrada",entrada);
          delay(1000);
          break;
        }
        else if(digitalRead(two) && digitalRead(one)){
          break;
        }
        else{
          i++;
          if(i == 300){
            break;
          }
        }
      }
    }

    else if(digitalRead(two)){
      while (true){
        reset();
        delay(200);
        if(digitalRead(one)){
          saida++;
          EEPROM.write("saida",saida);
          delay(1000);
          break;
        }
        else if(digitalRead(two) && digitalRead(one)){
          break;
        }
        else{
          i++;
          if(i == 300){
            break;
          }
        }
      }
    }
}}

void reset(){
if(digitalRead(1) == LOW){
  lcd.clear();
  entrada = 0;
  saida = 0;
  EEPROM.write("entrada",0);
  EEPROM.write("saida",0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Resetando");
  delay(500);
  lcd.clear();
  delay(500);
  lcd.print("Resetando");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Entrada: ");
  lcd.setCursor(10,0);
    lcd.print(entrada);
    lcd.setCursor(0,3);
    lcd.print("Saida: ");
    lcd.setCursor(10,3);
    lcd.print(saida);
  }
  if(digitalRead(0) == LOW){
    lcd.clear();
    if (one == 7){
      one = 8;
      two = 7;
    }
    else{
      one = 7;
      two = 8;
    }
  lcd.setCursor(0,0);
  lcd.print("Mudando de Lado");
  delay(500);
  lcd.clear();
  delay(500);
  lcd.print("Mudando de Lado");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Entrada: ");
  lcd.setCursor(10,0);
  lcd.print(entrada);
  lcd.setCursor(0,3);
  lcd.print("Saida: ");
  lcd.setCursor(10,3);
  lcd.print(saida);
  }
}

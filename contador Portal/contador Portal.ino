#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <string.h>

#define b 256 // Representation of max int value in 1 byte  => (0xFF) ([11111111])


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int one = 7;
int two = 8;
int entradaArray[4]= {1, 2, 3, 4};
int saidaArray[4]={5, 6, 7, 8};
int entrada = 0;
int saida = 0;



void saveValue(int value, int address[4]){

  unsigned char bytes[4];

  bytes[0] = (value >> 24) & 0xFF;
  bytes[1] = (value >> 16) & 0xFF;
  bytes[2] = (value >> 8) & 0xFF; 
  bytes[3] = value & 0xFF;   

  for(int i = 0; i < 4; i++){
    EEPROM.write(address[i], bytes[i]);
  }
  
}

unsigned int getValue(int address[4]){

  unsigned char bytes[4];

  for(int i = 0; i < 4; i++){
    bytes[i] = EEPROM.read(address[i]);
  }

  unsigned int reconvert = bytes[3] + (bytes[2] * b) + ((bytes[1] * b) * b) + (((bytes[0] * b) * b) * b);

  return reconvert;

}

void setEntrada(){
  int i = 0;
  while(i != 300){
    i++;
    Serial.print(i);
    Serial.print("\n");
    if ((digitalRead(two))){
      Serial.print("cai entrada\n");
      entrada++;
      saveValue(entrada,entradaArray);
      break;
    }
    if(i == 299){
      break;
    }
  }
  delay(500);
}

void setSaida(){
  int i = 0;
  while(i != 300){
    i++;
    Serial.print(i);
    Serial.print("\n");
    if ((digitalRead(one))){
      Serial.print("cai saida\n");
      saida++;
      saveValue(saida,saidaArray);
      break;
    }
    if(i == 299){
      break;
    }
  }
  delay(500);
}

void setup(){
  
  Serial.begin(9600);
  entrada = getValue(entradaArray);
  saida = getValue(saidaArray);
  pinMode(1,INPUT_PULLUP);
  pinMode(0,INPUT_PULLUP);
  lcd.begin(20, 4);

}

void loop(){
    
    lcd.setCursor(0,0);
    lcd.print("RFID BRASIL ");
    lcd.setCursor(0,1);
    lcd.print("Contador de Fluxo");
    lcd.setCursor(0,3);
    lcd.print("Versao: 1.3.0");
    delay(5000);
    lcd.clear();
 
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

        if(digitalRead(one)){
          Serial.print("Esperando entrada\n");
          setEntrada();
        }

        if(digitalRead(two)){
          Serial.print("Esperando saida\n");
          setSaida();
        }
    }
}

void reset(){
  ///Botão de reset
if(digitalRead(1) == LOW){
    lcd.clear();
    entrada = 0;
    saida = 0;
    saveValue(0,entradaArray);
    saveValue(0,saidaArray);
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
  ///Mudar de Lado
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
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
  
}

void loop()
{
  int entrada = 0;
  int saida = 0;
  
  lcd.begin(20, 4);

  pinMode(7,INPUT);
  pinMode(8,INPUT);

  for(;;){
    Serial.begin(9600);
  
    lcd.setCursor(0,0);
    lcd.print("Entrada: ");
    lcd.setCursor(10,0);
    lcd.print(entrada);
    lcd.setCursor(0,3);
    lcd.print("Saida: ");
    lcd.setCursor(10,3);
    lcd.print(saida);

    int i = 0;
    
    if(digitalRead(7) && digitalRead(8)){
      delay(500);
    }
    
    
    
    else if(digitalRead(7)){
    
      while (true){
        delay(200);
        if(digitalRead(8)){
          entrada++;
          delay(1000);
          break;
        }
        else if(digitalRead(8) && digitalRead(7)){
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

    else if(digitalRead(8)){
      while (true){
        delay(200);
        if(digitalRead(7)){
          saida++;
          delay(1000);
          break;
        }
        else if(digitalRead(8) && digitalRead(7)){
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
//Projeto destinado a disciplina de HOW III - Segundo semestre de 2022

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sensor = 9;  //Pin definido para o sensor
int state = LOW; //Sem movimento por definição
int val = 0;
int buzzer = 7;  //Pin definido para o alarme
int vermelho = 13; //Pin definido para o LED
void setup() 
{
  //SETUP DO SENSOR E ALARME
  pinMode(sensor, INPUT);    //Sensor é uma entrada
  pinMode(buzzer, OUTPUT); //Alarme é uma saída
  lcd.begin(16, 2);

  //SETUP DA TEMPERATURA
  Serial.begin(9600);
  pinMode(A0,INPUT);
    	lcd.setCursor(0, 0);
		lcd.print("   BEM VINDO!");
    	lcd.setCursor(0, 1);
  		lcd.print("  CARREGANDO..");
  		Serial.println("BEM VINDO, ESTAMOS CUIDANDO DE TUDO, NAO SE PREOCUPE!");
		Serial.println("VERIFICANDO MOVIMENTO E TEMPERATURA");
  		delay(1500);

  //SETUP DO LED
		pinMode(vermelho,OUTPUT); //
}
void loop() {
  //TEMPERATURA - CONFIGURAÇÃO DO TERMÔMETRO
  float temp = ((analogRead(A0)*(5.0/1024))-0.5)/0.01; //temp = nome da variável
  delay(200);
  
  //FUNCIONAMENTO DO SISTEMA
  val = digitalRead(sensor);  		 //Lê o valor do sensor
  if (val == HIGH)
  {
  delay(100);              			//Delay 100ms 
    if (state == LOW) 
      {
      lcd.clear() ;
  	  lcd.setCursor(0, 0);			//Seleciona a primeira linha do display                
	  lcd.print(temp);
      lcd.print("C");
   	  lcd.setCursor(0, 1);			//Seleciona a segunda linha do display
      lcd.print("AGITO DETECTADO!");
      Serial.println(temp);			//Escreve para o MS
      Serial.println("AGITO DETECTADO!");
      digitalWrite(vermelho, HIGH); //Liga o LED
	  digitalWrite(buzzer, HIGH);   //Liga o alarme
      tone(buzzer,600);
      state = HIGH;       			//Muda o status para ligado
      delay(2000);  
       }  
     }
  else
   {
     delay(200);            		 // delay 200ms
      if (state == HIGH)
     {
        lcd.clear() ;
        lcd.setCursor(0, 0);                 
		lcd.print(temp);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("SEM AGITO");
        Serial.println(temp);
        Serial.println("SEM AGITO");
        digitalWrite(vermelho, LOW);   //Desliga o LED
        digitalWrite(buzzer, LOW);     //Desliga o alarme
        noTone(buzzer);
        state = LOW;     			   //Muda o status para desligado
        delay(1000);				   //Delay 1seg		
     }
   }
      if (state == 0) //Caso não seja LOW nem HIGH
  {
   		delay(100);
		lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("TEMPERATURA:");
        lcd.setCursor(0,1);
    	lcd.print(temp);
   		lcd.print("C");
        delay(100);

  }
	  if(temp>37.0) //Se a temperatura for acima de 37ºC = Febre)
  {
		digitalWrite(7,HIGH); //Alarme é acionado acima de 37ºC
        tone(buzzer,440);
        lcd.clear();
        lcd.print("TEMPERATURA ALTA");
        lcd.setCursor(0, 1);
        lcd.print(temp);
        lcd.print("C");
        Serial.println(temp);
        digitalWrite(vermelho, HIGH);   //Liga o LED
        delay(1000);
  }
  else
  {
		digitalWrite(7,LOW); //Alarme é desligado
    	noTone(buzzer);
  		delay(1000);
        digitalWrite(vermelho, LOW);   //Desliga o LED
  }

}
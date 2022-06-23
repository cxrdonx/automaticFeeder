
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLQvFw3QQx"
#define BLYNK_DEVICE_NAME "comedero"
#define BLYNK_AUTH_TOKEN "1pOkgTxt2yT3kz8p0BjCHcRdeLbdFhbA"
#include<Servo.h>
#include <iostream>
#include <string>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal_I2C.h>
#define activate V0
//#define temperature V6
LiquidCrystal_I2C lcd(0x27, 16, 2);

char ssid[] = "ECDREPEATER";
char pass[] = "dA8crKmCGcqu!!%";
int value = 0;
int pin = 15;
int buzzer = 14;
Servo myServo;
WidgetTerminal terminal(V2);
BlynkTimer timer;

void setup()
{
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
    myServo.attach(pin);
    myServo.write(100);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  terminal.clear();
  timer.setInterval(1000L, tempEvent);
}

BLYNK_WRITE(V0){
  
   int pinData = param.asInt();
   value = pinData;
   Serial.println(pinData);
   serve();
   
}

//BLYNK_READ(temperature){
 // Blynk.virtualWrite(temperature, millis(), 1000);
//}



BLYNK_WRITE(V2){
String value = param.asStr();
terminal.clear();
int op = 0;
   
     terminal.println("==========================");
     terminal.println("ASHLEY CARDONA");
     terminal.println("COMEDERO INTELIGENTE");
     terminal.println("Escoge una opción: ");
     terminal.println("(1) Servir 1 porcion");
     terminal.println("(2) Servir 2 porciones");
     terminal.println("(3) Girar motor a 0°");
     terminal.println("(4) Girar motor a 90°");
     terminal.println("(5) Girar motor a 180°");
      terminal.println("==========================");
  terminal.flush();
  op = value.toInt();
    switch(op){
      case 1: 
         feed(1);
         break;
      case 2 : 
           feed(2);
          break;
      case 3: 
           moveDegrees(0);
           break;
      case 4: 
            moveDegrees(90);
            break;
      case 5: 
             moveDegrees(180);
             break;

            
    }
}

void feed(int value){
  for(int i=0; i<value; i++){
     serve();
  }
}

void moveDegrees(int value){
     myServo.write(value);
}


void tempEvent(){
  int value= analogRead(A0);
  float milivolts = (value/1024.0)*3300;
  float celsius = milivolts/10;
  Blynk.virtualWrite(V6, celsius);
}
     

void serve(){
  digitalWrite(buzzer, HIGH);
  myServo.write(0);
   delay(300);
   myServo.write(100);
   digitalWrite(buzzer, LOW);
}
void loop()
{
  
  Blynk.run();
  timer.run();
  
}

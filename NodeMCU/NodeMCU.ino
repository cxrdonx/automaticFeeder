
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLQvFw3QQx"
#define BLYNK_DEVICE_NAME "comedero"
#define BLYNK_AUTH_TOKEN "1pOkgTxt2yT3kz8p0BjCHcRdeLbdFhbA"
#include<Servo.h>
#include <iostream>
#include <string>
using namespace std;
#define activate V0

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char ssid[] = "ECDREPEATER";
char pass[] = "dA8crKmCGcqu!!%";
int value = 0;
int pin = 5;
int buzzer = 14;
String pet = "";
Servo myServo;
WidgetTerminal terminal(V2);

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
    myServo.attach(pin);
    myServo.write(0);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  terminal.clear();
}

BLYNK_WRITE(V0){
  
   int pinData = param.asInt();
   value = pinData;
   Serial.println(pinData);
   serve();
   
}

BLYNK_WRITE(V2){
String value = param.asStr();
terminal.clear();
int op = 0;
   
     terminal.println("==========================");
     terminal.println("nombre:" + pet);
     terminal.println("COMEDERO INTELIGENTE");
     terminal.println("Escoge una opción: ");
     terminal.println("(1) Cambiar nombre de mascota");
     terminal.println("(2) Programar dispensador automatico");
     terminal.println("(3) Cual es la temperatura actual?");
     terminal.println("(4) salir");
      terminal.println("==========================");
  terminal.flush();
  op = value.toInt();
    switch(op){
      case 1: 
         terminal.clear();
         terminal.println("(0) Regresar");
         terminal.println("Ingrese el nombre de su mascota:");
         terminal.flush();
          pet = param.asStr();
         break;
    }
}
     
 //  if(String("hola") == param.asStr()){
  //  terminal.println("hola mundo");
 //  }
  // terminal.flush();

void serve(){
  digitalWrite(buzzer, HIGH);
  myServo.write(150);
   delay(300);
   myServo.write(0);
   digitalWrite(buzzer, LOW);
}
void loop()
{
  Blynk.run();
}

#include <Arduino.h>

#define BUTTON_PIN D1
#define LED_PIN D2

void setup(){
  Serial.begin(9600);
  pinMode(BUTTON_PIN,INPUT);
  pinMode(LED_PIN,OUTPUT);
}

void loop(){
  int value = digitalRead(BUTTON_PIN);
  Serial.print("Button State : ");
  Serial.println(value);
  digitalWrite(LED_PIN,!value);
  delay(100);
}
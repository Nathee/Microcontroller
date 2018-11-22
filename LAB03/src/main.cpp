#include <Arduino.h>

const byte INPUT_PIN = D1;
const byte OUTPUT_PIN = D2;
bool state = false;

void setup(){
  Serial.begin(9600);
  pinMode(INPUT_PIN,INPUT);
  pinMode(OUTPUT_PIN,OUTPUT);
  digitalWrite(OUTPUT_PIN,state);
}

void loop(){
  while(digitalRead(INPUT_PIN)==HIGH){
    delay(10);
  Serial.print("HIGH Button State : ");
  Serial.println(state);
  }
  
  while(digitalRead(INPUT_PIN)==LOW){
    delay(10);
  Serial.print("LOW Button State : ");
  Serial.println(state);
    state = !state;
    digitalWrite(OUTPUT_PIN,state);
  }  
}
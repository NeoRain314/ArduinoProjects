#include <IRremote.h>
#include <IRremoteInt.h>
#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#include <Servo.h>
#define Speed_PIN 10
#define DCIN_PIN 11
#define DCOUT_PIN 12

void setup() {
  // put your setup code here, to run once:
  pinMode(DCIN_PIN, OUTPUT);
  pinMode(DCOUT_PIN, OUTPUT);
  pinMode(Speed_PIN, OUTPUT);  
  
}

void loop() {
  // put your main code here, to run repeatedly:
    analogWrite(Speed_PIN,124);
    digitalWrite(DCIN_PIN, LOW);
    digitalWrite(DCOUT_PIN, HIGH);
delay(2000);
  analogWrite(Speed_PIN,255);
    /*digitalWrite(DCIN_PIN, HIGH);
    digitalWrite(DCOUT_PIN, LOW);*/
    delay(2000);
    
}

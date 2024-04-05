#include <Servo.h>

Servo servo1;

int pos = 0;
int x=0;
int analogX=A0;
int analogY=A1;
int buttonPin=8;

int offsetX=0;
int offsetY=0;
int valX=0;
int valY=0;
int valButton=0;

void setup() {
  // put your setup code here, to run once:
servo1.attach(9);
Serial.begin(9600);
pinMode(buttonPin, INPUT_PULLUP);
offsetX=analogRead(analogX)-512;
offsetY=analogRead(analogY)-512;
}

void loop() {
  // put your main code here, to run repeatedly:

valButton=digitalRead(buttonPin);
//Serial.println(valButton);
valX=analogRead(analogX)-offsetX;
Serial.println(valX);
delay(100); //simplest way of filtering noise of stick for motion
pos=map(valX, 0, 1023, 0, 180);;
Serial.println(pos);
servo1.write(pos);
//valY=analogRead(analogY);
//Serial.println(valY);
}

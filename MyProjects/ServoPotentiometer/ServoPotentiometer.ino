#include <Servo.h>

Servo myservo;
int val = 0;

void setup(){
  myservo.attach(9);
  Serial.begin(9600);
}

void loop(){
  val = analogRead(5);
  val = map(val, 0, 1023, 180, 0);
  
  Serial.println(val);
  myservo.write(val);
  delay(100);
}

#include <Servo.h>
#define TRIGGER1 5
#define ECHO1 4
#define TRIGGER2 9
#define ECHO2 10
Servo Lenkung;
long dauer1 = 0;
long entfernung1 = 0;
long dauer2 = 0;
long entfernung2 = 0;
long entfernung1_2 = 0;
long dauer1_2 = 0;
int carDirection = 0;
#define DCIN 11
#define DCOUT 12

  /*
  0 -> vorwärts
  1 -> links
  2 -> rechts
  3 -> stehenbleiben
  4 -> rückwärts
  */

void setup(){
  Serial.begin (9600);
  pinMode(TRIGGER1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIGGER2, OUTPUT);
  pinMode(ECHO2, INPUT);
  Lenkung.attach(6);
}

void loop(){
  carDirection = 1;
  drive();
  delay(1000);

  carDirection = 2;
  drive();
  delay(1000);
  
/*
  usSensor_1(); //misst auf US1
  usSensor_2(); //misst auf US2
  delay(500);
  usSensor_12(); //misst nochmal auf US1 und merkt sich zweiten wert
  
  delay(1000);
  
  if (entfernung1 < entfernung1_2) {
    carDirection = 0;
    //vorwärts
  }
  if (entfernung1 > entfernung2) {
    carDirection = 1;
    // links fahren
  }
  if (entfernung1 < entfernung2) {
    carDirection = 2;
    //rechts fahren
  }
  if (entfernung1 > entfernung1_2){
    carDirection = 4;
    if (entfernung1 <5) {
      carDirection = 3;
    //stehenbleiben
    }
  } //rückwärts
*/
  
}

void usSensor_1(){
  digitalWrite(TRIGGER1, LOW); //US1
  delay(5);
  digitalWrite(TRIGGER1, HIGH);
  delay(10);
  digitalWrite(TRIGGER1, LOW);
  dauer1 = pulseIn(ECHO1, HIGH);
  entfernung1 = (dauer1 / 2) * 0.03432;

  Serial.print(entfernung1);
  Serial.println(" cm US1 ");  
}

void usSensor_2(){
  digitalWrite(TRIGGER2, LOW); //US2
  delay(5);
  digitalWrite(TRIGGER2, HIGH);
  delay(10);
  digitalWrite(TRIGGER2, LOW);
  dauer2 = pulseIn(ECHO2, HIGH);
  entfernung2 = (dauer2 / 2) * 0.03432;
  
  Serial.print(entfernung2);
  Serial.println(" cm US2 ");
}

void usSensor_12(){
  digitalWrite(TRIGGER1, LOW); //US1.2 Gleiche US sensor aber nächte Zeitpunkt
  delay(5);
  digitalWrite(TRIGGER1, HIGH);
  delay(10);
  digitalWrite(TRIGGER1, LOW);
  dauer1_2 = pulseIn(ECHO1, HIGH);
  entfernung1_2 = (dauer1_2 / 2) * 0.03432;

  Serial.print(entfernung1_2);
  Serial.println(" cm US1.2 ");
}


void drive() {
  if (carDirection == 1) { //fahr  links
    delay(1000);
    Lenkung.write(90);
    Serial.println(" links ");
  }
  if (carDirection == 2) { //fahr nach rechts
    delay(1000);
    Lenkung.write(30);
    Serial.println(" rechts ");
  }
  if (carDirection == 0) { //vorwärts
    digitalWrite(DCIN, LOW);
    digitalWrite(DCOUT, HIGH);
    Lenkung.write(90);
    Serial.println(" vorwärts fahren ");
  }
  if (carDirection == 3) { //stehenbleieben
    digitalWrite(DCIN, LOW);
    digitalWrite(DCOUT, LOW);
    Serial.println(" stehenbleieben");
  }
   if (carDirection == 4) { //rückwärts
    digitalWrite(DCIN, HIGH);
    digitalWrite(DCOUT, LOW);
    Serial.println("rückwärts fahren");
  }
}

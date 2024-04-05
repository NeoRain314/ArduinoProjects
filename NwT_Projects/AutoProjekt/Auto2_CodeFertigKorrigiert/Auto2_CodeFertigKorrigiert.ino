#include <Servo.h>

#include <IRremote.h>

#include <Servo.h>

// Servo
#define SERVO_PIN 10
Servo Lenkung;

//US Sensoren
int dauer1 = 0;
int entfernung1 = 0;
int dauer2 = 0;
int entfernung2 = 0;
#define TRIGGER_1 5
#define ECHO_1 6
#define TRIGGER_2 9
#define ECHO_2 8

//DC Motor
#define DC_PIN1 11
#define DC_PIN2 12
#define SPEED_PIN 3

int carDirection = 0;
int mitte = 95;
int entfernung1_old = 0;
int entfernung2_old = 0;
int entfernungsdifferenz = 0;


void setup() {
  Serial.begin(9600);

  //Servo
  Lenkung.attach(SERVO_PIN);

  //US Sensoren
  pinMode(TRIGGER_1, OUTPUT);
  pinMode(ECHO_1, INPUT);
  pinMode(TRIGGER_2, OUTPUT);
  pinMode(ECHO_2, INPUT);
  digitalWrite(SPEED_PIN, 125);

  Lenkung.write(mitte);

}

void loop() {
  usSensor_1();
  usSensor_2();
  Serial.print(entfernung1);
  Serial.println(" cm US1 ");
  Serial.print(entfernung2);
  Serial.println(" cm US2 ");
  entfernungsdifferenz = entfernung2 - entfernung1;
  delay(500);




  if (-5 < entfernungsdifferenz || entfernungsdifferenz < 5) {
    Lenkung.write(mitte);
    Serial.println("gerade");
  }

  if (entfernungsdifferenz > 5 || entfernungsdifferenz < -5) {
    if (entfernung1 < entfernung2) {
      delay(1000);
      Lenkung.write(mitte - 20);
      Serial.println("rechts");
      //rechts fahren
    }

    if (entfernung1 > entfernung2) {
      delay(1000);
      Lenkung.write(mitte + 20);
      Serial.println("links");
      //links fahren
    }
  }

  if (entfernung1_old < entfernung1 || entfernung2_old < entfernung2) {
    carDirection = 1;
    //vorwärts fahren
  }
  if (entfernung1_old > entfernung1 || entfernung2_old > entfernung2) {
    carDirection = 0;
    //stehenbleiben
  }


  drive();

  delay(1000);
}

void usSensor_1() {  //US1
  digitalWrite(TRIGGER_1, LOW);
  delay(5);
  digitalWrite(TRIGGER_1, HIGH);
  delay(10);
  digitalWrite(TRIGGER_1, LOW);
  dauer1 = pulseIn(ECHO_1, HIGH);
  entfernung1_old = entfernung1;
  entfernung1 = (dauer1 / 2) * 0.03432;
}

void usSensor_2() {  //US2
  digitalWrite(TRIGGER_2, LOW);
  delay(5);
  digitalWrite(TRIGGER_2, HIGH);
  delay(10);
  digitalWrite(TRIGGER_2, LOW);
  dauer2 = pulseIn(ECHO_2, HIGH);
  entfernung2_old = entfernung2;
  entfernung2 = (dauer2 / 2) * 0.03432;
}




void drive() {
  if (carDirection == 0) {  //stehenbleiben
    digitalWrite(DC_PIN1, LOW);
    digitalWrite(DC_PIN2, LOW);
    Serial.println("stehenbleiben");
  }

  if (carDirection == 1) {  //vorwärts
    digitalWrite(DC_PIN1, HIGH);
    digitalWrite(DC_PIN2, LOW);
    Serial.println("vorwaerts");
  }
}

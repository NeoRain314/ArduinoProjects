#include <Servo.h>

// Servo
#define SERVO_PIN 6
Servo Lenkung;

//US Sensoren
int dauer1 = 0;
int entfernung1 = 0;
int dauer2 = 0;
int entfernung2 = 0;
int dauer1_2 = 0;
int entfernung1_2 = 0;
#define TRIGGER_1 5
#define ECHO_1 4
#define TRIGGER_2 9
#define ECHO_2 10

//DC Motor
#define DC_PIN1 11
#define DC_PIN2 12

int carDirection = 0;
  /*
    0 -> Stehenbleiben
    1 -> vorwärts
    2 -> rückwärts
    3 -> rechts
    4 -> links
  */

void setup() {
  Serial.begin(9600);

  //Servo
  Lenkung.attach(SERVO_PIN);

  //US Sensoren
  pinMode(TRIGGER_1, OUTPUT);
  pinMode(ECHO_1, INPUT);
  pinMode(TRIGGER_2, OUTPUT);
  pinMode(ECHO_2, INPUT);
}

void loop() {
  usSensor_1();
  Serial.print(entfernung1);
  Serial.println(" cm US1 ");

  delay(500);

  usSensor_12();
  Serial.print(entfernung1_2);
  Serial.println(" cm US1 _2 ");
  

  /*if(entfernung1 < entfernung1_2){
    carDirection = 1;     
    //anfangen geradeaus fahren
  }

  if(entfernung1 > entfernung1_2){
    carDirection = 0;
    //anhalten
  }

  drive();

  delay(1000);*/ 
}

void usSensor_1(){ //US1
  digitalWrite(TRIGGER_1, LOW); 
  delay(5);
  digitalWrite(TRIGGER_1, HIGH);
  delay(10);
  digitalWrite(TRIGGER_1, LOW);
  dauer1 = pulseIn(ECHO_1, HIGH);
  entfernung1 = (dauer1 / 2) * 0.03432;

  /*Serial.print(entfernung1);
  Serial.println(" cm US1 ");  */
}

void usSensor_2(){ //US2
  digitalWrite(TRIGGER_2, LOW); 
  delay(5);
  digitalWrite(TRIGGER_2, HIGH);
  delay(10);
  digitalWrite(TRIGGER_2, LOW);
  dauer2 = pulseIn(ECHO_2, HIGH);
  entfernung2 = (dauer2 / 2) * 0.03432;
  
  /*Serial.print(entfernung2);
  Serial.println(" cm US2 ");*/
}

void usSensor_12(){
  digitalWrite(TRIGGER_1, LOW); 
  delay(5);
  digitalWrite(TRIGGER_1, HIGH);
  delay(10);
  digitalWrite(TRIGGER_1, LOW);
  dauer1_2 = pulseIn(ECHO_1, HIGH);
  entfernung1_2 = (dauer1 / 2) * 0.03432;

  /*Serial.print(entfernung1_2);
  Serial.println(" cm US1 _2 ");  */
}

void drive(){
  if(carDirection == 0){ //stehenbleiben
    digitalWrite(DC_PIN1, LOW);
    digitalWrite(DC_PIN2, LOW);
    Serial.println("stehenbleiben");
  }

  if(carDirection == 1){ //vorwärts
    digitalWrite(DC_PIN1, HIGH);
    digitalWrite(DC_PIN2, LOW);
    Serial.println("vorwaerts");
  }

  if(carDirection == 2){ //rückwärts
    digitalWrite(DC_PIN1, LOW);
    digitalWrite(DC_PIN2, HIGH);
    Serial.println("rueckwaerts");
  }

  if(carDirection == 3){ //rechts
    Lenkung.write(0);
    Serial.println("rechts");
  }

  if(carDirection == 4){ //links
    Lenkung.write(180);
    Serial.println("links");
  }
}

#define TRIGGER1_PIN
#define ECHO1_PIN
#define TRIGGER2_PIN
#define ECHO2_PIN

long dauer1 = 0;
long entfernung1 = 0;
long dauer2 = 0;
long entfernung2 = 0;

int direktion = 0; // 0 = stehenbleiben, 1 = forwärts,

void setup(){
  Serial.begin(9600);
  pinMode(TRIGGER1_PIN, OUTPUT);
  pinMode(ECHO1_PIN, INPUT);
}

void loop(){
  usSensor1();
  usSensor2();

  drive();
  delay(200);
}

void drive(){

}

void usSensor1(){
  digitalWrite(TRIGGER1_PIN, LOW);
  delay(5);
  digitalWrite(TRIGGER1_PIN, HIGH);
  delay(10);
  digitalWrite(TRIGGER1_PIN, LOW);
  dauer1 = pulseIn(ECHO1_PIN, HIGH);
  entfernung1 = (dauer1 / 2) * 0.03432;

  if (entfernung1 >= 500 || entfernung1 <= 0){
    Serial.println("Kein Messwert");
    entfernung1 = 100;
  }
  else{
    Serial.print(entfernung1);
    Serial.println(" cm US1");
    delay(100);
  }
}

void usSensor2(){
  digitalWrite(TRIGGER2_PIN, LOW);
  delay(5);
  digitalWrite(TRIGGER2_PIN, HIGH);
  delay(10);
  digitalWrite(TRIGGER2_PIN  , LOW);
  dauer2 = pulseIn(ECHO2_PIN, HIGH);
  entfernung2 = (dauer2 / 2) * 0.03432;

  if (entfernung2 >= 500 || entfernung2 <= 0){
    Serial.println("Kein Messwert");
    entfernung2 = 100;
  }
  else{
    Serial.print(entfernung2);
    Serial.println(" cm US2");
    delay(100);
  }
}


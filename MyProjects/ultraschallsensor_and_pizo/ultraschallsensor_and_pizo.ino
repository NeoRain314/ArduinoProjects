int trigger = 7;
int echo = 6;
long dauer = 0;
long entfernung = 0;
int buzzer = 5;

void setup(){
  Serial.begin (9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);

  for(int i=8; i<13; i++){
    pinMode(i, OUTPUT);
  }
}

void loop(){
  clearLED();
  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);
  dauer = pulseIn(echo, HIGH);
  entfernung = (dauer / 2) * 0.03432;
  if (entfernung >= 500 || entfernung <= 0){
    Serial.println("Kein Messwert");
    entfernung = 100;
  }
  else{
    Serial.print(entfernung);
    Serial.println(" cm");
    tone(buzzer, 440);
    leds();
    delay(100);
    noTone(buzzer);
  }
  delay(entfernung*8);
}


void leds(){
  int led = 8;

  if(entfernung < 10){
    led = 8;
  }else if(entfernung < 20){
    led = 9;
  }else if(entfernung < 40){
    led = 10;
  }else if(entfernung < 60){
    led = 11;
  }else if(entfernung < 80){
    led = 12;
  }else if(entfernung < 100){
    led = 13;
  }else{
    led = 14;
  }
  
  clearLED();
  for(int i=led; i<13; i++){
      digitalWrite(i, HIGH);
  }
}

void clearLED(){
  for(int i=8; i<13; i++){
      digitalWrite(i, LOW);
  }
}


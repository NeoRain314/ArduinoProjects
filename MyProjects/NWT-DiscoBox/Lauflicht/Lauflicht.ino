int taster;
void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT); // OUTPUT für LED1
  pinMode(5,OUTPUT); // OUTPUT für LED2
  pinMode(6,OUTPUT); // OUTPUT für LED3
  pinMode(1, INPUT_PULLUP); // fuer den Taster

}

void loop() {
  // put your main code here, to run repeatedly:
  taster=digitalRead(4);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    delay(100);
    digitalWrite(5,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(6,LOW);
    delay(100);
    digitalWrite(6,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    delay(100);

  if(taster==0){
    
  }  

}

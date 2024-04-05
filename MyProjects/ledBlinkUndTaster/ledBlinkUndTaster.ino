
int ledPin = 5;
int buttonApin = 8;
int buttonBpin = 9;
int pause = 60;
int START_COUNTER = 120;
int counter = START_COUNTER;
int buttonPressed_B = 0;
int buttonPressed_A = 0;

byte leds = 0;

void blinkLED(){
  digitalWrite(ledPin, HIGH);
  delay(pause);
  digitalWrite(ledPin, LOW);
  delay(pause);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
  digitalWrite(ledPin, HIGH);
}

void loop() {
  delay(1000/60);

  int buttonB = digitalRead(buttonBpin);
  int buttonA = digitalRead(buttonApin);

  counter -= 1;
  if(counter == 0) {
    digitalWrite(ledPin, HIGH);
    counter = START_COUNTER;
  }
  if(counter == START_COUNTER/2){
    digitalWrite(ledPin, LOW);
  }


  if(buttonB == HIGH) {
    buttonPressed_B = 0;
    //digitalWrite(ledPin, LOW);
  }
  if(buttonB == LOW) {
    if(buttonPressed_B == 0) {
      buttonPressed_B = 1;
      digitalWrite(ledPin, HIGH);
      START_COUNTER = START_COUNTER / 2;
      counter = START_COUNTER;
    } 
  }

  if(buttonA == HIGH) {
    buttonPressed_A = 0;
    //digitalWrite(ledPin, LOW);
  }
  if(buttonA == LOW) {
    if(buttonPressed_A == 0) {
      buttonPressed_A = 1;
      digitalWrite(ledPin, HIGH);
      START_COUNTER = START_COUNTER * 2;
      counter = START_COUNTER;
    } 
  }
}

/*
START_COUNTER = START_COUNTER * 2;
    counter = START_COUNTER;
    digitalWrite(ledPin, HIGH);
*/
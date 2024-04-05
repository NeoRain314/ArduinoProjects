
#define PAUSE 250

void pinOnOff(int pinNr, int pause) {
  digitalWrite(pinNr, HIGH);
  delay(pause);           
  digitalWrite(pinNr, LOW); 
}

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  pinOnOff(3, PAUSE);
  pinOnOff(5, PAUSE);
  pinOnOff(7, PAUSE);
}
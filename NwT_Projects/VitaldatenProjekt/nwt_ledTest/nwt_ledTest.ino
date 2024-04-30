const int arraySize = 5;  
int numOrder[arraySize];
int taster = 13;

volatile int stat = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  for(int i = 1; i<10; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(13, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(13), pressed, FALLING); //!!! only some pins work with interrupt
}


void loop() {}

void pressed(){
  x();
  //addElementToArray(random(1,10));
}

void x(){
  Serial.println(stat);
  if(stat == 1){
      /*for(int i = 1; i<10; i++){
        digitalWrite(i, LOW);
      }
      for (int i = 0; i < arraySize; i++) {
        delay(500);
        digitalWrite(numOrder[i], HIGH);
        delay(200);
        digitalWrite(numOrder[i], LOW);
        if (numOrder[i] == 0) break; // Element hinzugefügt, Schleife verlassen
      }*/
      delay(1000);
      Serial.println(stat);
      stat = 0;
    }
}

void addElementToArray(int value) {
  // Finde die erste freie Position im Array
  for (int i = 0; i < arraySize; i++) {
    if (numOrder[i] == 0) {
      numOrder[i] = value;
      break; // Element hinzugefügt, Schleife verlassen
    }
  }
}

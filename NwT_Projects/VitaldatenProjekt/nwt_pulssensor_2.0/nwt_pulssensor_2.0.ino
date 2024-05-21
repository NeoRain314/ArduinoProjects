int SensorPin = A3;
int LED = 13; 


int Sensorwert;
int Grenzwert = 800;

int stat = 0;
unsigned long startTime = 0;
int puls = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Sensorwert = analogRead(SensorPin);
  Serial.print("Wert:");
  Serial.print(Sensorwert);
  Serial.print(",A:200");
  Serial.println(",B:900");


  if(millis() < startTime + 15000){
    if (Sensorwert > Grenzwert && stat == 0) {
      digitalWrite(LED, HIGH);
      stat = 1;
      puls++;
      Serial.println(puls);
    } else if(Sensorwert < Grenzwert && stat == 1){
      digitalWrite(LED, LOW);
      stat = 0;
    }
  }else{
    puls = puls*4;
    Serial.print("Puls: ");
    Serial.println(puls);
    puls = 0;
    startTime = millis();
  }

  delay(10);  // Kurze Pause im Code, damit die Messwerte besser zu erkennen sind.
}
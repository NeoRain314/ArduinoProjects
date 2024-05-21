
//pulsesensor
int SensorPin = A10;
int LED = 13; 
int Grenzwert = 800;
int stat = 0;
unsigned long startTime = 0;
int puls = 0;

//tempsensor
int sensor = A0;
float temperatur;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  tempsensor();
  pulsesensor();
}

void tempsensor(){
  int messwert;
  messwert = analogRead(sensor);
  messwert = analogRead(sensor);
  temperatur = map(messwert, 29, 79, 16, 40);
  /*Serial.print(temperatur);
  Serial.println(" C°");*/
}

void pulsesensor(){
  if(millis() < startTime + 15000){
    int Sensorwert = analogRead(SensorPin);
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
}
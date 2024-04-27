int SensorPin = A3;  // Signalleitung an Analoa A0
int LED = 13;        // LED an Port 13 wird verwendet


int Sensorwert;       // Variable für den Sensworwert
int Grenzwert = 510;  // Grenzwert, ab dem die LED an Pin13 später leuchten soll

void setup() {
  pinMode(LED, OUTPUT);  // Pin 13 ist ein Ausgang, damit die LED mit Spannung versorgt wird
  Serial.begin(9600);    // Serielle Verbindung starten, damit Daten am Seriellen Monitor angezeigt werden können
}

void loop() {
  Sensorwert = analogRead(SensorPin);  // Sensorwert vom Sensor auslesen und unter der Variablen "Sensor" abspeichern
  Serial.print("Wert:");
  Serial.print(Sensorwert);          // Sensorwert über die Serielle Schnittstelle an den PC senden.
  Serial.print(",A:500");
  Serial.println(",B:600");

  if (Sensorwert > Grenzwert)  // Hier wird eine Verarbeitung gestartet. Wenn der Sensorwert über dem Grenzwert ist...
  {
    digitalWrite(LED, HIGH);  // ...dann soll die LED leuchten
  } else                      // Ansonsten...
  {
    digitalWrite(LED, LOW);  //  ...ist die LED aus
  }

  delay(10);  // Kurze Pause im Code, damit die Messwerte besser zu erkennen sind.
}
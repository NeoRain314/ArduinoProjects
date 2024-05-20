int sensor = A0;
int messwert;
float temperatur;

void setup() {
  Serial.begin(9600);
}

void loop() {
  messwert = analogRead(sensor);
  temperatur = map(messwert, 29, 79, 16, 40);
  Serial.print(temperatur);
  Serial.println(" C°");
  delay(200);
}


// -- old map -- // map(messwert, 51, 41, 238, 206);

// -- correct map -- // map(messwert, 29, 79, 16, 40);

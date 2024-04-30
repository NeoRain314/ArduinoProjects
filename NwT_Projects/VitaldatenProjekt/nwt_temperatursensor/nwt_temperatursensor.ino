int sensor=A0;

int messwert;

float temperatur;

void setup() {
Serial.begin(9600);
}

void loop() {
messwert=analogRead(sensor);

temperatur=map(messwert,51,41,238,206);

Serial.println(temperatur);

delay(200);
}


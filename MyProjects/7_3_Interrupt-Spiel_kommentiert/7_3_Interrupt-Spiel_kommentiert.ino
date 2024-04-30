
// Buchstaben fang Spiel :D

// Sinn des Spiels:Nach einer zufälligen Pause saust ein Buchstabe unterschiedlich schnell durchs Bild.
// es gilt ihn möglichst schnell zu fangen. Die Durchgänge werden einzelnd gestartet sodass mögiche Highscores notiert werden können.
// die Zeiten können nach jedem Durchgang auf dem Seriellen Monitor ausgelesen werden.
// bedienung: Taster 1 - pin 2 1x drücken = start es geht los sobald der Buchstabe auftaucht möglichst schnell fangen.
//            Taster 2 - pin 3 1x drücken = gefangen.
//            Taster 1 - pin 2 1x drücken es geht von vorne los.
#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C Lcd(0x27, 16, 2);
int p;
int y;
int level = 1;                  // Level
int highscore = 0;              // Punktezahl
unsigned long startzeit;        // ohne vorzeichen --> kann höhere zahlen speichern
unsigned long vergangene_zeit;  // ohne vorzeichen --> kann höhere zahlen speichern
int taster1 = 2;                // pin für taster1
int taster2 = 3;                // pin für taster2
volatile int zustand1 = 0;      // wird im Interrupt verwendet
void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(A0));                                         // initialisiert Zufallszahlengenerator an A0
  randomSeed(analogRead(A1));                                         // initialisiert Zufallszahlengenerator an A1
  Serial.begin(9600);                                                 // initialisiert Seriellen Monitor
  Lcd.init();                                                         // initialisiert LCD-Display
  attachInterrupt(digitalPinToInterrupt(taster1), Start, FALLING);    // Interrupt-Funktion "Start" wenn sich Signal von 1 auf 0 ändert für Taster 1
  attachInterrupt(digitalPinToInterrupt(taster2), Gefangen, CHANGE);  // Interrupt-Funktion "Gefangen" wenn sich Signal ändert für Taster 2
  pinMode(taster1, INPUT_PULLUP);                                     // pin taster1 --> input_pullup
  pinMode(taster2, INPUT_PULLUP);                                     // pin taster2 --> input_pullup
  Lcd.backlight();
}

void loop() {
  p = random(1000, 5000);  // p --> zufallszahl zwischen 1000 und 4999
  y = random(25, 50);      // y --> zufallszahl zwischen 15 und 49
  if (zustand1 == 1) {
    Serial.print("Level: ");
    Serial.println(level);
    delay(p);
    startzeit = millis();           // startzeit --> millisekunden seit programmbeginn
    for (int x = 0; x < 17; x++) {  // wiederhohlt 16 mal
      Lcd.setCursor(0, 0);
      Lcd.print("Highscore: ");  // Schreibt an 0|0 "Highscore: " aufs LCD Display
      Lcd.setCursor(13, 0);
      Lcd.print(highscore);
      Lcd.setCursor(x, 1);
      Lcd.print("B");    // schreibt an x|1 "B" " aufs LCD Display
      delay(y / level);  //verzögert y/level
      Lcd.clear();
      if (zustand1 == 0) {          // wenn zustand 0 ist (siehe Interrupt funktionen)
        highscore = highscore + 5;  //highscore+=5; erhöht highscore um 5
        Lcd.clear();
        Serial.print("Zeit vergangen :  ");
        vergangene_zeit = (millis() - startzeit) / 1000;  // berechnet gebrauchte zeit in sekunden [(millisekunden seit begin des programms) - startzeit] /1000
        Serial.println(vergangene_zeit);
        Serial.println("  Sekunden");
        Serial.println("   ");
        delay(2000);
        level++;  // level = level+1 (erhöht level um 1)
        x = 17;   // setzt x auf 17 (schleife wird nicht nochmal ausgeführt)
      }

      if (x >= 15) {                    // wenn x kleiner gleich 15 ist
        highscore = highscore - 2 * 5;  // highscore -= 10 ???
        Serial.println("Depp");
        delay(2000);
        x = 17;
        level--;  //level = level-1 (erniedrigt level um 1)
      }
    }
  }
}
}


void Start() {
  zustand1 = 1;  // setzt zustand auf 1 -> ändert ausführung in loop
}

void Gefangen() {
  zustand1 = 0;  // setzt zustand auf 0 -> ändert ausführung in loop
}

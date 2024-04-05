#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD-Adresse: 0x27, 16 Spalten, 2 Zeilen

void setup() {
  lcd.begin(16, 2); // Initialisierung des LCD-Displays
  lcd.backlight(); // Hintergrundbeleuchtung einschalten
  lcd.setCursor(0, 0); // Cursor auf die erste Position setzen
  lcd.print("Hello, World!"); // Text auf dem Display anzeigen
}

void loop() {
  // Hier kannst du weitere Aktionen oder Aktualisierungen vornehmen
}
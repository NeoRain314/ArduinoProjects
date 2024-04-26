#include <LiquidCrystal_I2C.h>

#include <Key.h>
#include <Keypad.h>

// ------ main -----------------------------------------------
int mode = 0; //0 -> Konzentrationsspiel; 1 -> Puls 

// ------ LCD Display ----------------------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ------ temperatursensor -----------------------------------------------
#define TEMP_SENSOR_PIN A0
int temp_value = 0;
int temperatur = 0;

// <-> Setup <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Setup <->  //

void setup() {
  //initializing --------------------------------------------
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();
}


// <-> Loop <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Loop <->  //

void loop() {

}


// <-> functions <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> functions <-> //

// ~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~

void konzentrationsspiel(){
  Serial.println("konzentrationsspiel");
}

void sensor(){
  Serial.println("Puls- und Temperatursensor");
}

// ~~~ all ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ all ~~~~~~~~~~~~~~

void printCharLcd(char text[], int cursorX, int cursorY){
  //Lcd.clear();
  lcd.setCursor(cursorY, cursorX);
  lcd.print(text);
}

void printNumLcd(int num, int cursorX, int cursorY){
  //Lcd.clear();
  lcd.setCursor(cursorY, cursorX);
  lcd.print(num);
}

// ~~~ Konzentrationsspiel ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Konzentrationsspiel ~~~


// ~~~ Pulssensor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Pulssensor ~~~~~~~~~~~~~~~


// ~~~ Temperatursensor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Temperatursensor ~~~~~~~~~~~~~~~

void temperaturMessung(){
  temp_value = analogRead(TEMP_SENSOR_PIN);
  temperatur = map(temp_value,51,41,238,206);
  Serial.println(temperatur);
}

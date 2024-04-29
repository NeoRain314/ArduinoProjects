#include <LiquidCrystal_I2C.h>

#include <Key.h>
#include <Keypad.h>

// ------ main ----------------------------------------------------
#define TASTER_PIN 18
int mode = 0; //0 -> Konzentrationsspiel; 1 -> Puls & Temp
volatile int taster_stat = 0;

// ------ LCD Display ----------------------------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ------ temperatursensor -----------------------------------------
#define TEMP_SENSOR_PIN A0
int temp_value = 0;
int temperatur = 0;

// ------ pulssensor -----------------------------------------------
#define PULS_SENSOR_PIN A1
int puls_value = 0;

// <-> Setup <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Setup <->  //

void setup() {
  //initializing --------------------------------------------
  Serial.begin(9600);
  //lcd.init();
  //lcd.clear();
  //lcd.backlight();
  attachInterrupt(digitalPinToInterrupt(TASTER_PIN), tasterInterrupt, FALLING);

  //main ----------------------------------------------------
  pinMode(TASTER_PIN, INPUT_PULLUP);  
}


// <-> Loop <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Loop <->  //

void loop() {
  if(taster_stat == 1){
    taster_stat = 0;
    changeMode();
  }
}


// <-> functions <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> functions <-> //


// ~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~

void tasterInterrupt(){
  taster_stat = 1;
}

void changeMode(){
  if(mode < 1){
    mode++;
  }else {
    mode = 0;
  }
  Serial.println(mode);
}

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


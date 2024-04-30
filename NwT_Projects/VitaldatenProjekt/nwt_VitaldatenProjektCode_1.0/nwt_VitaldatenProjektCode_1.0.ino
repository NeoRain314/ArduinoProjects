// <-> Introduction <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Introduction <->  //
/*
  > "<-><->" --> main parts
  > "------" --> initializing sub categories
  > "~~~~~~" --> function sub categories


Todo:
 > ...

Bugs:
 > ...

*/

// <-> Initializing <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Initializing <->  //
#include <LiquidCrystal_I2C.h>

#include <Key.h>
#include <Keypad.h>


// ------ main ----------------------------------------------------
#define TASTER_PIN 18
int mode = 0; //0 -> start; 1 --> Konzentrationsspiel; 2 -> Puls & Temp
volatile int taster_stat = 0;

// ------ LCD Display ----------------------------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ------ temperatursensor -----------------------------------------
#define TEMP_SENSOR_PIN A0
int temp_value = 0;
float temperatur = 0;

// ------ pulssensor -----------------------------------------------
#define PULS_SENSOR_PIN A3
int puls_value = 0;
int puls = 0;


// ------ konzentrationsspiel -----------------------------------------------
bool gamestart = false; //


// <-> Setup <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Setup <->  //

void setup() {
  //initializing --------------------------------------------
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  attachInterrupt(digitalPinToInterrupt(TASTER_PIN), tasterInterrupt, FALLING);

  //main ----------------------------------------------------
  pinMode(TASTER_PIN, INPUT_PULLUP);  


  // start screen
  startMode();
}


// <-> Loop <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Loop <->  //

void loop() {
  
  if(taster_stat == 1){
    taster_stat = 0;
    changeMode();
  }

  if(mode == 1){ //temp- & pulssensor
    //sensors();
  }else if(mode == 2){ //konzentrationsspiel
    if(gamestart == true){
      //konzentrationsspiel();
    }
  }
}


// <-> functions <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> functions <-> //


// ~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~

void tasterInterrupt(){
  taster_stat = 1;
}

void changeMode(){
  if(mode < 2){
    mode++;
  }else {
    mode = 1;
  }
  //Serial.println(mode);
  startMode();
}

void startMode(){
  if(mode == 0){ //start screen
    Serial.println(">-------------------- Vitaldaten Projekt NwT Klasse 9 --------------------<");
    lcd.clear();
    printCharLcd("Vitaldatenprojekt", 0, 0);
    printCharLcd("NwT Klasse 9", 1, 0);
  }else if(mode == 1){ //temp- & pulssensor
    Serial.println("Vitaldatenmessung");
    lcd.clear();
    printCharLcd("Vitaldaten", 0, 0);
    printCharLcd("Messung", 1, 0);

    delay(2000);
  }else if(mode == 2){ //konzentrationsspiel
    Serial.println("Konzentrationsspiel");
    lcd.clear();
    printCharLcd("Konzentration", 0, 0);
    printCharLcd("Spiel", 1, 0);

    gamestart = true;
  }
}

void sensors(){
  tempSensor();
  pulsSensor();

  lcd.clear();
  printCharLcd("Temperatur:", 0, 0);
  printFloatLcd(temperatur, 0, 11);
  printCharLcd("Puls:", 1, 0);
  printNumLcd(puls, 1, 5);
}

void konzentrationsspiel(){
  gamestart = false;
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

void printFloatLcd(float num, int cursorY, int cursorX){
  //Lcd.clear();
  lcd.setCursor(cursorX, cursorY);
  lcd.print(num);
}
// ~~~ Konzentrationsspiel ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Konzentrationsspiel ~~~


// ~~~ Pulssensor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Pulssensor ~~~~~~~~~~~~~~~

void pulsSensor(){
  puls = 0;
}

// ~~~ Temperatursensor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Temperatursensor ~~~~~~~~~~~~~~~

void tempSensor(){
  temp_value = analogRead(TEMP_SENSOR_PIN);
  temp_value /= 10;
  temperatur = map(temp_value, 42, 20, 215, 99); 
  temperatur /= 10;
  
  Serial.println(temperatur);
  delay(500);
}


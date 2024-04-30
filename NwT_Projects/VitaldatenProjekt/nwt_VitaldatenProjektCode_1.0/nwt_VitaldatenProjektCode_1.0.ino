// <-> Introduction <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Introduction <->  //
/*
  > "<-><->" --> main parts
  > "------" --> initializing sub categories
  > "~~~~~~" --> function sub categories


Todo:
 > break(); --> um aus schleife auszubrechen (evt. bei konzentrationsspiel nötig)

Bugs:
 > 

*/

// <-> Initializing <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Initializing <->  //
#include <LiquidCrystal_I2C.h>

#include <Key.h>
#include <Keypad.h>

// ------ Keypad ----------------------------------------
//defines Size of Keypad
const byte COLS = 3; //3 Spalten
const byte ROWS = 4; //4 Zeilen; (schwarz)

char hexaKeys[ROWS][COLS] = { //Die Ziffern/Zeichen
  {'#', '0', '*'},
  {'9', '8', '7'},
  {'6', '5', '4'},
  {'3', '2', '1'}
};

byte colPins[COLS] = { 8, 7, 6 }; //Definition der Pins für die 3 Spalten
byte rowPins[ROWS] = { 5, 4, 3, 2 };//Definition der Pins für die 4 Zeilen

char Taste; //pressed Key
Keypad myKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// ------ LCD Display ----------------------------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);


// ------ main ----------------------------------------------------
#define TASTER_PIN 18
int mode = 0; //0 -> start; 1 --> Konzentrationsspiel; 2 -> Puls & Temp
volatile int taster_stat = 0;

// ------ temperatursensor -----------------------------------------
#define TEMP_SENSOR_PIN A0
int temp_value = 0;
float temperatur = 0;

// ------ pulssensor -----------------------------------------------
#define PULS_SENSOR_PIN A3
int puls_value = 0;
int puls = 0;

//------ konzentrationsspiel ----------------------------------------
int order[30] = {}; //later with for 0 in array
int order_index = 0; //index in order arr
int order_length; //length of order array
int game_round = 0; //current game round
int led_stat = 0; //stat if leds were shown or not
bool gameover = false;

#define CTRL_LED 13
#define BUZZ_PIN 12

#define arr_length(a) (sizeof(a) / sizeof(a[0]))

// ------ Sounds ----------------------------------------
int sound_gameRight[1] = {440};
int sound_gameover[4] = {210, 190, 210, 130};
int sound_gameRoundFinish[1] = { 587};


// ------ konzentrationsspiel -----------------------------------------------
bool gamestart = false; //


// <-> Setup <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Setup <->  //

void setup() {
  //initializing --------------------------------------------
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();
 

  //main ----------------------------------------------------
  pinMode(TASTER_PIN, INPUT_PULLUP);
  Serial.print("taster_stat: ");
  Serial.println(taster_stat);
  attachInterrupt(digitalPinToInterrupt(TASTER_PIN), tasterInterrupt, FALLING);


  // start screen
  startScreen();
  taster_stat = 0; // Interrupt wird aus irgeneinem Grund davor schon aufgerufen, deshalb nochmal auf 0
}


// <-> Loop <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Loop <->  //

void loop() {
  
  if(taster_stat == 1){
    taster_stat = 0;
    changeMode();
  }

  if(mode == 1){ //temp- & pulssensor
    sensors();
  }else if(mode == 2){ //konzentrationsspiel
    if(gamestart == true){
      konzentrationsspiel();
    }
  }
}


// <-> functions <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> functions <-> //


// ~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~
volatile unsigned long alteZeit=0, entprellZeit=500;

void tasterInterrupt(){
  if((millis() - alteZeit) > entprellZeit) { 
    taster_stat = 1;
    //Serial.println("Taser Interrupt");
    alteZeit = millis(); //letzte Schaltzeit merken      
  }
}

void changeMode(){
  mode = mode + 1;
  if(mode > 2) mode = 1;
  //Serial.println(mode);
  startMode();
}

void startMode(){
  if(mode == 1){ //temp- & pulssensor
    Serial.println("Vitaldatenmessung");
    lcd.clear();
    printCharLcd("Vitaldaten", 0, 0);
    printCharLcd("Messung", 1, 0);
    delay(1000);
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

void startScreen(){
  Serial.println(">-------------------- Vitaldaten Projekt NwT Klasse 9 --------------------<");
  lcd.clear();
  printCharLcd("Vitaldatenprojekt", 0, 0);
  printCharLcd("NwT Klasse 9", 1, 0);
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


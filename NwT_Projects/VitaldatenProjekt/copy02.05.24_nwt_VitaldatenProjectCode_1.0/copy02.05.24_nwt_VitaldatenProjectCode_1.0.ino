// <-> Introduction <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Introduction <->  //
/*
  > "<-><->" --> main parts
  > "------" --> initializing sub categories
  > "~~~~~~" --> function sub categories


Todo:
 > 

Bugs:
 > um von laufendem konzentrationsspiel umzuschalten 2 mal klicken nötig (erst gameover...)

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

  //loading screen --------
  printCharLcd("loading...", 0, 0);

  //konzentrationsspiel -------------------------------------
  int seed = analogRead(A0);
  randomSeed(seed);
  Serial.print("Seed: ");
  Serial.println(seed);

  order_length = sizeof(order) / sizeof(order[0]);
  //randomizeOrderArray(); //wird am anfang von konzentrationsspiel gemacht
  
  pinMode(CTRL_LED, OUTPUT);

  for(int i = 22; i<38; i++){
    pinMode(i, OUTPUT); //16 leds (Display)
  }

  //just for testing the leds and make sure everything is working
  /*for(int i = 22; i<38; i++){
    digitalWrite(i, HIGH);
    delay(200);
    digitalWrite(i, LOW);
    delay(200);
  }  */


  // start screen
  startScreen();
  taster_stat = 0; // Interrupt wird aus irgeneinem Grund davor schon aufgerufen, deshalb nochmal auf 0
}


// <-> Loop <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-> Loop <->  //

void loop() {
  
  checkTasterChange();

  if(mode == 1){ //temp- & pulssensor
    sensors();
  }else if(mode == 2){ //konzentrationsspiel
    konzentrationsspiel();
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

void checkTasterChange(){
  if(taster_stat == 1){
    taster_stat = 0;
    changeMode();
  }
}

void changeMode(){
  mode = mode + 1;
  if(mode > 2) mode = 1;
  Serial.println(mode);
  startMode();
}

void startMode(){
  if(mode == 1){ //temp- & pulssensor
    Serial.println("Vitaldatenmessung");
    lcd.clear();
    printCharLcd("Vitaldaten", 0, 0);
    printCharLcd("Messung", 1, 0);  
  }else if(mode == 2){ //konzentrationsspiel
    Serial.println("Konzentrationsspiel");
    lcd.clear();
    printCharLcd("Konzentration", 0, 0);
    printCharLcd("Spiel", 1, 0);
  }
  delay(1000);
}

void startScreen(){
  Serial.println(">-------------------- Vitaldaten Projekt NwT Klasse 9 --------------------<");
  lcd.clear();
  printCharLcd("Vitaldatenprojekt", 0, 0);
  printCharLcd("NwT Klasse 9", 1, 0);
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
  //reset everything
  randomizeOrderArray();
  order_index = 0;
  game_round = 0;
  gameover = false;


  while(gameover == false && mode == 2){
    checkTasterChange(); //check if interrupt
    

    if(order_index == game_round){ //not planned but finished all rounds
      if(game_round == order_length){
        Serial.println("Finished");
        //buggy cuz it is called each frame !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !!     !! W I C H T I G !!
        lcd.clear();
        printCharLcd("ouh you finished", 0, 0);
        printCharLcd("all rounds! :D", 1, 0);
      }else {
        order_index = 0;
        game_round++;  
        led_stat = 0;
        lcd.clear();
        printCharLcd("--- Memorize ---", 0, 0);
        printCharLcd("Runde:", 1, 0);
        printNumLcd(game_round, 1, 7);

        playSound(sound_gameRoundFinish, arr_length(sound_gameRoundFinish));   
      }
      
    } else {
      Taste = myKeypad.getKey();
      controllLed();
      Serial.println(order[order_index]);
      if (Taste == ('0' + order[order_index])) {
        Serial.println("right button");
        order_index++;
        playSound(sound_gameRight, arr_length(sound_gameRight));
      }else if(Taste){ //wrong Key pressed
        gameover = true;
      }

      if(led_stat == 0){
        showLedOrder();
        led_stat = 1;
      }
    }
  }

  //gameover
  Serial.println("Game Over");
  playSound(sound_gameover, arr_length(sound_gameover));
  gameOver();

  mode = 0;
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

void playSound(int sound[], int sound_length){
  for(int i = 0; i<sound_length; i++){
    tone(BUZZ_PIN, sound[i]);
    delay(200);
    noTone(BUZZ_PIN);
  }
}

// ~~~ Konzentrationsspiel ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Konzentrationsspiel ~~~

void showLedOrder(){
  Serial.println("led order");
  delay(500);
  for(int i = 0; i<game_round; i++){
    digitalWrite(order[i] + 21, HIGH);
    delay(500);
    digitalWrite(order[i] + 21, LOW);
    delay(500);
  }
}

void controllLed(){ 
  if(Taste){
    //Serial.println("led");
    digitalWrite(CTRL_LED, HIGH);
  }else{
    digitalWrite(CTRL_LED, LOW);
  }
} 

void pressedLEDglow(int led){
  digitalWrite(led + 21, HIGH);
  delay(300);
  digitalWrite(led + 21, LOW);
}

void gameOver(){
  lcd.clear();
  printCharLcd("- Game  Over -", 0, 1);
  printCharLcd("Runde:", 1, 0);
  
  printNumLcd(game_round, 1, 7);
  printCharLcd(":(", 1, 14);

  /*for(int i = 22; i<38; i++){
    digitalWrite(i, HIGH);
  }*/

  //gameover = false;
}

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

// ~~~ Konzentratiosnspiel ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Temperatursensor ~~~~~~~~~~~~~~~

void randomizeOrderArray(){
  for(int i=0; i<order_length; i++) {
    order[i] = random(1, 10);
  }
}
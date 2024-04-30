#include <LiquidCrystal_I2C.h>

#include <Key.h>
#include <Keypad.h>

//marker !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !! ___ !!     !! W I C H T I G !!

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

// ------ Sounds ----------------------------------------

int sound_gameRight[1] = {440};
int sound_gameover[4] = {210, 190, 210, 130};
int sound_gameRoundFinish[1] = { 587};

// ------ LCD Display ----------------------------------------

LiquidCrystal_I2C lcd(0x27, 16, 2);

//------ konzentrations spiel variablen ----------------------------------------
int order[30] = {}; //later with for 0 in array
int order_index = 0; //index in order arr
int order_length; //length of order array
int game_round = 0; //current game round
int led_stat = 0; //stat if leds were shown or not
bool gameover = false;

#define CTRL_LED 13
#define BUZZ_PIN 12

#define arr_length(a) (sizeof(a) / sizeof(a[0]))


// <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->  //


void setup() {
  //initializing --------------------------------------------
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();

  int seed = analogRead(A0);
  randomSeed(seed);
  Serial.print("Seed: ");
  Serial.println(seed);

  //array ----------------------------------------------------
  order_length = sizeof(order) / sizeof(order[0]);
  for(int i=0; i<order_length; i++) {
    order[i] = random(1, 10);
  }

  pinMode(CTRL_LED, OUTPUT);

  for(int i = 22; i<38; i++){
    pinMode(i, OUTPUT); //16 leds (Display)
  }

  //just for testing the leds and make sure everything is working
  for(int i = 22; i<38; i++){
    digitalWrite(i, HIGH);
    delay(200);
    digitalWrite(i, LOW);
    delay(200);
  }
  
  /*for(int i=0; i<order_length; i++) {
    Serial.println(order[i]);
  }*/
}

// <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->  //

void loop() {
  if(gameover == true){ //gameover
      Serial.println("Game Over");
      playSound(sound_gameover, arr_length(sound_gameover));
      gameOver();
  }else if(order_index == game_round){ //not planned but finished all rounds
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
  };
  
  
}

// <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->  //

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

void playSound(int sound[], int sound_length){
  for(int i = 0; i<sound_length; i++){
    tone(BUZZ_PIN, sound[i]);
    delay(200);
    noTone(BUZZ_PIN);
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

  for(int i = 22; i<38; i++){
    digitalWrite(i, HIGH);
    //write on LCD Display
  }
  gameover = false;
}

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



// <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->  //

/*  --- old code --
  int stat = 0; // 0 -> neue zufallszahl; 1 -> warten bis rand taste gedrückt;2 -> warten bis nächste taste in array gedrückt

  if(stat == 0){
    //save new number in array
    rando = random(1, 10);
    saveInArr(rando, order);
    index = 0;
    stat = 2;
  } else if(stat == 1){
    Serial.print("Zahl: ");
    Serial.println(order[index]);
    Taste = myKeypad.getKey();
    if (Taste) Serial.println(Taste);
    if (Taste == ('0' + order[index])) {
      Serial.println("right button");
      index++;
      //stat = 2;
    }
  } else if(stat == 2){
    //go through array and ask for keypad
    //if (Taste) Serial.println(Taste);
    //Serial.println(order[index]);
    if(order[index]){
      stat = 1;
    } else{
      stat = 0; //neue zufallszahl
    } 
  }



  void saveInArr(int x, int arr[]){
  for(int i=0; i< (sizeof(arr) / sizeof(arr[0])); i++){
    if(arr[i]){ // kann man das so machen? Keine ahnung?
      //... idk what, nothing...?!
    } else{
      arr[i] = x;
      return;
    }
  }
}
  */

/*
if (Taste) { //Wenn eine Taste gedrückt wurde
      Serial.print("Die Taste ");
      Serial.print(Taste);
      Serial.print(" wurde gedrueckt");
      Serial.println(); //Teile uns am Serial Monitor die gedrückte Taste mit
    }
*/






#include <Key.h>
#include <Keypad.h>

//Hier wird die größe des Keypads definiert
const byte COLS = 3; //3 Spalten
const byte ROWS = 4; //4 Zeilen; schwarz

//Die Ziffern/Zeichen:
char hexaKeys[ROWS][COLS] = {
  {'#', '0', '*'},
  {'9', '8', '7'},
  {'6', '5', '4'},
  {'3', '2', '1'}
};



byte colPins[COLS] = { 8, 7, 6 }; //Definition der Pins für die 3 Spalten
byte rowPins[ROWS] = { 5, 4, 3, 2 };//Definition der Pins für die 4 Zeilen

char Taste; //pressedKey entspricht in Zukunft den gedrückten Tasten
Keypad myKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //Das Keypad kann absofort mit myKeypad angesprochen werden


int stat = 0; // 0 -> neue zufallszahl; 1 -> warten bis rand taste gedrückt;2 -> warten bis nächste taste in array gedrückt

//order array
int order[5] = {0, 0, 0, 0, 0};
int order_index = 0; //index in order arr
int order_length;
int game_round = 0;
int rando = 0; //

// <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->  //

void setup() {
  //initializing --------------------
  Serial.begin(9600);

  int seed = analogRead(A0);
  randomSeed(seed);
  Serial.print("Seed: ");
  Serial.println(seed);

  //array --------------------
  order_length = sizeof(order) / sizeof(order[0]);
  for(int i=0; i<order_length; i++) {
    order[i] = random(1, 10);
  }

  /*for(int i=0; i<order_length; i++) {
    Serial.println(order[i]);
  }*/
}

// <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->  //

void loop() {
  //Taste = myKeypad.getKey();
  //Serial.println(Taste);
  if(order_index == game_round){
    if(game_round == order_length){
      Serial.println("Finished");
    }else{
      order_index = 0;
      game_round++;      
    }
    
    
  } else {
    Taste = myKeypad.getKey();
    Serial.println(order[order_index]);
    if (Taste == ('0' + order[order_index])) {
      Serial.println("right button");
      order_index++;
    }
  }
  
}









// <-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><-><->  //

/*  --- old code --
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






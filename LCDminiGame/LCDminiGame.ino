// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int xPos = 0;
bool leftDown = false;
bool rightDown = false;

void setup() {
  pinMode(2, INPUT_PULLUP); //left
  pinMode(3, INPUT_PULLUP); //right

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Move left/right");
}

void loop() {

  if(digitalRead(2)==LOW){  //left
    leftDown = true;
  }
  if (leftDown && digitalRead(2) == HIGH) {
    leftDown = false;
      if(xPos > 0){
        clear(xPos, 1);
        xPos--;
      }
  } 

  if(digitalRead(3)==LOW){  //right
    rightDown = true;
  }
  
  if (rightDown && digitalRead(3) == HIGH) {
    rightDown = false;
      if(xPos < 15){
        clear(xPos, 1);
        xPos++;
      }
  } 
  
  print(xPos, 1, "|");
}


void clear(int x, int y){
  lcd.setCursor(x, y);
  lcd.print(" ");
}

void print(int x,int y, const char* text){
  lcd.setCursor(x, y);
  lcd.print(text);
}

/*-------------------------------------------------------------
    >>> ToDo <<<
  - Display show 0 from countdown




-------------------------------------------------------------*/



#include <LiquidCrystal_I2C.h>

//max millis time:  .046471111111h

#define RED_PIN 7
#define YELLOW_PIN 2
#define GREEN_PIN 3

#define START_BUTTON_PIN 4

#define BUZZER_PIN 13

unsigned long shooting_time = 0; //modus später
unsigned long start_time = 0;
unsigned long preparing_time = 0;
unsigned long old_disp_time = 0; //to remember the old display time to update it everytime it changes

int taster_stat = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  //initializing
  Serial.begin(9600);

  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  pinMode(START_BUTTON_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  
  printCharLcd("Ampel", 5, 0);

  //set variables
  shooting_time = secInMil(10);
  preparing_time = secInMil(3);
}

void loop() {
  if(digitalRead(START_BUTTON_PIN) == 0 && taster_stat == 0){
    taster_stat = 1;
  }
  if(digitalRead(START_BUTTON_PIN) == 1 && taster_stat == 1){
    taster_stat = 0;
    mode();
  }

}

// -------------------------------------------------------------------------------


void mode(){
  //reset
  if(millis() < start_time) Serial.print("!!!! ACHTUNG RESTARTEN - TIME OVERFLOW !!!!"); //TIME OVERFLOW!!!!! (this happens after ca. 1193h, then nothing works bis you restart)
  start_time = millis();
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);

  //prepare time (red)
  while(millis() <= start_time + preparing_time){
    digitalWrite(RED_PIN, HIGH);
    writeTime(preparing_time/1000 - (millis()- start_time) / 1000);
  }
  

  start_time = millis();

  //green time
  while(millis() <= start_time + shooting_time - secInMil(3)){ //yellow time (should be 30 sec in the end) ------------------------------------------------------------------------------------------------- !!!!
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    writeTime(shooting_time/1000 - (millis()- start_time) / 1000);
  }

  //yellow time
  while(millis() <= start_time + shooting_time){
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, HIGH);
    writeTime(shooting_time/1000 - (millis()- start_time) / 1000);
  }

  //red! Finished
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
  lcd.clear();
  printCharLcd("Time up!", 4, 0);
}


void ampel(){
  tone(BUZZER_PIN, 440);
  delay(1000);
  noTone(BUZZER_PIN);
  
  digitalWrite(RED_PIN, HIGH);
  delay(500);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, HIGH);
  delay(500);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  delay(500);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
}


void writeTime(int zeit){
  if(zeit != old_disp_time){
    old_disp_time = zeit;
    lcd.clear();
    printIntLcd(zeit, 0, 0);
    Serial.println(zeit);
  }
}


// ----------------------------- Help Functions ----------------------------------
int secInMil(int sec){
  return sec * 1000;
}

int minInMil(int min){
  return min * 60 * 1000;
}

void printCharLcd(char text[], int cursorX, int cursorY){
  //Lcd.clear();
  lcd.setCursor(cursorX, cursorY);
  lcd.print(text);
}

void printIntLcd(int num, int cursorX, int cursorY){
  //Lcd.clear();
  lcd.setCursor(cursorX, cursorY);
  lcd.print(num);
}

void printFloatLcd(float num, int cursorY, int cursorX){
  //Lcd.clear();
  lcd.setCursor(cursorX, cursorY);
  lcd.print(num);
}




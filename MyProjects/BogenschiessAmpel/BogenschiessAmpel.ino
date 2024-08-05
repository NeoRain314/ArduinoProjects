/*-------------------------------------------------------------
    >>> ToDo <<<
  - Display show 0 from countdown??
  - after abbruch (interrupt) noting works)
  - instead of 0 and 1 AB and CD on display




-------------------------------------------------------------*/


#include <LiquidCrystal_I2C.h>

//max millis time:  .046471111111h

#define RED_PIN 8
#define YELLOW_PIN 9
#define GREEN_PIN 10

#define START_BUTTON_PIN 6

#define BUZZER_PIN 7
#define INTERRUPT_PIN 2

unsigned long shooting_time = 0; //modus später
unsigned long start_time = 0;
unsigned long preparing_time = 0;
unsigned long old_disp_time = 0; //to remember the old display time to update it everytime it changes


bool terminate = false;

int taster_stat = 0;

//mode variables
bool mode_ABCD = false; //true/false
int curr_group = 0; //0 = AB/ 1 = CD


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  //initializing
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), terminateAll, FALLING);

  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  pinMode(START_BUTTON_PIN, INPUT_PULLUP);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  
  printCharLcd("Ampel", 5, 0);

  //set variables
  //shooting_time = secInMil(10);
  preparing_time = secInMil(3);
}

void loop() {
  if(digitalRead(START_BUTTON_PIN) == 0 && taster_stat == 0){
    taster_stat = 1;
  }
  if(digitalRead(START_BUTTON_PIN) == 1 && taster_stat == 1){
    taster_stat = 0;
    setMode(20, true); // ------------------------------------------------------------------------------------------------------------------------------------------- < set mode, later with buttons > ------------- //
    preparing_time = secInMil(10); // see at begin, later everytime 10 sec, just now to make it faster to debug :D
    executeMode();
  }

}

// -------------------------------------------------------------------------------

void setMode(int time, bool ABCD){ //time in minutes; ab mode true or false
  shooting_time = secInMil(time);
  Serial.println(shooting_time);
  mode_ABCD = ABCD;
}

void executeMode(){
  //reset
  if(millis() < start_time) Serial.print("!!!! ACHTUNG RESTARTEN - TIME OVERFLOW !!!!"); //TIME OVERFLOW!!!!! (this happens after ca. 1193h, then nothing works bis you restart)


  shootingCountdown(); //green and yellow time
  
  if(mode_ABCD){
    changeGroup();
    shootingCountdown(); //if ABCD agaiin
  }
  

  //red! Finished
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
  lcd.clear();
  printCharLcd("Time up!", 4, 0);

  if(terminate){  //Abbruch
    for(int i=0; i<6; i++){
      playTone(800, 500);
    }
    terminate = false;
  }else{          //norm. Ende
    playTone(440, 700);
    playTone(440, 700);
    playTone(440, 700);
  }
  
}


void shootingCountdown(){
  //reset
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  start_time = millis();
  

  //prepare time (red)
  int x = 0;
  while(millis() <= start_time + preparing_time){
    
    digitalWrite(RED_PIN, HIGH);
    writeTime(computeCountdown(preparing_time));
    if(x < 2){
      playTone(440, 700);
      x++;
    }
  }


  start_time = millis(); //reset start time again

  //green time
  playTone(440, 700);
  while(millis() <= start_time + shooting_time - secInMil(3)){ //yellow time (should be 30 sec in the end) ------------------------------------------------------------------------------------------------- !!!!
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    writeTime(computeCountdown(shooting_time));
  }

  //yellow time
  while(millis() <= start_time + shooting_time){
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, HIGH);
    writeTime(computeCountdown(shooting_time));
  }
}


void terminateAll(){
  terminate = true;
  shooting_time = 0;
  preparing_time = 0;
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
}

void writeTime(int zeit){       //wite time and (if abcd) group at lcd display
  if(zeit != old_disp_time){
    old_disp_time = zeit;
    lcd.clear();
    printIntLcd(zeit, 0, 0);
    if(curr_group == 0 ) printCharLcd("AB", 0, 1);
    if(curr_group == 1 ) printCharLcd("CD", 0, 1);
    //Serial.println(zeit);
  }
  
}

void changeGroup(){
  if(curr_group == 0){
      curr_group = 1;
    }else{
      curr_group = 0;
  }
  Serial.println(curr_group);

  /*
  if(mode_ABCD){
    if(curr_group == "AB"){
      printCharLcd("AB", 0, 1);
      curr_group = "CD";
    }else{
      printCharLcd("CD", 0, 1);
      curr_group = "AB";
    }
  }
  */
}

// ----------------------------- Help Functions ----------------------------------
int secInMil(int sec){
  return sec * 1000;
}

int minInMil(int min){
  return min * 60 * 1000;
}

int computeCountdown(unsigned long time){ //computes the remaining time of the current countdown
  //Serial.println(20000/1000 - (millis()- start_time) / 1000);
  return time/1000 - (millis()- start_time) / 1000;
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

void playTone(int f, int dur){
  tone(BUZZER_PIN, f);
  delay(dur); //tone duration
  noTone(BUZZER_PIN);
  delay(dur); //pause == tone dur
}




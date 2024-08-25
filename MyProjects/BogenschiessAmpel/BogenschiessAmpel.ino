

/*-------------------------------------------------------------
    >>> ToDo <<<
  - Display show 0 from countdown??
  - after abbruch (interrupt) noting works)


  next todo:
  - fix displayed mode and time & show in menue
  - check if all modi are correct
  - stop (curr to end)



--------------------------------------------------------------- */
#include <IRremote.hpp>

#include <LiquidCrystal_I2C.h>

//max millis time:  .046471111111h

#define RED_PIN 11
#define YELLOW_PIN 12
#define GREEN_PIN 13

#define START_BUTTON_PIN 8
#define MODE_1 4
#define MODE_2 5
#define MODE_3 6
#define MODE_4 7

#define BUZZER_PIN 9
#define INTERRUPT_ABBRUCH_PIN 18
#define INTERRUPT_WEITER_PIN 19

#define RECV_PIN 2

unsigned long shooting_time = 0; //modus später
unsigned long start_time = 0;
unsigned long preparing_time = 0;
unsigned long old_disp_time = 0; //to remember the old display time to update it everytime it changes


bool terminate = false;
bool jump_forward = false;

int taster_stat = 0;

//mode variables
bool mode_ABCD = false; //true/false
int curr_group = 0; //0 = AB/ 1 = CD


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  //initializing
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_ABBRUCH_PIN), terminateAll, FALLING);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_WEITER_PIN), jumpForward, FALLING);
  attachInterrupt(digitalPinToInterrupt(RECV_PIN), irInterrupt, FALLING);

  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  pinMode(INTERRUPT_ABBRUCH_PIN, INPUT_PULLUP);
  pinMode(INTERRUPT_WEITER_PIN, INPUT_PULLUP);
  pinMode(START_BUTTON_PIN, INPUT_PULLUP);
  pinMode(MODE_1, INPUT_PULLUP);
  pinMode(MODE_2, INPUT_PULLUP);
  pinMode(MODE_3, INPUT_PULLUP);
  pinMode(MODE_4, INPUT_PULLUP);

  IrReceiver.begin(RECV_PIN);


  lcd.init();
  lcd.clear();
  lcd.backlight();
  
  printCharLcd("Ampel", 5, 0);

  //set variables
  setMode(4, false); //standart mode; 1 -> 4min, AB
  preparing_time = secInMil(10);
  setMode(20, false); //standard mode
}

void loop() {
  //testIR();

  //buttons to set mode
  if(digitalRead(MODE_1) == 0) setMode(4, false); //1 -> 4min, AB
  if(digitalRead(MODE_2) == 0) setMode(4, true);  //1 -> 4min, ABCD
  if(digitalRead(MODE_3) == 0) setMode(2, false); //1 -> 2min, AB
  if(digitalRead(MODE_4) == 0) setMode(2, true);  //1 -> 2min, ABCD

  //Serial.println(terminate);



  if(millis() % 500 == 0){  //write settings on display
    lcd.clear();
    printCharLcd("Ampel", 5, 0);

    printIntLcd(milInMin(shooting_time), 4, 1);
    printCharLcd("min", 5, 1);

    printCharLcd("|", 6, 1);

    if(mode_ABCD){
      printCharLcd("ABCD", 7, 1);
    }else{
      printCharLcd("AB", 7, 1);
    }
  }


  /*Serial.print("time: ");
  Serial.println(shooting_time);
  Serial.print(", ABCD: ");
  Serial.println(mode_ABCD);*/

  if(digitalRead(START_BUTTON_PIN) == 0 && taster_stat == 0){   //start button
    taster_stat = 1;
  }
  if(digitalRead(START_BUTTON_PIN) == 1 && taster_stat == 1){
    taster_stat = 0;
    terminate = false;
    executeMode();
  }
}

// -------------------------------------------------------------------------------

void testIR(){
  delay(200);
  if (IrReceiver.decode()){
    if (IrReceiver.decodedIRData.address == 0){
      IrReceiver.resume();            // receive the next value
      Serial.println(IrReceiver.decodedIRData.command);
    }
  }

}

void setMode(unsigned long time, bool ABCD){ //time in minutes; ab mode true or false
  shooting_time = minInMil(time);
  //Serial.println(shooting_time);
  mode_ABCD = ABCD;
  curr_group = 0; //everytime you set a mode ab starts
  //Serial.println(shooting_time);
}

void executeMode(){
  //reset
  if(millis() < start_time) Serial.print("!!!! ACHTUNG RESTARTEN - TIME OVERFLOW !!!!"); //TIME OVERFLOW!!!!! (this happens after ca. 1193h, then nothing works bis you restart)


  shootingCountdown(); //green and yellow time
  if(mode_ABCD){
    changeGroup();
    shootingCountdown(); //if ABCD again
  }


  //red! Finished
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
  lcd.clear();

  if(terminate){  //Abbruch
    printCharLcd("Abbruch!", 4, 0);
    for(int i=0; i<6; i++){
      playTone(800, 500);
    }
    terminate = false;
  }else{          //norm. Ende
    printCharLcd("Time up!", 4, 0);
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
  while(!terminate && !jump_forward && (millis() <= start_time + preparing_time)){
    
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
  while(!terminate && !jump_forward && (millis() <= start_time + shooting_time - secInMil(30))){ //yellow time (should be 30 sec in the end) ------------------------------------------------------------------------------------------------- !!!!
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    writeTime(computeCountdown(shooting_time));
  }

  //yellow time
  while(!terminate && !jump_forward && (millis() <= start_time + shooting_time)){
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, HIGH);
    writeTime(computeCountdown(shooting_time));
  }
  
  jump_forward = false;
}

void irInterrupt(){
  
}

void terminateAll(){
  terminate = true;
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
}

void jumpForward(){
  jump_forward = true;
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

    if(mode_ABCD){
      printCharLcd("ABCD", 12, 1);
    }else{
      printCharLcd("AB", 14, 1);
    }
    printIntLcd(milInMin(shooting_time), 12, 0);
    printCharLcd("min", 13, 0);

    printCharLcd("|", 11, 0);
    printCharLcd("|", 11, 1);
  }
  
}

void changeGroup(){
  if(curr_group == 0){
      curr_group = 1;
    }else{
      curr_group = 0;
  }
  //Serial.println(curr_group);

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
unsigned long secInMil(int sec){
  return sec * 1000;
}

unsigned long minInMil(unsigned long min){
  return min * 60 * 1000;
}

unsigned long milInMin(unsigned long mil){
  return mil / 1000 / 60;
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
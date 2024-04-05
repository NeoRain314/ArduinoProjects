#include <Wire.h>

#include <LiquidCrystal_I2C.h>

// >>> defines <<< //
#define HALBE 1000
#define VIERTEL 500
#define ACHTEL 250

#define NO_TONE 0
#define TONE_G 392
#define TONE_A 440
#define TONE_B 466
#define TONE_C 523
#define TONE_D 587
#define TONE_Es 622
#define TONE_A2 880
#define TONE_B2 932

#define DISCOFLOOR1_PIN 12
#define DISCOFLOOR2_PIN 13
#define BUZZER_PIN 7
#define BUZZLED_PIN 8
#define RGB_R_PIN 9
#define RGB_G_PIN 10
#define RGB_B_PIN 11
#define LAUFLICHT1_PIN 4
#define LAUFLICHT2_PIN 5 
#define LAUFLICHT3_PIN 6
#define BUTTON_KARAOKE_PIN 1
#define BUTTON_SONG_PIN 2
#define BUTTON_ALL_PIN 3

// >>> variables <<< //
int wantToSwitchSong = 0;
int song = 0;
int lights = 0; //all lights off or on

int discofloor_stat = 0;
int buzzled_stat = 0;
int lauflicht_stat = 0;

//buttons pressed?
int button_karaoke_stat = 0;
int button_song_stat = 0;
int button_all_stat = 0;

//new var to check if buttons are pressed
int button_karaoke_pressed = 0;
int button_song_pressed = 0;
int button_all_pressed = 0;

int i = 0;

LiquidCrystal_I2C Lcd(0x27, 16, 2);

void setup() {
  pinMode(DISCOFLOOR1_PIN, OUTPUT);
  pinMode(DISCOFLOOR2_PIN , OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUZZLED_PIN, OUTPUT);
  pinMode(RGB_R_PIN, OUTPUT);
  pinMode(RGB_G_PIN, OUTPUT);
  pinMode(RGB_B_PIN, OUTPUT);
  pinMode(LAUFLICHT1_PIN, OUTPUT);
  pinMode(LAUFLICHT2_PIN, OUTPUT);
  pinMode(LAUFLICHT3_PIN, OUTPUT);
  pinMode(BUTTON_KARAOKE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_SONG_PIN, INPUT_PULLUP);
  pinMode(BUTTON_ALL_PIN, INPUT_PULLUP);

  randomSeed(analogRead(A1));
  Serial.begin(9600);
  
  //Lcd.init();
  Lcd.begin(16, 2);
  Lcd.clear();
  Lcd.backlight();
  Lcd.setCursor(0, 0);
  Lcd.print("hello");
}

void loop() {
 //wantToSwitchSong = 0;
/*
 if(song == 0){
    Lcd.clear();
    Lcd.setCursor(0, 0);
    Lcd.print("astronomia");
    astronomia();
   
 }else if(song == 1){
    Lcd.clear();
    Lcd.setCursor(0, 0);
    Lcd.print("blue");
    imBlue();
 }
 */
}


// >>> songs <<< //
void imBlue() {
  playTone(TONE_A, VIERTEL);
  playTone(TONE_B, VIERTEL);
  playTone(TONE_G, ACHTEL);
  playTone(TONE_B, ACHTEL);
  playTone(TONE_C, ACHTEL);
  playTone(TONE_C, ACHTEL);
  playTone(TONE_A, ACHTEL);
  playTone(TONE_B, HALBE);
  playTone(TONE_B, ACHTEL);
  playTone(TONE_D, ACHTEL);
  playTone(TONE_Es, VIERTEL);
  playTone(TONE_D, ACHTEL);
  playTone(TONE_C, ACHTEL);
  playTone(TONE_B, VIERTEL);
  playTone(TONE_G, ACHTEL);
  playTone(TONE_B, ACHTEL);
  playTone(TONE_C, ACHTEL);
  playTone(TONE_C, ACHTEL);
  playTone(TONE_A, ACHTEL);
  playTone(TONE_B, HALBE);
}

void astronomia(){
  playTone(TONE_G, VIERTEL);
  playTone(TONE_G, ACHTEL);
  playTone(TONE_D, ACHTEL);
  playTone(TONE_C, VIERTEL);
  playTone(TONE_B, VIERTEL);
  playTone(TONE_A, VIERTEL);
  playTone(TONE_A, ACHTEL);
  playTone(TONE_A, ACHTEL);
  playTone(TONE_C, VIERTEL);
  playTone(TONE_B, ACHTEL);
  playTone(TONE_A, ACHTEL);
  playTone(TONE_G, VIERTEL);
  playTone(TONE_G, ACHTEL);
  playTone(TONE_B2, ACHTEL);
  playTone(TONE_A2, ACHTEL);
  playTone(TONE_B2, ACHTEL);
  playTone(TONE_A2, ACHTEL);
  playTone(TONE_B2, ACHTEL);
  playTone(TONE_G, VIERTEL);
  playTone(TONE_G, ACHTEL);
  playTone(TONE_B2, ACHTEL);
  playTone(TONE_A2, ACHTEL);
  playTone(TONE_B2, ACHTEL);
  playTone(TONE_A2, ACHTEL);
  playTone(TONE_B2, ACHTEL);
}

// >>> play tone <<< //
void playTone(int f, int t){
  /*if(wantToSwitchSong == 1) {
    return;
  }*/
  changeLight();
  tone(BUZZER_PIN, f);
  delay(t);
  noTone(BUZZER_PIN);
  delay(10);
  checkButtons();
}

// >>> light changes <<< //
void checkButtons() {
  //All off/on  button_all_stat button_all_pressed
  button_song_stat = digitalRead(BUTTON_ALL_PIN);

  if((button_all_stat == 0) && (button_all_pressed == 0)){
    button_all_pressed = 1;
  }
  if((button_all_stat == 1) && (button_all_pressed == 1)){
    button_all_pressed = 0;
    //set int lights to on(1) or off(0)
    if(lights = 1){
      lights = 0;
    }else {
      lights = 1;
    }
  }

  //Song Change
  button_song_stat = digitalRead(BUTTON_SONG_PIN);

  if((button_song_stat == 0) && (button_song_pressed == 0)){
    button_song_pressed = 1;
  }
  if((button_song_stat == 1) && (button_song_pressed == 1)){
    button_song_pressed = 0;
    //change to the next song
    if(song > 0){
      song = 0;
    }else {
      song++;
      //wantToSwitchSong = 1;
    }
  }
  
}

void changeLight(){
  if(lights == 0){
    digitalWrite(DISCOFLOOR1_PIN, LOW);
    digitalWrite(DISCOFLOOR2_PIN, LOW);
    digitalWrite(BUZZLED_PIN, LOW);
    digitalWrite(RGB_R_PIN, LOW);
    digitalWrite(RGB_G_PIN, LOW);
    digitalWrite(RGB_B_PIN, LOW);
    digitalWrite(LAUFLICHT1_PIN, LOW);
    digitalWrite(LAUFLICHT2_PIN, LOW);
    digitalWrite(LAUFLICHT3_PIN, LOW);
  }else{
    changeBuzzLight();
    changeLauflicht();
    changeDiscofloor();
    changeRGB();

  }
  
}

void changeBuzzLight(){
  
  if(buzzled_stat == 0){
    buzzled_stat = 1;
    digitalWrite(BUZZLED_PIN, HIGH);
  }else{
    buzzled_stat = 0;
    digitalWrite(BUZZLED_PIN, LOW);
  } 
}


void changeLauflicht(){
  if(lauflicht_stat < 6){
    lauflicht_stat++;
  }else {
    lauflicht_stat = 4;
  }
  //write all leds low
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  //make the one on
  digitalWrite(lauflicht_stat, HIGH);
}

void changeDiscofloor() {
  if(discofloor_stat == 0){
    //blue leds on, green off
    digitalWrite(DISCOFLOOR1_PIN, HIGH);
    digitalWrite(DISCOFLOOR2_PIN, LOW);
    discofloor_stat = 1;
  }else{
    //green leds on, blue off
    digitalWrite(DISCOFLOOR1_PIN, LOW);
    digitalWrite(DISCOFLOOR2_PIN, HIGH);
    discofloor_stat = 0;
  }
}

void changeRGB() {
  analogWrite(RGB_R_PIN, random(0,256));
  analogWrite(RGB_G_PIN, random(0,256));
  analogWrite(RGB_B_PIN, random(0,256)); 
}


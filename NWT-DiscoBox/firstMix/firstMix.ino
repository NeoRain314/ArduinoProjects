//   >>> discofloor + buzzer with LED <<<     //


//define pins
#define BUZZER 1
#define BUZZER_LED 2
#define DISCOFLOOR_GREEN 3
#define DISCOFLOOR_BLUE 4

//define tone lengths and note frequenzes
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

// variables show status of single peaces
int buzz_led = 0; //the led in the buzzer (on/off)
int discoFloorStat = 0; //0 = blue leds; 1 = gree leds

void setup(){
  pinMode(DISCOFLOOR_GREEN, OUTPUT);
  pinMode(DISCOFLOOR_BLUE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUZZER_LED, OUTPUT);
}

void loop(){
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

void playTone(int f, int t){
  //function to change all lights
  changeLights();
  
  tone(BUZZER, f);
  delay(t);
  noTone(BUZZER);
  delay(10);
  
}

void changeLights(){
  //calls all other light functions
  changediscoFloor();
  changeBuzzLight();
}

void changeBuzzLight(){
  //light in buzzer
  if(buzz_led == 0){
    buzz_led = 1;
    digitalWrite(BUZZER_LED, HIGH);
  }else{
    buzz_led = 0;
    digitalWrite(BUZZER_LED, LOW);
  }
}

void changediscoFloor() {
  //discofloor
  if(discoFloorStat == 0){
    //blue leds on, green off
    digitalWrite(DISCOFLOOR_BLUE, HIGH);
    digitalWrite(DISCOFLOOR_GREEN, LOW);
    discoFloorStat = 1;
  }else{
    //green leds on, blue off
    digitalWrite(DISCOFLOOR_BLUE, LOW);
    digitalWrite(DISCOFLOOR_GREEN, HIGH);
    discoFloorStat = 0;
  }
}


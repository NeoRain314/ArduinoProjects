 #define BUZZER 1
#define BUZZER_LED 3

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

  
int buzz_led = 0;

void setup(){
  pinMode(BUZZER, OUTPUT);
  pinMode(BUZZER_LED, OUTPUT);
}

void loop(){
  astronomia();
}

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

void playTone(int f, int t){
  if(buzz_led == 0){
    buzz_led = 1;
    digitalWrite(BUZZER_LED, HIGH);
  }else{
    buzz_led = 0;
    digitalWrite(BUZZER_LED, LOW);
  }
    
  tone(BUZZER, f);
  delay(t);
  noTone(BUZZER);
  delay(10);
}

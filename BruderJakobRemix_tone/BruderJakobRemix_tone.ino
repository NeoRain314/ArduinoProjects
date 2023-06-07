//defines all Tones
#define T_C0 130//65
#define T_F0 175//87
#define T_G0 196//98
#define T_A0 220//110
#define T_H0 247//123
#define T_C1 262//130
#define T_D1 294//147
#define T_E1 330//165
#define T_F1 349//175
#define T_G1 392//196
#define T_A1 440//220
#define T_H1 493//247
//defines tone lengths
#define VIERTEL 256
#define ACHTEL (VIERTEL/2)
#define HALBE (VIERTEL*2)
#define PAUSE 10


void setup() {
  pinMode(4, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  bruderJakob();
}


void bruderJakob(){
  part1();
  part1();
  part2();
  part2();
  part3();
  part3();
  part4();
  part4();
}

void playTone(int f, int length, const char* text = "") {
  Serial.println(text);
  
  tone(4, f);
  delay(length/2);
  noTone(PAUSE);
  tone(4, f/2);
  delay(length/2);
  noTone(PAUSE);
  
 /* tone(4, f);
  delay(length/3);
  noTone(PAUSE); */

  
  //tone(4, f);
  //delay(length);
  //noTone(PAUSE);
}

void part1(){
  
  playTone(T_C1, VIERTEL, "Bru");
  playTone(T_D1, VIERTEL, "der");
  playTone(T_E1, VIERTEL, "Ja");
  playTone(T_C1, VIERTEL, "kob");
}

void part2(){
  playTone(T_E1, VIERTEL, "Schlaefst");
  playTone(T_F1, VIERTEL, "du");
  playTone(T_G1, HALBE, "noch?");
}

void part3(){
  playTone(T_G1, ACHTEL, "Hoerst");
  playTone(T_A1, ACHTEL, "du");
  playTone(T_G1, ACHTEL, "nicht");
  playTone(T_F1, ACHTEL, "die");
  playTone(T_E1, VIERTEL, "Glo");
  playTone(T_C1, VIERTEL, "cken");
}

void part4(){
  playTone(T_C1, VIERTEL, "Ding");
  playTone(T_G0, VIERTEL, "Ding");
  playTone(T_C1, HALBE, "Dong");
}

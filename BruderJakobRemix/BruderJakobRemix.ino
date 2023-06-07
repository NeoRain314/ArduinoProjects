unsigned long pin_fCounter[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long time_ms = 0;

#define FtoUS(f) 1000000/f

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

#define T_00 0

void setup() {
  pinMode(4, OUTPUT); // Melody Output
}

//makes the pin turning 1 and 0 after the counter reached the number
void togglePinMicroSec(int pin, unsigned long max_us){
  if(max_us == 0){
    digitalWrite(pin, LOW);
    return;
  }

  unsigned long delta_time = micros() - pin_fCounter[pin];
  if(delta_time < max_us/2){
    digitalWrite(pin, LOW);
  } else {
    digitalWrite(pin, HIGH);
    if(delta_time >= max_us){
      pin_fCounter[pin] = micros();
    }
  }
}


unsigned int melody[] = {       // Bruder Jakob (without other functions cuz idk)
       T_C1, T_00, T_D1, T_00, //first part (C,D,E,C)
       T_E1, T_00, T_C1, T_00, 
       T_C1, T_00, T_D1, T_00, //first part again (C,D,E,C)
       T_E1, T_00, T_C1, T_00,
       
       T_E1, T_00, T_F1, T_00, //second part (E,F,G)
       T_G1, T_00, T_00, T_00,
       T_E1, T_00, T_F1, T_00, //second part again (E,F,G)
       T_G1, T_00, T_00, T_00,   

       T_G1, T_A1, T_G1, T_F1, //third part  (E,F,G)
       T_E1, T_00, T_C1, T_00,   
       T_G1, T_A1, T_G1, T_F1, //third part again (E,F,G)
       T_E1, T_00, T_C1, T_00, 

       T_C1, T_00, T_G0, T_00, //last part (E,F,G)
       T_C1, T_00, T_00, T_00, 
       T_C1, T_00, T_G0, T_00, //last part again(E,F,G)
       T_C1, T_00, T_00, T_00, 
};


// consts the length of the melody and sets the position where he current is in the melody to 0
const int melody_length = sizeof(melody) / sizeof(melody[0]);
unsigned int melody_pos = 0;

void playMelody(){
  unsigned long delta_time_ms = millis() - time_ms;

  if(delta_time_ms >= 200) {
    time_ms = millis();
    
    melody_pos = (melody_pos + 1) % melody_length;
  }

  togglePinMicroSec(4, FtoUS(melody[melody_pos])); // melody
}

void loop() {
  playMelody(); //plays Bruder Jakob
 // togglePinMicroSec(12, 600000); //blinking LED 
}
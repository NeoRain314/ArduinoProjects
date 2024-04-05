unsigned long pin_fCounter[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long time_ms = 0;

#define FtoUS(f) 1000000/f

#define T_C0 65
#define T_F0 87
#define T_G0 98
#define T_A0 110
#define T_H0 123

#define T_C1 130
#define T_D1 147
#define T_E1 165
#define T_G1 196
#define T_A1 220
#define T_H1 247

#define T_C2 262
#define T_D2 294
#define T_E2 330
#define T_F2 349
#define T_G2 392
#define T_A2 440
#define T_H2 493
#define T_C3 523

#define T_00 0

void setup() {
  pinMode(4, OUTPUT); // Melody Buzzer - old buzzer
  pinMode(2, OUTPUT); // Bass Buzzer  - new buzzer
  pinMode(12, OUTPUT); //LED
}

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


unsigned int melody[] = {       // Faded
//begin
       T_C2, T_00, T_C2, T_00,
       T_C2, T_00, T_E2, T_00,

       T_A2, T_00, T_A2, T_00,
       T_A2, T_00, T_G2, T_00,
       
       T_E2, T_00, T_E2, T_00,
       T_E2, T_00, T_E2, T_00,

       T_H1, T_00, T_H1, T_00,
       T_H1, T_00, T_A0, T_00,   

//verse 
      //part1      
       T_00, T_C2, T_C2, T_A0,  
       T_C2, T_A0, T_C2, T_D2, 

       T_E2, T_00, T_C2, T_C2,  
       T_G0, T_E2, T_00, T_E2,

       T_00, T_00, T_00, T_00,  
       T_00, T_C2, T_C2, T_C2,

       T_H0, T_00, T_00, T_C2,  
       T_H0, T_A0, T_C2, T_00,

       //part2
       T_00, T_C2, T_C2, T_A0,  
       T_C2, T_A0, T_C2, T_D2, 

       T_E2, T_00, T_C2, T_C2,  
       T_G1, T_00, T_E2, T_00,

       T_00, T_00, T_00, T_00,  
       T_00, T_C1, T_C1, T_D1,

       T_00, T_00, T_00, T_00,  
       T_00, T_00, T_00, T_00,

       //part3
       T_00, T_00, T_00, T_00,  
       T_00, T_00, T_00, T_00, 

       T_00, T_00, T_00, T_00,  
       T_00, T_00, T_00, T_00, 

       T_00, T_00, T_00, T_00,  
       T_00, T_00, T_00, T_00, 

       T_00, T_00, T_00, T_00,  
       T_00, T_00, T_00, T_00, 

};
unsigned int bass[] = {     // Bass Faded
        T_A0, T_E1, T_C1, T_E1, // A moll
        T_A0, T_E1, T_C1, T_E1,

        T_F0, T_C1, T_A0, T_C1, // F dur
        T_F0, T_C1, T_A0, T_C1,

        T_C1, T_G1, T_E1, T_G1, // C dur
        T_C1, T_G1, T_E1, T_G1,

        T_G0, T_D1, T_H0, T_D1, // G dur
        T_G0, T_D1, T_H0, T_D1,
};

//unsigned int melody[] = {T_C1, T_D1, T_E1, T_F1, T_G1, T_A1, T_H1, T_C2};

// const melody
/*unsigned int melody[] = {     // Melody 1
       T_A2, T_H2, T_C3, T_H2,
       T_A2, T_H2, T_C3, T_H2,
       T_C2, T_E2, T_A2, T_E2,
       T_E2, T_E2, T_C2, T_C2,
};*/

// const bass
/*unsigned int bass[] = {     // Bass zu Melody 1
        T_A0, T_A0, T_00, T_00,
        T_A1, T_A1, T_00, T_00,
        T_A0, T_A0, T_00, T_00,
        T_A1, T_A1, T_00, T_00,

        T_C0, T_C0, T_00, T_00,
        T_C1, T_C1, T_00, T_00,
        T_C0, T_C0, T_00, T_00,
        T_C1, T_C1, T_00, T_00,
};*/



const int bass_length = sizeof(bass) / sizeof(bass[0]);
unsigned int bass_pos = 0;
const int melody_length = sizeof(melody) / sizeof(melody[0]);
unsigned int melody_pos = 0;

void playMelody(){
  unsigned long delta_time_ms = millis() - time_ms;

  if(delta_time_ms >= 300) {
    time_ms = millis();

    bass_pos = (bass_pos + 1) % bass_length;
    melody_pos = (melody_pos + 1) % melody_length;
  }

  togglePinMicroSec(4, FtoUS(melody[melody_pos])); // melody
  togglePinMicroSec(2, FtoUS(bass[bass_pos]));     // bass
}

void loop() {
  playMelody();
  togglePinMicroSec(12, 600000); //LED
}



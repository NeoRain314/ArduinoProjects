#include <IRremote.h>
#include <IRremoteInt.h>
#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>


#include <Servo.h>

//servo
Servo Lenkung;
#define SERVO_PIN 6
int mitte = 95;

// remote control
#define RECV_PIN 3
IRrecv irrecv(RECV_PIN); 
decode_results results;
#define REMOTE_VORWÄRTS 16736925
#define REMOTE_RÜCKWÄRTS 16754775
#define REMOTE_LINKS 16720605
#define REMOTE_RECHTS 16761405
#define REMOTE_STEHENBLEIBEN 16712445

//DC Motor
#define DCIN_PIN 11
#define DCOUT_PIN 12
#define SPEED_PIN 5



int carDirection = 0; //0 = stehenbleiben, 1 = vorwärts, 2 = rückwärts

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(DCIN_PIN, OUTPUT);
  pinMode(DCOUT_PIN, OUTPUT);
  pinMode(SPEED_PIN, OUTPUT);
  Lenkung.attach(SERVO_PIN);
  pinMode(RECV_PIN, INPUT);

  Serial.print("start");

  analogWrite(SPEED_PIN, 200  );

}

void loop() {
  remoteControl();
  delay(50);
}

void remoteControl() {
  if (irrecv.decode(&results)) { //Wenn Daten empfangen wurden

    Serial.println(results.value, DEC);//werden sie als Dezimalzahl (DEC) an den Serial-Monitor ausgegeben.
    
    if (results.value == 16736925) {
      carDirection = 1;
      Serial.println("vorwärts");
      Lenkung.write(mitte);
  
    }   //vorwärts fahren

    if (results.value == 16754775) {
      carDirection = 2;
      Serial.println("rückwärts");
      Lenkung.write(mitte);

    }//rückwärts fahren

    if (results.value == 16712445) {
      carDirection = 0;
      Serial.println("stehenbleiben");
      Lenkung.write(mitte);
    }   //stehenbleiben

    if (results.value == 16720605) {
      Lenkung.write(mitte - 20);
      Serial.println("links");
    } //links

    if (results.value == 16761405) {
      Lenkung.write(mitte + 20);
      Serial.println("rechts");
    } //rechts

    irrecv.resume(); //Der nächste Wert soll vom IR-Empfänger eingelesen werden
  }

  drive();
}

void drive() {
  if (carDirection == 1) { //fahr  vorwärts
    //Serial.println("rückwärts");
    digitalWrite(DCIN_PIN, LOW);
    digitalWrite(DCOUT_PIN, HIGH);
  }
  if (carDirection == 2) { //fahr  rückwärts
    //Serial.println("vorwärts");
    digitalWrite(DCIN_PIN, HIGH);
    digitalWrite(DCOUT_PIN, LOW);
  }
  if (carDirection == 0) { //bleib stehen
    //Serial.println("stehenbleiben");
    digitalWrite(DCIN_PIN, LOW);
    digitalWrite(DCOUT_PIN, LOW);
  }
}

void followLine() {
  /*
    if( ir sensor rechts misst signal){
    //   drehe Auto nach rechts und fahr mini stück vorwärts
     }
    if( ir sensor links misst signal){
    //    drehe Auto nach links und fahr mini stück vorwärts
    }
  */
}






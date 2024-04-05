#include <IRremote.h>
#include <IRremoteInt.h>
#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#include <Servo.h>

//servo
Servo Lenkung;
#define SERVO_PIN 5

// remote control
int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define DCIN_PIN 11
#define DCOUT_PIN 12

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  Lenkung.attach(SERVO_PIN);
  pinMode(RECV_PIN, INPUT);
  pinMode(DCIN_PIN, OUTPUT);
  pinMode(DCOUT_PIN, OUTPUT);
  Serial.print("start");
}

void loop() {
  remoteControl();
  delay(50);
}

void remoteControl(){
  if (irrecv.decode(&results)) { //Wenn Daten empfangen wurden

    //Serial.println(results.value, DEC);//werden sie als Dezimalzahl (DEC) an den Serial-Monitor ausgegeben.
    
    if (results.value == 16736925) {
      Serial.println("vorwärts");
      Lenkung.write(90);

      digitalWrite(DCIN_PIN, HIGH);
      digitalWrite(DCOUT_PIN, LOW);
  
    }   //vorwärts fahren

    if (results.value == 16754775) {
      Serial.println("rückwärts");
      Lenkung.write(90);

    }//rückwärts fahren

    if (results.value == 16712445) {
      Serial.println("stehenbleiben");
      Lenkung.write(90);

      digitalWrite(DCIN_PIN, LOW);
      digitalWrite(DCOUT_PIN, LOW);
    }   //stehenbleiben

    if (results.value == 16720605) {
      Lenkung.write(180);
      Serial.println("links");
    } //links

    if (results.value == 16761405) {
      Lenkung.write(0);
      Serial.println("rechts");
    } //rechts

    irrecv.resume();
  }
}




#include <IRremote.h>
#include <IRremoteInt.h>
#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#include <Servo.h>

/*Servo
  95  mitte
  < 95 links
  > 95 rechts
*/

#define RECV_PIN 3
IRrecv irrecv(RECV_PIN); 
decode_results results;

#define SERVO_PIN 6

#define DC_PIN1 11
#define DC_PIN2 12
#define SPEED_PIN 5
Servo Lenkung;
int speed = 100;

int carDirection = 0;

void setup() {
  //Lenkung.attach(SERVO_PIN);

  pinMode(DC_PIN1, OUTPUT);
  pinMode(DC_PIN2, OUTPUT);
  pinMode(SPEED_PIN, OUTPUT);

  pinMode(RECV_PIN, INPUT);

  analogWrite(SPEED_PIN, speed);

  Serial.begin(9600);

  Serial.println("start");
}

void loop() {
  remoteControl();
  /*//Lenkung.write(95);
  digitalWrite(DC_PIN1, LOW);
  digitalWrite(DC_PIN2, HIGH);

  delay(3000);

  //Lenkung.write(75);

  delay(2000);

  Lenkung.write(115);
  remoteControl();

  delay(2000);

  //Lenkung.write(90);
  digitalWrite(DC_PIN1, HIGH);
  digitalWrite(DC_PIN2, LOW);

  delay(3000);

  //Lenkung.write(95);
  digitalWrite(DC_PIN1, LOW);
  digitalWrite(DC_PIN2, LOW);

  delay(3000);*/
}

void remoteControl() {
  //Serial.println("Remote");

  Serial.println(results.value, DEC);
  
  if (irrecv.decode(&results)) { //Wenn Daten empfangen wurden

    
    
    if (results.value == 16736925) {
      carDirection = 1;
      Serial.println("vorwärts");
  
    }   //vorwärts fahren

    if (results.value == 16754775) {
      carDirection = 2;
      Serial.println("rückwärts");

    }//rückwärts fahren

    if (results.value == 16712445) {
      carDirection = 0;
      Serial.println("stehenbleiben");
    }   //stehenbleiben

    if (results.value == 16720605) {
      Serial.println("links");
    } //links

    if (results.value == 16761405) {
      Serial.println("rechts");
    } //rechts

    irrecv.resume(); //Der nächste Wert soll vom IR-Empfänger eingelesen werden
  }
}


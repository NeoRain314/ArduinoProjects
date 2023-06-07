#define BUZZER 2
#define RED_LED 6
#define YELLOW_LED 7
#define GREEN_LED 8
#define BLUE_LED 9

int speed = 100;

void setup() {
  pinMode(BUZZER, OUTPUT); 
  pinMode(RED_LED, OUTPUT); 
  pinMode(YELLOW_LED, OUTPUT); 
  pinMode(GREEN_LED, OUTPUT); 
  pinMode(BLUE_LED, OUTPUT); 
}

void loop() {
  disco();
  playTone(440, 50);
}

void disco(){
    //red
  led(RED_LED, HIGH);
  delay(speed);
  led(RED_LED, LOW);
  delay(speed);
  //yellow
  led(YELLOW_LED, HIGH);
  delay(speed);
  led(YELLOW_LED, LOW);
  delay(speed);
  //green
  led(GREEN_LED, HIGH);
  delay(speed);
  led(GREEN_LED, LOW);
  delay(speed);
  //blue
  led(BLUE_LED, HIGH);
  delay(speed);
  led(BLUE_LED, LOW);
  delay(speed);
}


void led(int pin, int stat){
  digitalWrite(pin, stat);
}

void playTone(int f, int length){
  tone(BUZZER, f);
  delay(length);
  noTone(BUZZER);
  delay(10);
}




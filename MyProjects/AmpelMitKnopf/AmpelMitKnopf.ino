#define BUTTONPIN 10
#define RED 3
#define YELLOW 5
#define GREEN 7

int light = 0;
int buttonPressed = 0;

void led(int red, int yellow, int green) {
  // red
  if(red == 1) {
    digitalWrite(RED, HIGH);    
  }else {
    digitalWrite(RED, LOW);
  }
  // yellow
  if(yellow == 1) {
    digitalWrite(YELLOW, HIGH);
  }else {
    digitalWrite(YELLOW, LOW);
  }
  // green
  if(green == 1) {
    digitalWrite(GREEN, HIGH);
  }else {
    digitalWrite(GREEN, LOW);
  }
}

void setup() {
  pinMode(3, OUTPUT); // red
  pinMode(5, OUTPUT); // yellow
  pinMode(7, OUTPUT); // green
  pinMode(BUTTONPIN, INPUT_PULLUP); // button
}

void loop() {

  delay(1000/60);

  int button = digitalRead(BUTTONPIN);

  if(button == LOW) {
    buttonPressed = 1;
  }
  if(button == HIGH && buttonPressed == 1) {
    buttonPressed = 0;
    light += 1;
  }

  if(light %5 == 0) {
    // green on - rest off
    led(0, 0, 1);
  }else if(light %5 == 1) {
    // yellow on - rest off
    led(0, 1, 0);
  }else if(light %5 == 2) {
    // red on - rest off
    led(1, 0, 0);
  }else if(light %5 == 3) {
    // yellow and red on - rest off
    led(1, 1, 0);
  }else if(light %5 == 4) {
    // all off
    led(0, 0, 0);
  }

}
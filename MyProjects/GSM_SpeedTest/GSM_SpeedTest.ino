// if button1 pressed -> GSM faster; if button2 pressed -> GSM slower

#define GSM1 10
#define IN1  8
#define IN2  9
#define button1 6
#define button2 7

int button1_pressed = 0;
int button2_pressed = 0;
int GSM_speed = 0;


void setup(){
  pinMode(GSM1,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
}

void loop(){
  checkButtons();
  writeGSM1(HIGH, LOW, GSM_speed);
}

void writeGSM1(int p1, int p2, int speed){
  digitalWrite(IN1, p1);
  digitalWrite(IN2, p2);
  analogWrite(GSM1, speed);
}

void checkButtons(){
 //button1 -------- faster
  if(digitalRead(button1) == 0 && button1_pressed == 0){
    button1_pressed = 1;
  }
  if(digitalRead(button1) == 1 && button1_pressed == 1){
    button1_pressed = 0;
    if (GSM_speed < 255) GSM_speed += 15; //15, 17, 5
  }

 //button2 -------- slower
  if(digitalRead(button2) == 0 && button2_pressed == 0){
    button2_pressed = 1;
  }
  if(digitalRead(button2) == 1 && button2_pressed == 1){
    button2_pressed = 0;
    if (GSM_speed > 0) GSM_speed -= 15; //15, 17, 5
  }
}




  #define button1_pin 1
#define light1_pin 2

int button1_pressed = false;
int light1 = 0;

void setup(){
  pinMode(button1_pin, INPUT_PULLUP);
  pinMode(light1_pin, OUTPUT);
}

void loop(){
  /*
  if(digitalRead(button1_pin) == 0){
    digitalWrite(light1_pin, HIGH);
  }else{
    digitalWrite(light1_pin, LOW);
  }*/

  
  if((digitalRead(button1_pin) == 0) && (button1_pressed == false)){
    button1_pressed = true;
  }
  if((digitalRead(button1_pin) == 1) && (button1_pressed == true)){
    button1_pressed = false;
    changeLight();
  }
  
}


void changeLight(){
  if(light1 == 1){
    light1 = 0;
    digitalWrite(light1_pin, LOW);
  }else{
    light1 = 1;
    digitalWrite(light1_pin, HIGH);
  }
}

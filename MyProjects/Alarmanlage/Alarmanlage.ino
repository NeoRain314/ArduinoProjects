int pinCounter[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
 pinMode(11, OUTPUT);
 pinMode(3, OUTPUT);
}

void myTone(int pin, int num){
  if(pinCounter[pin] == num){
    digitalWrite(pin, LOW);
  }
  if(pinCounter[pin] == num*2){
    digitalWrite(pin, HIGH);
    pinCounter[pin]  = 0;
  }

  pinCounter[pin]++;
}

void loop() { 
  myTone(11, 600);
  myTone(3, 100);
}

/*

int f = 400;

delay(1);
  tone(5,  );
  f +=1;

  if(f > 2000) {
    f = 400;
  }
  */
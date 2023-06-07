/*
void setup() {
Serial.begin(9600);
for (int n=0; n<30; n++){
Serial.println("hello");
Serial.println(n);
}
}

void loop() {
}
*/



// sirene

int lowF = 440; // lowest frequenz
int highF = 1000; //highest frequenz
int pause = 5; // pause between the tones
int led = 9;

void setup() {
}

void loop() {
//go up
for(int f=lowF; f < highF; f++){
ledOnOff(0);
tone(4, f);
delay(pause);
ledOnOff(1);
}
//go down
for(int f=highF; f > lowF; f--){
ledOnOff(0);
tone(4,f);
delay(pause);
ledOnOff(1);
}

}

void ledOnOff(int stat){
if(stat == 0){
digitalWrite(led, LOW);
}else{
//next led
if (led < 13){
led++;
} else{
led = 9;
}
digitalWrite(led, HIGH);
}

}
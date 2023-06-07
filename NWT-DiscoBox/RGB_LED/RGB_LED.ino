//int q; // Variable für taster
void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
 // pinMode(7,INPUT_PULLUP);


}

void loop() {
  // put your main code here, to run repeatedly:
  // if(q==0){
   for(int r=0;r<256; r++){
     analogWrite(10,r);
      for(int g=0; g<256; g++){
         analogWrite(9,g);
       for(int b=0; b<256; b++){
            analogWrite(8,b);
       }
     }
   }
  delay(5000);
 // }
}

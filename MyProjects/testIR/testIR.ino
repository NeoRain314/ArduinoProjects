#include <IRremote.hpp>

void setup() {
  IrReceiver.begin(44);
  Serial.begin(9600);
}

void loop() {
  delay(200);
  if (IrReceiver.decode()){
    if (IrReceiver.decodedIRData.address == 0){
      IrReceiver.resume();            // receive the next value
      Serial.println(IrReceiver.decodedIRData.command);
    }
  }
}

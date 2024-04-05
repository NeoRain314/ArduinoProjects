#define BUTTON 9

int button_stat = 0; //der tatsächliche Status (gedrückt/nicht gedrückt) vom Taster (0 = gedrückt; 1 = nicht gedrückt)
int button_pressed = 0; //der manuell gesetzte Status vom Taster  (1 = gedrückt; 0 = nicht gedrückt)

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  button_stat = digitalRead(BUTTON);
  if(button_stat == 0 && button_pressed == 0){ //wenn tatsächlicher Status gedrückt und manueller Status nicht gedrückt
    button_pressed = 1; //manueller Status auf gedrückt (1) gesetzt
  }
  if(button_stat == 1 && button_pressed == 1){ //wenn tatsächlicher Status nicht gedrückt und manueller Status gedrückt
    button_pressed = 1; //manueller Status nicht gedrückt (0) gesetzt
    action(); 
}

void action(){
  //wird ausgeführt wenn der Taster gedrückt und wieder losgelassen wurde :)
}
// > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > // libraries, defines, vars
#include <LiquidCrystal_I2C.h>

#define TASTER_UP_PIN 8
#define TASTER_DOWN_PIN 9
#define TASTER_LEFT_PIN 0
#define TASTER_RIGHT_PIN 0
#define TASTER_SELECT_PIN 3
#define TASTER_START_PIN 4
#define BUZZER_PIN 0
#define LED_1_PIN 0
#define LED_2_PIN 0
#define LED_3_PIN 0
#define LED_4_PIN 0

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------------------------------------------------------------// var - main
int mode_num = 0;
char* mode_names[] = {"Labyrinth Game", "Obstacle Game"};

int taster_up_stat = 1;
int taster_down_stat = 1;
int taster_left_stat = 1;
int taster_right_stat = 1;
int taster_select_stat = 1;
int taster_start_stat = 1;

// ---------------------------------------------------------------------// var - main game
int player_x_pos = 0;
int player_y_pos = 0;

// ---------------------------------------------------------------------// var - labyrinth game
int labyrinth_game_score = 0;
int labyrinth_game_highscore = 0;

// ---------------------------------------------------------------------// var - obstacle game
int obstacle_game_score = 0;
int obstacle_game_highscore = 0;
int obstacle_amount = 0;
int obstacles_x_pos[10] = {};
int obstacles_y_pos[10] = {};


// > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > // SETUP
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  pinMode(TASTER_UP_PIN, INPUT_PULLUP);
  pinMode(TASTER_DOWN_PIN, INPUT_PULLUP);
  pinMode(TASTER_LEFT_PIN, INPUT_PULLUP);
  pinMode(TASTER_RIGHT_PIN, INPUT_PULLUP);
  pinMode(TASTER_SELECT_PIN, INPUT_PULLUP);
  pinMode(TASTER_START_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
  

  lcd.init();
  lcd.clear();
  lcd.backlight();
}

// > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > // main functions
// ------------------------------------------------------------------------------------------// loop
void loop() {
  
  // - - - - - - - - - - - - - - - - - - - - // start and select gamemode
  if(digitalRead(TASTER_SELECT_PIN) == 0 && (taster_select_stat == 1)){
    taster_select_stat = 0;
  }else if(digitalRead(TASTER_SELECT_PIN) == 1 && (taster_select_stat == 0)){ //call function when button is released
    taster_select_stat = 1;
    selectMode();
  }

  if(digitalRead(TASTER_START_PIN) == 0 && (taster_start_stat == 1)){
    taster_start_stat = 0;
  }else if(digitalRead(TASTER_START_PIN) == 1 && (taster_start_stat == 0)){ //call function when button is released
    taster_start_stat = 1;
    startMode();
  }

  // - - - - - - - - - - - - - - - - - - - - // update Display
  if(millis() % 500 == 0){
    lcd.clear();
    printCharLcd(mode_names[mode_num], 0, 0);
    printCharLcd("- press start -", 0, 1);
  }
}

void selectMode(){
  mode_num++;
  if(mode_num>1) mode_num = 0;
  Serial.print("mode: ");
  Serial.print(mode_names[mode_num]);
  Serial.print(" (");
  Serial.print(mode_num);
  Serial.println(")");
}

void startMode(){
  Serial.println("Game Started");
  if(mode_num == 0){
    labyrinthGame();
  }else if(mode_num == 1){
    obstacleGame();
  }
}

// ------------------------------------------------------------------------------------------// labyrinth game
void labyrinthGame(){
  
}

// ------------------------------------------------------------------------------------------// obstacle game
void obstacleGame(){
  player_x_pos = 0;
  player_y_pos = 0;

  while(true){
    // - - - - - - - - - - - - - - - - - - - - // spawn obstacles
    /*if(random(10000) == 0){
      Serial.println("spawned obstacle");
    }*/
    /*if(millis() % 500 == 0){
      obstacles_x_pos[obstacle_amount] = 15;
      obstacles_y_pos[obstacle_amount] = random(0);
      Serial.println(obstacle_amount);
      Serial.println(obstacles_x_pos[obstacle_amount]);
      Serial.println(obstacles_y_pos[obstacle_amount]);
      obstacle_amount++;
    }*/

    // - - - - - - - - - - - - - - - - - - - - // move_up
    if(digitalRead(TASTER_UP_PIN) == 0 && (taster_up_stat == 1)){
      taster_up_stat = 0;
    }else if(digitalRead(TASTER_UP_PIN) == 1 && (taster_up_stat == 0)){ 
      //call function when button is released
      taster_up_stat = 1;
      if(player_y_pos > 0) player_y_pos--;
    }

    // - - - - - - - - - - - - - - - - - - - - // move_down
    if(digitalRead(TASTER_DOWN_PIN) == 0 && (taster_down_stat == 1)){
      taster_down_stat = 0;
    }else if(digitalRead(TASTER_DOWN_PIN) == 1 && (taster_down_stat == 0)){ 
      //call function when button is released
      taster_down_stat = 1;
      if(player_y_pos < 1) player_y_pos++;
    }

    // - - - - - - - - - - - - - - - - - - - - // update Game & Display
    /*if(millis() % 1000 == 0){ // ---- update Obstacles
      for(int i=0; i<16; i++){
        obstacles_x_pos[i] -= 1;
        if(obstacles_x_pos[i] < 0) obstacles_x_pos[i] = 15;
      }
    }
    */
    if(millis() % 500 == 0){ // ---- update Display
      lcd.clear();
      printCharLcd("H", player_x_pos, player_y_pos);

      /*for(int i=0; i<16; i++){
        printCharLcd("-", obstacles_x_pos[i], obstacles_y_pos[i]);
      }*/
    }
  }
}

// > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > // sub functions
void printCharLcd(char text[], int cursorX, int cursorY){
  lcd.setCursor(cursorX, cursorY);
  lcd.print(text);
}

void printIntLcd(int num, int cursorX, int cursorY){
  lcd.setCursor(cursorX, cursorY);
  lcd.print(num);
}

void printFloatLcd(float num, int cursorY, int cursorX){
  lcd.setCursor(cursorX, cursorY);
  lcd.print(num);
}

void playTone(int f, int dur){
  tone(BUZZER_PIN, f);
  delay(dur); //tone duration
  noTone(BUZZER_PIN);
  delay(dur); //pause == tone dur
}

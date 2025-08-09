const char* study_menu_entries[] = {"25/5 min", "Rept: 1 ", "start", "back"};
const char* study_menu_modes[] = {"25/5 min", "50/10", "90/20 min"};
int studytimer_time[] = {0, 0};

class StudyMenu : public AbstractMenu {
  int selected_index = 0;
  
  
  public:
  bool study_stat = 0;
  int study_mode = 0;
  int study_repetitions = 1;
  unsigned long studytimer_star_mill = 0;
  unsigned long studytimer_time_mill = 0;

  virtual void draw(){
    if(study_stat) {
      printMenuBar("Study Menu");
      printMenuEntries(selected_index, 4, study_menu_entries); // index, menu_length, menu_entries[]
    }
  }

  virtual void selectPressed() {
    selected_index = (selected_index + 1) % 4;
  }
   
  virtual void okPressed(){
    beforeMenuSwitch();
    if(study_stat == true) {
      //interrupt study mode
      study_stat = false;
    }
    if (selected_index == 0){
      study_mode = (study_mode + 1) % 3; 
      study_menu_entries[0] = study_menu_modes[study_mode];
    }
    if (selected_index == 1){
      study_repetitions += 1;
      if(study_repetitions>5) study_repetitions = 1;

      sprintf(study_menu_entries[1], "Rept: %d", study_repetitions);
    }
    if (selected_index == 2){
      if(study_mode == 0){
        studytimer_time[0];
      } else if(studytimer_time == 1){}
      study_stat = true;
    };
    if (selected_index == 3) g_pActiveMenu = g_pMainMenu;
  }
};

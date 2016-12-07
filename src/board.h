#ifndef BOARD_H_
#define BOARD_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>
#include "SDL/SDL_ttf.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "sprite.h"
#include "pacman.h"
#include "ghost.h"
#include "food.h"
#include "score.h"
#include "highscore.h"
#include "timer.h"
#include "menu.h"
#include "string_input.h"
#include "map_data.h"

class Board {
public:
  Board(SDL_Surface *screen);
  
  void run();
  
 private:
  void exit_program(std::string message);
  void update_screen();
  void show_start_menu(bool &quit);
  void run_pause_loop(bool &quit);
  void handle_key_press(bool& quit, SDL_Event &event);
  void move_stuff();
  void do_creepy_ghost_stuff();
  void handle_ghost_eats_pacman(bool &quit);
  void handle_no_food_left(bool &quit);
  void handle_ghost_mood();
  void draw_background();
  void draw_everything();
  
  SDL_Surface *screen;
  Start Startup;
  Button theButton1;
  Button theButton2;
  Button theButton3;
  Button theButton4;
  
  Pacman myPacman;
  Ghost1 myGhost1;
  Ghost2 myGhost2;
  Ghost3 myGhost3;
  Score myScore;
  Highscore myHighscore;
  Timer fps;
  Timer checktimer1;
  Timer checktimer2;
  Timer checktimer3;
  Timer special_food_timer;
  
  std::vector<Food> food_vector;
  std::vector<Special_Food> special_food_vector;
  std::vector<SDL_Rect> maze;
  SDL_Rect wall25;
  std::vector<SDL_Rect> checkpoint_vector;
  void handle_end_game(bool &quit);
};

#endif /* BOARD_H_ */

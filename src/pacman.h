//============================================================================
// Name        : pacman.h
// Author      : Benjamin, Ingrid, Jonatan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================

#ifndef PACMAN_H
#define PACMAN_H



//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>  //for felsokning med std::cout
#include "SDL/SDL_ttf.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "sprite.h"
#include "ghost.h"
#include "score.h"


//===================== PACMAN ==============================================
class Pacman : public Sprite
{
private:
  //The collision box of the square
  SDL_Rect box;
  int x, y;

  //The velocity of the square
  int xVel, yVel;

  //The attributes of the Pacman
  const int PACMAN_WIDTH  {30};
  const int PACMAN_HEIGHT {29};

  //the directions of the pacman
  const int PACMAN_RIGHT {0};
  const int PACMAN_LEFT {1};
  const int PACMAN_UP {2};
  const int PACMAN_DOWN {3};

  //Pacmans lives
  int lives;
 
  //Its current frame
  int frame;

  //Its animation status
  int status;

  //food left
  int food_left;

  //true if pacman has eaten special_food
  bool pacman_has_eaten_special_food;

   
  //The areas of the pacmansheet
  SDL_Rect clipsRight;
  SDL_Rect clipsLeft;
  SDL_Rect clipsDown;
  SDL_Rect clipsUp;


public:
  //Initializes the variables
  Pacman(); //string filename

  //Reveals pacmans position, ghosts will ask for this
  int reveal_position_x();
  int reveal_position_y();

  //Keeps tracks of pacmans lives and when he dies
  int life();
  void showlife(SDL_Surface*);
  bool game_over();
  bool eat_eaten(class Ghost&, class Score&);
 
 //Pacman eats food for points
  void eat_food(std::vector<class Food>&, class Score&); //bool eat_food(class Food&, class Score&);

  //Pacman eats special_food - ghosts flees
  void eat_special_food(std::vector<class Special_Food>&, class Score&);

  //Takes key presses and adjusts the square's velocity
  void handle_input();

  //Moves the Pacman
  void move(std::vector<SDL_Rect>, SDL_Rect);

  //Shows the Pacman on the screen
  void show(SDL_Surface*);
  
  //Sets Pacmans position to startposition
  void get_home();

  //returns true if there is no food left
  bool no_food_left();

  void pacman_change_mood();
  
  bool has_pacman_eaten_special_food();

  void set_clips();

  void showlife(int, SDL_Surface*);
};

#endif

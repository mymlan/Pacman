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
class Pacman
{
private:
  //The collision box of the square
  SDL_Rect box;
  int x, y;

  //The velocity of the square
  int xVel, yVel;

  //Pacmans lives
  int lives;
 
  //Its current frame
    int frame;

    //Its animation status
    int status;

  //food left
  int food_left;

public:
  //Initializes the variables
  Pacman();

  //Reveals pacmans position, ghosts will ask for this
  int reveal_position_x();
  int reveal_position_y();

  //Keeps tracks of pacmans lives and when he dies
  int life();
  void showlife();
  bool game_over();
  bool eat_eaten(class Ghost&, class Score&);
 
 //Pacman eats food for points
  void eat_food(std::vector<class Food>&, class Score&); //bool eat_food(class Food&, class Score&);

  //Pacman eats special_food - ghosts flees
  bool eat_special_food(class Special_Food&, class Score&);

  //Takes key presses and adjusts the square's velocity
  void handle_input();

  //Moves the Pacman
  void move(std::vector<SDL_Rect>, SDL_Rect);

  //Shows the Pacman on the screen
  void show();
  
  //Sets Pacmans position to startposition
  void get_home();

  //returns true if there is no food left
  bool no_food_left();

  

};


#endif

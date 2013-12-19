//============================================================================
// Name        : food.h
// Author      : Benjamin, Ingrid, Jonatan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================

#ifndef FOOD_H
#define FOOD_H


//The headers
#include "sprite.h"
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


//========================================== FOOD ==============================================

//Food
class Food : public Sprite
{
 private:
  SDL_Rect box;
  bool eaten_;
 public:
  Food(int,int);
  bool eaten();
  void was_eaten();
  void show(SDL_Surface*);
  SDL_Rect get_box();
  void show_all_food(std::vector<Food>, SDL_Surface*);
};
//###############################################################################################

//========================================== SPECIAL FOOD =======================================

//Special_Food
class Special_Food : public Sprite
{
 private:
  SDL_Rect box;
  bool eaten_;

 public:
  Special_Food(int,int);
  bool eaten();
  void was_eaten();
  void show(SDL_Surface*);
  void show_all_special_food(std::vector<Special_Food>, SDL_Surface*);
  SDL_Rect get_box();  
};

#endif

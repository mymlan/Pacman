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



//========================================== FOOD ==============================================

//Food
class Food : public Sprite
{
private:
  SDL_Rect box;
  bool eaten_;
public:
  Food(int,int); //filname
  bool eaten();
  void was_eaten();
  void show() = delete;
  SDL_Rect get_box();
  void show_all_food(std::vector<Food> food_vector);
 

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
  Special_Food(int,int); //filename
  bool eaten();
  void was_eaten();
  void show();
  void show_all_special_food(std::vector<Special_Food> special_food_vector);

  SDL_Rect get_box();

  
};







#endif

//============================================================================
// Name        : food.cpp
// Author      : Benjamin, Ingrid, Jonatan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================

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
#include "food.h"
#include "sprite.h"




//============================================================================
//  FOOD
//============================================================================


Food::Food(int x_cord, int y_cord)
{
  bool eaten_=false;
 
  //Initialize the offsets
  box.x = x_cord;
  box.y = y_cord;

  //Set the foods dimensions
  box.w = PACMAN_WIDTH; //we should change the global constants names PACMAN_WIDTH to CHARACTER_WIDTH
  box.h = PACMAN_HEIGHT;
}

void Food::was_eaten()
{
  eaten_=true;

}

bool Food::eaten()
{
  return eaten_;
}

void Food::show()
{
  /*if (!eaten())
    {
      apply_surface(box.x,box.y,food, screen);
      }*/
  Sprite animation;
  animation.show_food(box.x, box.y, eaten());
}




//Returns SDL-object of ghost
SDL_Rect Food::get_box()
{
  return box;
}









//============================================================================
//  Class: Special_Food
//============================================================================
Special_Food::Special_Food(int x_cord, int y_cord)
{
  bool eaten_=false;

  //Initialize the offsets
  box.x = x_cord;
  box.y = y_cord;

  //Set the foods dimensions
  box.w = PACMAN_WIDTH;    //we should change the global constants names PACMAN_WIDTH to CHARACTER_WIDTH
  box.h = PACMAN_HEIGHT;
}

void Special_Food::was_eaten()
{
  eaten_=true;
}

bool Special_Food::eaten()
{
  return eaten_;
}

void Special_Food::show()
{
  /*if (!eaten())
    {
      apply_surface(box.x,box.y,special_food, screen);
      }*/
  Sprite animation;
  animation.show_special_food(box.x,box.y,eaten());
}



//Returns SDL-object of ghost
SDL_Rect Special_Food::get_box()
{
  return box;
}



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
class Food
{
private:
  SDL_Rect box;
  bool eaten_;
public:
  Food(int,int);
  bool eaten();
  void was_eaten();
  void show();
  SDL_Rect get_box();
};


//###############################################################################################

//========================================== SPECIAL FOOD =======================================


//Special_Food
class Special_Food
{
private:
  SDL_Rect box;
  bool eaten_;
public:
  Special_Food(int,int);
  bool eaten();
  void was_eaten();
  void show();
  SDL_Rect get_box();
};


/*
//Ghosts checkpoints, to make their ways in the maze
class Checkpoint
{
private:
  SDL_Rect box;

<<<<<<< HEAD
public:
  Checkpoint(int, int);
  SDL_Rect get_box();
  void show(); //används för att testa, ska egentligen vara osynlig
 
};
*/




#endif

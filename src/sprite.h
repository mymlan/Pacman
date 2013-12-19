//============================================================================
// Name        : Sprite.h
// Author      : Benjamin, Ingrid, Jonathan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================
#ifndef SPRITE_H
#define SPRITE_H

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



//============================================================================
// Sprite 
//============================================================================

class Sprite

{
public:
  Sprite( std::string filename );
  virtual ~Sprite();
  virtual void apply_surface( SDL_Surface* destination, SDL_Rect* clip = NULL );
  
  virtual bool check_collision( SDL_Rect A, SDL_Rect B );
  

  virtual void show() = 0;


 protected:

  SDL_Surface *ytpekare;

};



#endif

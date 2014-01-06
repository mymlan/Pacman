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
#include <iostream>
#include "SDL/SDL_ttf.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>




//============================================================================
// Sprite 
//============================================================================

class Sprite

{
public:
 
  Sprite();
  Sprite(const Sprite& f); //kopiering
  virtual ~Sprite();
   void apply_surface(int x, int y, SDL_Surface* ytpekare, SDL_Surface* destination, SDL_Rect* clip = NULL ); //virtual
  
  bool check_collision( SDL_Rect A, SDL_Rect B ); 
  

  virtual void show(SDL_Surface*) = 0;


 protected:

  SDL_Surface *ytpekare;
  int MAP_WIDTH;
  int SCREEN_HEIGHT;
  int SCREEN_WIDTH;
};



#endif

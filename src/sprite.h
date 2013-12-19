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




//============================================================================
// Sprite 
//============================================================================

class Sprite

{
public:
  // Sprite( std::string filename );
  virtual ~Sprite();
  // virtual void apply_surface( SDL_Surface* destination, SDL_Rect* clip = NULL ); 
  // som den såg ut inatt

  void apply_surface(int x, int y, SDL_Surface* ytpekare, SDL_Surface* destination, SDL_Rect* clip = NULL ); //virtual
  
  bool check_collision( SDL_Rect A, SDL_Rect B ); //virtual
  

  virtual void show(SDL_Surface*) = 0; //pure virtual


 protected:

  SDL_Surface *ytpekare;

};



#endif

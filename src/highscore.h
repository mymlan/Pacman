//============================================================================
// Name        : highscore.h
// Author      : Benjamin, Ingrid, Jonatan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================

#ifndef HIGHSCORE_H
#define HIGHSCORE_H

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
#include "score.h"



//========================================== HIGHSCORE============================================

//Highscore
class Highscore : public Sprite
{
private:
  std::vector<Score> highscoretable;
 
public:
   Highscore() = default;
  bool is_new_highscore(Score&);
  void save_new_highscore(Score&);
  void show(SDL_Surface*);
  void load_list();
};

#endif

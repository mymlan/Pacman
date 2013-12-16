
//============================================================================
// Name        : score.h
// Author      : Benjamin, Ingrid, Jonatan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================

#ifndef SCORE_H
#define SCORE_H


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



//========================================== SCORE ==============================================
class Score
{
private:
  int points;
public:
  Score();
  void reset_score();
  void add_points(int);
  std::string get_score(); // return score as string
  void show();
  int return_score(); // returns score as int
};

#endif

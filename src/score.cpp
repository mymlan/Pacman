


//============================================================================
// Name        : score.cpp
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
#include "score.h"


//============================================================================
//  Class: Score
//============================================================================
Score::Score()
{
  points=0;
}

void Score::reset_score()
{
  points=0;
}

void Score::add_points(int new_points)
{
  points += new_points;
}

std::string Score::get_score()
{
  std::stringstream stream;
  std::string text;
  stream << points;
  stream >> text; 
  return text;
}

int Score::return_score()
{
  return points;
}

void Score::show()
{/*
  score = TTF_RenderText_Solid( scoreFont, get_score().c_str(), textColor );
  apply_surface(0,0,score, screen);
 */
  Sprite animation;
  animation.show_score(get_score().c_str());
}
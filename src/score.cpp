


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
#include <iostream>
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
  name="";
  scoreFont = NULL ;

  //Load player scoreFont
  scoreFont = TTF_OpenFont("img/arial.ttf",28);

  
}

Score::Score(const Score& other)
{
  this->points=other.points;
  this->name=other.name;
  this->scoreFont=other.scoreFont;
 
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
std::string Score::return_name()
{
  return name;
}
void Score::set_score(int new_points)
{
  points=new_points;
}
void Score::set_name(std::string new_name)
{
  name=new_name;
}

void Score::show(SDL_Surface* screen)
{
  SDL_Surface* score;
  score = TTF_RenderText_Solid( scoreFont, get_score().c_str(), {0,0,0,0} );
  apply_surface(0,0,score, screen);
}


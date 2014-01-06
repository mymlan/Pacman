
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
class Score : public Sprite
{
private:
  int points=0;
  std::string name="";
  TTF_Font *scoreFont;
public:
  Score();
  Score(const Score&);
  //Score(const Score& other) : points(other.points), name(other.name) {}
  Score& operator=(const Score& other) {
     
 this->points = other.points;
   
    this->name = other.name; 
    return *this;
  }
  void reset_score();
  void add_points(int);
  std::string get_score(); // return score as string
  void set_score(int);
  void set_name(std::string);
  void show(SDL_Surface*);
  int return_score(); // returns score as int
  std::string return_name();
  // static bool sortingfunction( Score, Score) ;
   bool operator< (const Score &other) const {
     return other.points < points;
   }
};

#endif

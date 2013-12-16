
//============================================================================
// Name        : ghost.h
// Author      : Benjamin, Ingrid, Jonatan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================

#ifndef GHOST_H
#define GHOST_H



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
#include "pacman.h"

//================================== GHOST ============================================================== 
class Ghost
{
protected:
  //if ghost crashes into a wall it will change direction, otherwise will keep going.
  bool crashed_;

//The collission box of the ghost
  SDL_Rect box;

  //The velocity of the ghost
  int xVel, yVel;

  //Angry or scare ghost. false is  angry, true is scared
  bool scared_;


  //1 is left, 2 is right, 3 is up, and 4 is down. 0 will be the starting value, meaning the ghost hasn't found out where pacman is
  int first_way_to_pacman_;
  int second_way_to_pacman_;
public:
  Ghost() = default;
  
  //Moves the ghost
  void move(std::vector<SDL_Rect>);
  
  
  SDL_Rect get_box();
  
  //use reverse_direction when ghost toggles scared_
  void reverse_direction();
 
  //Sets Ghost position to startposition
  virtual void get_home() = 0;
  
  //Returns if ghost is scared/angry
  bool is_scared();
  
  //Switches ghost between chase and flee states
  void change_mood();

 
};



class Ghost1 : public Ghost
{
public:
 //Finds out how to move to Pacman. Seek sets the "first and second way to pacman" member units.
  void seek(class Pacman);

  //Initializes the variables
  Ghost1();

  void get_home();  

  //Shows the ghost on the screen
  void show();

 //Looks for checkpoints, 
  bool is_checkpoint(std::vector<SDL_Rect>, Pacman);

  //If the ghost finds a checkpoint, it reorients. uses is_checkpoint?
  void do_if_checkpoint(std::vector<SDL_Rect>, Pacman);


};


//The second ghost
class Ghost2 : public Ghost  //this is a whimsy  ghost, it moves in random directions.
{
public:
  void seek();

  Ghost2();

  void get_home();

  //Shows the ghost on the screen
  void show();


//Looks for checkpoints
  bool is_checkpoint(std::vector<SDL_Rect>);

//If the ghost finds a checkpoint, it reorients. uses is_checkpoint?
  void do_if_checkpoint(std::vector<SDL_Rect>);

};

//The third ghost
class Ghost3 : public Ghost //this ghost mixes up the first and second most desirable directions towards pacman
{
public:
  void seek(Pacman paccy);

  Ghost3();

  void get_home();

  //Shows the ghost on the screen
  void show();
  
  //Looks for checkpoints
  bool is_checkpoint(std::vector<SDL_Rect>, Pacman);

 //If the ghost finds a checkpoint, it reorients. uses is_checkpoint
  void do_if_checkpoint(std::vector<SDL_Rect>, Pacman);

 
};


#endif

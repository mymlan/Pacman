
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
class Ghost : public Sprite
{

protected:
  //keeps track of previous direction, helps the ghosts from getting stuck.
   int crashed_;
//The collission box of the ghost
  SDL_Rect box;
  //The velocity of the ghost
  int xVel, yVel;
//The attributes of the Pacman
  const int GHOST_WIDTH  {30};
  const int GHOST_HEIGHT {29};
  //Angry or scare ghost. false is  angry, true is scared
  bool scared_;
  //1 is left, 2 is right, 3 is up, and 4 is down. 0 will be the starting value, meaning the ghost hasn't found out where pacman is
  int first_way_to_pacman_;
  int second_way_to_pacman_;

public:
  
  //Returns if ghost is scared/angry
  bool is_scared();
  //Switches ghost between chase and flee states
  void change_mood();
//use reverse_direction when ghost toggles scared_
  void reverse_direction();
  void show();
  //Moves the ghost
  void move(std::vector<SDL_Rect>); 
  bool is_checkpoint(std::vector<SDL_Rect>, class Pacman);
  SDL_Rect get_box();

//Sets Ghost position to startposition
  virtual void get_home() = 0;
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
  //  void show();

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
  // void show();

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
  //  void show();

 //If the ghost finds a checkpoint, it reorients. uses is_checkpoint
  void do_if_checkpoint(std::vector<SDL_Rect>, Pacman);

 
};


#endif

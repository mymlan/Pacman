
//============================================================================
// Name        : timer.cpp
// Author      : Benjamin, Ingrid, Jonatan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================


#ifndef TIMER_H
#define TIMER_H



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




//========================================= TIMER ===============================================
class Timer
{
private:
  //The clock time when the timer started
  int startTicks;
  
  //The ticks stored when the timer was paused
  int pausedTicks;
  
  //The timer status
  bool paused;
  bool started;
  int FRAMES_PER_SECOND{20};
  
public:
  //Initializes variables
  Timer();
  
  //The various clock actions
  void start();
  void stop();
  void pause();
  void unpause();
  
  //Gets the timer's time
  int get_ticks();
  
  //Checks the status of the timer
  bool is_started();
  bool is_paused();

  void delay_game();
 
};


#endif

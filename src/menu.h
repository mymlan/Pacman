
//============================================================================
// Name        : menu.h
// Author      : Benjamin, Ingrid, Jonatan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================

#ifndef MENU_H
#define MENU_H


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


//========================================== MENU ==============================================

class Menu : public Sprite
{
protected:
  SDL_Rect button;
  std::string message_;
  SDL_Surface *textpekare;
  TTF_Font *Font;
  SDL_Color color;
  SDL_Surface *screen {NULL};
SDL_Surface *header {NULL};

  //The attributes of the Buttons
  const int BUTTON_WIDTH {220};
  const int BUTTON_HEIGHT {40};

public:
  virtual void show(SDL_Surface*);
  Menu();
  // Menu(std::string filename);//: new Sprite (std::string filename){}
  virtual ~Menu();
};


//========================================== START ==============================================

class Start : public Menu
{

private:
  bool start;


  SDL_Rect clipsStartscr;
  SDL_Rect clipsInfopanel;
  
  const int MAP_WIDTH{640};
  //int INFOPANEL_WIDTH;
 //The attributes of the Infopanel
  const int INFOPANEL_WIDTH {40};
  const int INFOPANEL_HEIGHT {480};
  const int SCREEN_HEIGHT{480};
 public:
  Start(int x, int y, std::string text);
  ~Start();
  void show(SDL_Surface*) const;
  void show_infopanel(SDL_Surface*) const;
  void handle_input(bool &proceed, bool &quit, SDL_Event);
  bool is_start();
  void change_start();
  void set_clips();
};

//========================================== BUTTON ==============================================
class Button : public Menu
{
public:
  ~Button();
  Button(int x, int y, std::string text);

  void show(SDL_Surface*) const ;
  void show(int x, int y, const char* header,SDL_Surface*) const;
 private:
  SDL_Surface *textpekare;


};


//====================================== HIGHSCORE_SCREEN=============================================


class Highscore_screen : public Menu
{
 private:
  bool pause_;
  
 public:
  ~Highscore_screen();
  Highscore_screen(int x, int y, std::string text);
  void show(SDL_Surface*) const;
  // void show(int x, int y, const char* header) const;
  bool is_paused() const;
  void change_pause();
};


//========================================== END_GAME =============================================


class End_game : public Menu
{
 public:
  ~End_game();
  End_game();
  void show(SDL_Surface*) const;
  // void show(int x, int y, const char* header) const;

};





#endif

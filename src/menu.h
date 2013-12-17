
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

class Menu
{
protected:
  SDL_Rect button;
  std::string message_;

public:
  virtual void show() const = 0;
  virtual ~Menu() = default;
};


class Start : public Menu
{
public:
  void show() const;
  void show_infopanel() const;
  bool is_start();
  void change_start();

  void handle_input(bool &proceed, bool &quit);

  Start(int x, int y, std::string text);
  ~Start() = default;

private:
  bool start;
};


class Button : public Menu
{
public:
  ~Button()=default;
  Button(int x, int y, std::string text);

  void show() const;
};


class Highscore_screen : public Menu
{
 private:
  bool pause_;
  
 public:
  ~Highscore_screen() = default;
  Highscore_screen(int x, int y, std::string text);
  void show() const;
  bool is_paused() const;
  void change_pause();

};

class End_game : public Menu
{
 public:
  ~End_game() = default;
  End_game();
  void show() const;



};





#endif

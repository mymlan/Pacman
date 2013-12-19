
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
  TTF_Font *Font;
public:
  //virtual void show() const = 0;
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
  ~Start();
  void set_clips();
  
private:
  bool start;
  SDL_Surface *textpekare;

  SDL_Rect clipsStartscr;
  SDL_Rect clipsInfopanel;
  
  
};


class Button : public Menu
{
public:
  ~Button();
  Button(int x, int y, std::string text);

  void show() const = delete;
  void show(int x, int y, const char* header) const;
 private:
  SDL_Surface *textpekare;
};


class Highscore_screen : public Menu
{
 private:
  bool pause_;
  
 public:
  ~Highscore_screen();
  Highscore_screen(int x, int y, std::string text);
  void show() const = delete;
  void show(int x, int y, const char* header) const;
  bool is_paused() const;
  void change_pause();
};

class End_game : public Menu
{
 public:
  ~End_game();
  End_game();
  void show() const = delete;
  void show(int x, int y, const char* header) const;

};





#endif

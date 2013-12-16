//============================================================================
// Name        : Sprite.h
// Author      : Benjamin, Ingrid, Jonatan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================
#ifndef SPRITE_H
#define SPRITE_H

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
#include "food.h"


//Screen attributes
extern const int SCREEN_WIDTH ; //640;
extern const int SCREEN_HEIGHT ;
extern const int SCREEN_BPP ;

//Map attributes
extern const int MAP_WIDTH ;

//The frame rate
extern const int FRAMES_PER_SECOND ;

//The attributes of the Pacman
extern const int PACMAN_WIDTH ;
extern const int PACMAN_HEIGHT ;

//the directions of the pacman
extern const int PACMAN_RIGHT ;
extern const int PACMAN_LEFT ;
extern const int PACMAN_UP ;
extern const int PACMAN_DOWN ;

//The attributes of the Buttons
extern const int BUTTON_WIDTH ;
extern const int BUTTON_HEIGHT ;

//The attributes of the Infopanel
extern const int INFOPANEL_WIDTH;
extern const int INFOPANEL_HEIGHT;

//The surfaces
extern SDL_Surface *pacman ;
extern SDL_Surface *screen ;
extern SDL_Surface *ghost ;
extern SDL_Surface *ghost2 ;
extern SDL_Surface *ghost3 ;
extern SDL_Surface *menu ;
extern SDL_Surface *score ;
extern SDL_Surface *startup;

extern SDL_Surface *food ;
extern SDL_Surface *special_food ;
extern SDL_Surface *text ;
extern SDL_Surface *highscore ;
extern SDL_Surface *checkpoint ;

//The event structure
extern SDL_Event event;


//The areas of the pacmansheet
extern SDL_Rect clipsRight[ 2 ];
extern SDL_Rect clipsLeft[ 2 ];
extern SDL_Rect clipsDown[ 2 ];
extern SDL_Rect clipsUp[ 2 ];
extern SDL_Rect clipsStartscr[ 1 ];
extern SDL_Rect clipsInfopanel[ 1 ];

//The font
extern TTF_Font *scoreFont ;
extern TTF_Font *headerFont;
extern TTF_Font *infoFont;

//The color of the font
extern SDL_Color textColor ;
extern SDL_Color headerColor ;







//============================================================================
// Sprite 
//============================================================================

class Sprite
{
public:
  SDL_Surface *load_image( std::string filename );
  void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
  void set_clips();
  bool check_collision( SDL_Rect A, SDL_Rect B );
  
  //Initialize and setup screen
  bool init();
  bool init(SDL_Surface* screen);  //New function

  bool load_files();

  //Draw
  void showlife(int lives);
  void show_pacman(int x, int y, int status, int frame);
  void show_ghost(int x, int y, SDL_Surface*);
  void show_score(const char* score);
  

  void show_start_background();
  void show_infopanel(const char* header);
  void show_button(int x, int y, const char* header);
  void show_highscore(int x, int y);

  void show_food(int x, int y, bool eaten);
  void show_all_food(std::vector<class Food> food_vector);
  void show_special_food(int x,int y, bool eaten);
  void show_walls(std::vector<SDL_Rect> maze);
  void show_one_wall(SDL_Rect wall); 
  void fill_screen_white();



  //Update screen
  int update_screen();



  void clean_up();

};



#endif

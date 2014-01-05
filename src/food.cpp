//============================================================================
// Name        : food.cpp
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
#include "food.h"
#include "sprite.h"


//============================================================================
//  FOOD
//============================================================================

Food::Food(int x_cord, int y_cord)
{
  bool eaten_=false;
 
  //Initialize the offsets
  box.x = x_cord;
  box.y = y_cord;

  //Set the foods dimensions
  box.w = 29;
  box.h = 30;
 
  //The image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized surface that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = IMG_Load("img/food2.bmp");

  //If the image loaded
  if( loadedImage != NULL )
    {
      //Create an optimized surface
      optimizedImage = SDL_DisplayFormat(loadedImage);

      //Free the old surface
      SDL_FreeSurface( loadedImage );

      //If the surface was optimized
      if( optimizedImage != NULL )
        {
	  //Color key surface
	  SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }  
  ytpekare =  optimizedImage; // * ??

  
}

bool Food::eaten()
{
  return eaten_;
}

void Food::was_eaten()
{
  eaten_=true;
}

void Food::show(SDL_Surface* screen)  // = delete? /ingrid
{
  if (!eaten_)
    {
      std::cout<<"like someboody"<<std::endl;
      apply_surface(box.x,box.y,ytpekare, screen);
      std::cout<<"genom"<<std::endl;
    }
}

//Returns SDL-object of ghost
SDL_Rect Food::get_box()
{
  return box;
}

void Food::show_all_food(std::vector<Food> food_vector, SDL_Surface* screen)
{
  for (std::vector<Food>::iterator it = food_vector.begin() ; it != food_vector.end(); ++it)
    {
      (*it).show(screen);
    }
}

//============================================================================
//  Class: Special_Food
//============================================================================
Special_Food::Special_Food(int x_cord, int y_cord)
{
  bool eaten_=false;

  //Initialize the offsets
  box.x = x_cord;
  box.y = y_cord;

  //Set the foods dimensions
  box.w = 29;    //we should change the global constants names PACMAN_WIDTH to CHARACTER_WIDTH
  box.h = 30;

  
  //The image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized surface that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = IMG_Load("img/special_food.bmp" );

  //If the image loaded
  if( loadedImage != NULL )
    {
      
      //Create an optimized surface
      optimizedImage = SDL_DisplayFormat( loadedImage );
     
      //Free the old surface
      SDL_FreeSurface( loadedImage );
      
      //If the surface was optimized
      if( optimizedImage != NULL )
        {
	  //Color key surface
	  SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }  
  ytpekare =  optimizedImage;
  
  
}

void Special_Food::was_eaten()
{
  eaten_=true;
}

bool Special_Food::eaten()
{
  return eaten_;
}

void Special_Food::show(SDL_Surface* screen)
{
  if (!eaten_)
    {
      apply_surface(box.x,box.y,ytpekare, screen);
    }
}

void Special_Food::show_all_special_food(std::vector<Special_Food> special_food_vector, SDL_Surface* screen)
{
  for (std::vector<Special_Food>::iterator it = special_food_vector.begin() ; it != special_food_vector.end(); ++it)
    {
      (*it).show(screen);
    }
}

//Returns SDL-object of ghost
SDL_Rect Special_Food::get_box()
{
  return box;
}



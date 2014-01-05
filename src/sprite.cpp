//============================================================================
// Name        : sprite.cpp
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
#include "sprite.h"



//============================================================================
// Constructor 
//============================================================================
/*Sprite::Sprite(std::string filename)
  
{
  //The image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized surface that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = IMG_Load( filename.c_str() );

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
*/

Sprite::Sprite()
: ytpekare(0)
, MAP_WIDTH(0)
, SCREEN_HEIGHT(0)
, SCREEN_WIDTH(0)
{}

Sprite::Sprite(const Sprite& f)
: ytpekare(0)
, MAP_WIDTH(0)
, SCREEN_HEIGHT(0)
, SCREEN_WIDTH(0)
{
	ytpekare = SDL_ConvertSurface(f.ytpekare, f.ytpekare->format, f.ytpekare->flags);
}

Sprite::~Sprite()
{
  //Free the surface
  SDL_FreeSurface( ytpekare );
 

  
  

}



//============================================================================
// Images 
//============================================================================
 
// Ändrar vi till 2 argument: SDL_Surface* destination, SDL_Rect* clip = NULL
// så lär vi ändra på massor med ställen!

void Sprite::apply_surface( int x, int y, SDL_Surface* ytpekare, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Var tidigare
    //  offset.x = box.x;
    //  offset.y = box.y;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( ytpekare, clip, destination, &offset ); //Har tagit bort source som andraargument
    //  SDL_BlitSurface( ytpekare, source, clip, destination, &offset );

}



//============================================================================
//  Collision
//============================================================================



bool Sprite::check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}


x2//============================================================================
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
#include "food.h"


/*
//Screen attributes
const int SCREEN_WIDTH = 1000; //640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Map attributes
const int MAP_WIDTH = 640;

//The frame rate
const int FRAMES_PER_SECOND = 20;

//The attributes of the Pacman
const int PACMAN_WIDTH = 30;
const int PACMAN_HEIGHT = 29;

//the directions of the pacman
const int PACMAN_RIGHT = 0;
const int PACMAN_LEFT = 1;
const int PACMAN_UP = 2;
const int PACMAN_DOWN = 3;

//The attributes of the Buttons
const int BUTTON_WIDTH = 220;
const int BUTTON_HEIGHT = 40;

//The attributes of the Infopanel
const int INFOPANEL_WIDTH=40;
const int INFOPANEL_HEIGHT=480;



//The surfaces
SDL_Surface *pacman = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *ghost = NULL;
SDL_Surface *ghost2 = NULL;
SDL_Surface *ghost3 = NULL;
SDL_Surface *menu = NULL;
SDL_Surface *score = NULL;
SDL_Surface *startup=NULL;

SDL_Surface *food = NULL;
SDL_Surface *special_food = NULL;
SDL_Surface *text = NULL;
SDL_Surface *highscore = NULL;
SDL_Surface *checkpoint = NULL;




//The event structure
SDL_Event event;


//The areas of the pacmansheet
SDL_Rect clipsRight[ 2 ];
SDL_Rect clipsLeft[ 2 ];
SDL_Rect clipsDown[ 2 ];
SDL_Rect clipsUp[ 2 ];
SDL_Rect clipsStartscr[ 1 ];
SDL_Rect clipsInfopanel[ 1 ];

//The font
TTF_Font *scoreFont = NULL;
TTF_Font *headerFont= NULL;
TTF_Font *infoFont=NULL;
TTF_Font *inputFont=NULL;

//The color of the font
SDL_Color textColor = {0,0,0,0};
SDL_Color headerColor = {255,255,0,0};
SDL_Color infoColor = {};
*/



/*
//============================================================================
// Initialize
//============================================================================
void Sprite::initialize()
{
//Screen attributes
  const int SCREEN_WIDTH {1000}; //640;
  const int SCREEN_HEIGHT {480};
  const int SCREEN_BPP  {32};

//Map attributes
  const int MAP_WIDTH {640};

//The frame rate
  const int FRAMES_PER_SECOND {20};

//The attributes of the Pacman
  const int PACMAN_WIDTH  {30};
  const int PACMAN_HEIGHT {29};

//the directions of the pacman
  const int PACMAN_RIGHT {0};
  const int PACMAN_LEFT {1};
  const int PACMAN_UP {2};
  const int PACMAN_DOWN {3};

  //The attributes of the Buttons
  const int BUTTON_WIDTH {220};
  const int BUTTON_HEIGHT {40};

  //The attributes of the Infopanel
  const int INFOPANEL_WIDTH {40};
  const int INFOPANEL_HEIGHT {480};

  //SDL_Surface *pacman = NULL;
  SDL_Surface *screen = NULL;
  SDL_Surface *ghost = NULL;
  SDL_Surface *ghost2 = NULL;
  SDL_Surface *ghost3 = NULL;
  SDL_Surface *menu = NULL;
  SDL_Surface *score = NULL;
  SDL_Surface *startup=NULL;

  SDL_Surface *food = NULL;
  SDL_Surface *special_food = NULL;
  SDL_Surface *text = NULL;
  SDL_Surface *highscore = NULL;
  SDL_Surface *checkpoint = NULL;

  //The event structure
  SDL_Event event;


  //The areas of the pacmansheet
  SDL_Rect clipsRight[ 2 ];
  SDL_Rect clipsLeft[ 2 ];
  SDL_Rect clipsDown[ 2 ];
  SDL_Rect clipsUp[ 2 ];
  SDL_Rect clipsStartscr[ 1 ];
  SDL_Rect clipsInfopanel[ 1 ];

  //The font
  TTF_Font *scoreFont = NULL;
  TTF_Font *headerFont= NULL;
  TTF_Font *infoFont=NULL;
  TTF_Font *inputFont=NULL;

  //The color of the font
  SDL_Color textColor = {0,0,0,0};
  SDL_Color headerColor = {255,255,0,0};

 
}
*/

//============================================================================
// Constructor 
//============================================================================
Sprite::Sprite(std::string filename)
  
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

  
  *ytpekare =  optimizedImage;

}




//============================================================================
// Images 
//============================================================================


 


void Sprite::apply_surface( SDL_Surface* destination, SDL_Rect* clip )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = box.x;
    offset.y = box.y;

    //Blit
    SDL_BlitSurface( ytpekare, source, clip, destination, &offset );

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



//============================================================================
//  Initilizing  SDL and files
//============================================================================


bool Sprite::init(SDL_Surface* screen, std::string caption)
{
//Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
 

 //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( caption.c_str(), NULL );
    
      //Initialize SDL_ttf
    if(TTF_Init() == -1)
      {
	return false;
      }

    //If everything initialized fine
    return true;

}


bool Sprite::load_files()
{
    //Load the Pacman image
  pacman = load_image( "img/Pacman.bmp" ); //

    //If there was a problem in loading the Pacman
    if( pacman == NULL )
    {
   
        return false;
    }
   
    //Load the ghost image
    ghost = load_image( "img/ghost-picture.bmp" );
    ghost2 = load_image( "img/ghost-picture2.bmp" );

    ghost3 = load_image( "img/ghost-picture3.bmp" );
    //If there was a problem in loading the ghost picture
    if( ghost == NULL || ghost2 == NULL || ghost3 == NULL)

      {
	return false;
      }
    

    //Load the foods image
    food = load_image( "img/food2.bmp" );

    //If there was a problem in loading the food picture
    if( food == NULL)
      {
        return false;
      }
  /*  
    //load the checkpoint image, only for testing. The checkpoints shall be invisible
    checkpoint = load_image( "img/checkpoint.bmp" );
    
    //If there was a problem in loading the checkpoint picture
    if( checkpoint == NULL)
      {
        return false;
      }
  */ 



 //Load the menu image
    menu = load_image( "img/pingvin.png" );

    //If there was a problem in loading the ghost picture
    if( ghost == NULL)
      {
	return false;
      }

    




    //Load Special_Food
    special_food = load_image( "img/special_food.bmp" );
    if (special_food ==NULL)
      {
	return false;
      }
//Load the startup image
    startup = load_image( "img/startup.bmp" );

    //If there was a problem in loading the startup picture
    if( startup == NULL)
      {
        return false;
      }
    

    //If everything loaded fine
    return true;
}






void Sprite::show_score(const char* points)
{
  score = TTF_RenderText_Solid( scoreFont, points, textColor );
  apply_surface(0,0,score, screen);
}


void Sprite::show_infopanel(const char* header)
{
  for (int i=0; i<=8; i++)
    { 

    apply_surface( (MAP_WIDTH+i*INFOPANEL_WIDTH), 0, startup, screen, &clipsInfopanel[0] );
  
    }

  text = TTF_RenderText_Solid( headerFont, header, headerColor );
  apply_surface(660, 30,text, screen); 
}





//============================================================================
//  Memory release
//============================================================================

Sprite::~Sprite()
{
  //Free the surface
  SDL_FreeSurface( ytpekare );
 

  
  //Quit SDL
  SDL_Quit();

}

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
#include "food.h"



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

//The color of the font
SDL_Color textColor = {0,0,0,0};
SDL_Color headerColor = {255,255,0,0};
SDL_Color infoColor = {};




//============================================================================
// Images 
//============================================================================


SDL_Surface * Sprite::load_image( std::string filename )
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

    //Return the optimized surface
    return optimizedImage;
}

void Sprite::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );

}

void Sprite::set_clips()
{
    //Clip the sprites
    clipsRight[ 0 ].x = 0;
    clipsRight[ 0 ].y = 0;
    clipsRight[ 0 ].w = PACMAN_WIDTH;
    clipsRight[ 0 ].h = PACMAN_HEIGHT;

    clipsRight[ 1 ].x = 0;
    clipsRight[ 1 ].y = PACMAN_HEIGHT;
    clipsRight[ 1 ].w = PACMAN_WIDTH;
    clipsRight[ 1 ].h = PACMAN_HEIGHT;

    clipsDown[ 0 ].x = PACMAN_WIDTH;
    clipsDown[ 0 ].y = 0;
    clipsDown[ 0 ].w = PACMAN_WIDTH;
    clipsDown[ 0 ].h = PACMAN_HEIGHT;

    clipsDown[ 1 ].x = PACMAN_WIDTH ;
    clipsDown[ 1 ].y = PACMAN_HEIGHT;
    clipsDown[ 1 ].w = PACMAN_WIDTH;
    clipsDown[ 1 ].h = PACMAN_HEIGHT;
    
    clipsLeft[ 0 ].x = PACMAN_WIDTH * 2 ;
    clipsLeft[ 0 ].y = 0 ;
    clipsLeft[ 0 ].w = PACMAN_WIDTH;
    clipsLeft[ 0 ].h = PACMAN_HEIGHT;

    clipsLeft[ 1 ].x = PACMAN_WIDTH * 2;
    clipsLeft[ 1 ].y = PACMAN_HEIGHT;
    clipsLeft[ 1 ].w = PACMAN_WIDTH;
    clipsLeft[ 1 ].h = PACMAN_HEIGHT;

    clipsUp[ 0 ].x = PACMAN_WIDTH * 3;
    clipsUp[ 0 ].y = 0;
    clipsUp[ 0 ].w = PACMAN_WIDTH;
    clipsUp[ 0 ].h = PACMAN_HEIGHT;

    clipsUp[ 1 ].x = PACMAN_WIDTH * 3;
    clipsUp[ 1 ].y = PACMAN_HEIGHT;
    clipsUp[ 1 ].w = PACMAN_WIDTH;
    clipsUp[ 1 ].h = PACMAN_HEIGHT;

    clipsStartscr[ 0 ].x = 0;
    clipsStartscr[ 0 ].y = 0;
    clipsStartscr[ 0 ].w = MAP_WIDTH;
    clipsStartscr[ 0 ].h = SCREEN_HEIGHT;

    clipsInfopanel[ 0 ].x = MAP_WIDTH;
    clipsInfopanel[ 0 ].y = 0;
    clipsInfopanel[ 0 ].w = INFOPANEL_WIDTH;
    clipsInfopanel[ 0 ].h = INFOPANEL_HEIGHT;

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


bool Sprite::init()
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
    SDL_WM_SetCaption( "Pacman", NULL );

    //Initialize SDL_ttf
    if(TTF_Init() == -1)
      {
	return false;
      }

    //If everything initialized fine
    return true;
}

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

    //Load  headerFont
    headerFont = TTF_OpenFont("img/xtrusion.ttf",55);

    if (headerFont ==NULL)
      {
	return false;
      }

 //Load infoFont
    infoFont = TTF_OpenFont("img/KarmaFuture.ttf",22);

    if (infoFont ==NULL)
      {
	return false;
      }


  //Load player scoreFont
   scoreFont = TTF_OpenFont("img/arial.ttf",28);

    if (scoreFont ==NULL)
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

void Sprite::showlife(int lives)
{
if (lives==2)
    {
      apply_surface(910,440 ,pacman, screen, &clipsLeft[1] );
       apply_surface(910+PACMAN_WIDTH,440 ,pacman, screen, &clipsLeft[1] );
       apply_surface(910+2*PACMAN_WIDTH,440 ,pacman, screen, &clipsLeft[1] );
    }   
 else if (lives==1)
    {

      apply_surface(910+PACMAN_WIDTH,440 ,pacman, screen, &clipsLeft[1] );
      apply_surface(910+2*PACMAN_WIDTH,440 ,pacman, screen, &clipsLeft[1] );
    }
    
 else if( lives==0)
   {
     apply_surface(910+2*PACMAN_WIDTH,440 ,pacman, screen, &clipsLeft[1] );
   }
}

void Sprite::show_pacman(int x, int y, int status, int frame)
{
 if( status == PACMAN_RIGHT )
    {
        apply_surface(x, y, pacman, screen, &clipsRight[ frame] );
    }
    else if( status == PACMAN_LEFT )
    {
        apply_surface( x, y, pacman, screen, &clipsLeft[ frame ] );
    }
    else if( status == PACMAN_UP)
      {
	apply_surface (x, y, pacman, screen, &clipsUp[ frame ]);
      }

 else if( status == PACMAN_DOWN)
      {
	apply_surface ( x, y, pacman , screen, &clipsDown[ frame ]);
      }
}


void Sprite::show_ghost(int x, int y, SDL_Surface* ghost)
{
  apply_surface(x,y,ghost,screen);
}


void Sprite::show_score(const char* points)
{
  score = TTF_RenderText_Solid( scoreFont, points, textColor );
  apply_surface(0,0,score, screen);
}

void Sprite::show_start_background()
{
 apply_surface(0,0,startup,screen, &clipsStartscr[0]); 
 std::cout << "Hey Big Boy/Girl!!!" <<std::endl;
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


void Sprite::show_button(int x, int y, const char* header)
{
  text = TTF_RenderText_Solid( infoFont, header , headerColor );
  apply_surface(x, y,text, screen);  
}

void Sprite::show_highscore(int x, int y)
{
  apply_surface(x,y,score,screen);
}
//***************************************************

void Sprite::show_food(int x, int y, bool eaten)
{
  if (!eaten)
    {
      apply_surface(x,y,food, screen);
    }
}
  
void Sprite::show_all_food(std::vector<Food> food_vector)
{
  for (std::vector<Food>::iterator it = food_vector.begin() ; it != food_vector.end(); ++it)
    {
      (*it).show();
    }
}
	

void Sprite::show_all_special_food(std::vector<Special_Food> special_food_vector)
{
  for (std::vector<Special_Food>::iterator it = special_food_vector.begin() ; it != special_food_vector.end(); ++it)
    {
      (*it).show();
    }
}

void Sprite::show_special_food(int x,int y, bool eaten)
{
 if (!eaten)
    {
      apply_surface(x,y,special_food, screen);
    }
}
//************************************************************************
void Sprite::show_walls(std::vector<SDL_Rect> maze)
{
  for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
    {
      SDL_FillRect( screen, &(*it), SDL_MapRGB( screen->format, 0x00, 0x00, 0xEF) );
    }
}

void Sprite::show_one_wall(SDL_Rect wall)
{
  SDL_FillRect( screen, &wall, SDL_MapRGB( screen->format, 0xAF, 0x00, 0x00) );
}

 int Sprite::update_screen()
 {
   if( SDL_Flip( screen ) == -1 )
     {
       return 1;
     }
 }


void Sprite::fill_screen_white()
{
  SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
}
	

//============================================================================
//  Memory release
//============================================================================


void Sprite::clean_up()
{
    //Free the surface
    SDL_FreeSurface( pacman );
    SDL_FreeSurface( ghost );
    SDL_FreeSurface( ghost2 );   //prova ta bort vid problem med ghost
    SDL_FreeSurface( score );
    SDL_FreeSurface( startup);
    SDL_FreeSurface( menu);
              
    //Quit SDL
    SDL_Quit();
}

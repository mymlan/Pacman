//============================================================================
// Name        : menu.cpp
// Author      : Benjamin, Ingrid, Jonathan, Lina, Mikaela & Minh
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
#include "menu.h"
#include "sprite.h"

Menu::~Menu()
{
}

//========================= START ==============================================

Start::Start(int x, int y, std::string text)
{
  //Initialize
  button.x = x;
  button.y = y;
  
  message_ = text;
  start = true;

  //Set dimension
  button.w = BUTTON_WIDTH;
  button.h = BUTTON_HEIGHT;

  //Load  Font
  Font = TTF_OpenFont("img/xtrusion.ttf",55);
  textpekare = NULL; 

  //The image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized surface that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = IMG_Load( "img/startup.bmp" ); // filename.c_str()

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
  
  ytpekare =  optimizedImage; // * ???
  
  SDL_Rect clipsStartscr[1];
  SDL_Rect clipsInfopanel[1];
}

Start::~Start()
{
  TTF_CloseFont(Font );           
}

void Start::show(SDL_Surface* screen)
{
  apply_surface(0,0,ytpekare,screen); 
}

void Start::show_infopanel(SDL_Surface* screen)
{
 for (int i=0; i<=8; i++)
    { 
      apply_surface( (MAP_WIDTH+i*INFOPANEL_WIDTH), 0, ytpekare, screen ); 
    }
}

void Start::handle_input(bool &proceed, bool &quit, SDL_Event event)
  
{
  if(event.type == SDL_KEYDOWN)
    {
      switch(event.key.keysym.sym)
	{
	case SDLK_s: proceed=true; std::cout<<" Spela!!!" <<std::endl;  break;
	case SDLK_q: quit=true; proceed=true; std::cout << "Game quit" << std::endl ; break;
	}
      change_start();
    }
}

bool Start::is_start()
{
  return start;
}

void Start::change_start()
{
  if(start == true)
    start = false;
  else
    start =true;
}

//====================== BUTTON ==========================================================

Button::~Button()
{
  SDL_FreeSurface( ytpekare );
  TTF_CloseFont( Font );         
}

Button::Button(int x, int y, std::string text)
{
  //Initialize
  button.x = x; 
  button.y = y;
  message_ = text;

 //Set dimension
  button.w = BUTTON_WIDTH;
  button.h = BUTTON_HEIGHT;
  textpekare = NULL;
  //Load Font
  Font = TTF_OpenFont("img/KarmaFuture.ttf",22);

  color = {255,255,0,0};

  //The image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized surface that will be used
  SDL_Surface* optimizedImage = NULL;

  ytpekare =  optimizedImage; // * ?? /Ingrid

}
  
void Button::show(SDL_Surface* screen)
{
  textpekare = TTF_RenderText_Solid( Font, message_.c_str() , color );
  apply_surface(button.x, button.y,textpekare, screen);  
}

void Button::show(int x, int y, const char* header,SDL_Surface* screen)
{
  SDL_Surface* texttest;
  texttest = TTF_RenderText_Solid( Font, header , color );
  apply_surface(button.x, button.y,texttest, screen);
}


//====================== HIGHSCORE_SCREEN ===================================================

Highscore_screen::~Highscore_screen()
{
  TTF_CloseFont( Font );          
}

Highscore_screen::Highscore_screen(int x, int y, std::string text)
{
  //Initialize
  button.x=x;
  button.y=y;
  message_ = text;
  pause_ = true;

  //Set dimension
  button.w = BUTTON_WIDTH;
  button.h = BUTTON_HEIGHT;

  //Load  Font
  Font = TTF_OpenFont("img/xtrusion.ttf",55);
} 

void Highscore_screen::show(SDL_Surface* screen)
{ 
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
	std::cerr << "Fel" << std::endl;
	SDL_Quit();
	exit(1);	
	}

	screen = SDL_SetVideoMode( 1000, 480, 32, SDL_SWSURFACE );
	if( screen == NULL )  {
	
	std::cerr << "Fel" << std::endl;
	SDL_Quit();
	exit(1);
	}

  const char* header = message_.c_str();
  SDL_Surface* texttest;
  texttest = TTF_RenderText_Solid( Font, header , color );
  apply_surface(button.x, button.y,texttest, screen);
}

bool Highscore_screen::is_paused() const
{
  return pause_;
}

void Highscore_screen::change_pause()
{
  if (pause_ == true)
    pause_ = false;
  else
    pause_ = true;
}

//====================== END_GAME ===================================================
End_game::~End_game()
{
  TTF_CloseFont( Font );
}

End_game::End_game()
{

  //Initialize
  button.x=100;
  button.y=10;
  message_="Skriv namn. Enter.";

  //Set dimension
  button.w = BUTTON_WIDTH;
  button.h = BUTTON_HEIGHT;

  //Load  Font
  Font = TTF_OpenFont("img/xtrusion.ttf",55);
}

void End_game::show(SDL_Surface* screen)
{

  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) 
    {
      std::cerr << "Fel" << std::endl;
      SDL_Quit();
      exit(1);	
    }
  screen = SDL_SetVideoMode( 1000, 480, 32, SDL_SWSURFACE );
  if( screen == NULL )  
    {
	
      std::cerr << "Fel" << std::endl;
      SDL_Quit();
      exit(1);
    }

  const char* header = message_.c_str();
  SDL_Surface* texttest;
  texttest = TTF_RenderText_Solid( Font, header , color ); //inputfont headercolor
  apply_surface(button.x, button.y,texttest, screen); 
}


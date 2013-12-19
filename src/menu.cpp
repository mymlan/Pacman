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

//============================================================================
//  Class: Menu
//============================================================================
/*
Menu::Menu(std::string filename)
{
  Sprite::Sprite(filename);
}
*/
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
  loadedImage = IMG_Load( "src/startup.bmp" ); // filename.c_str()

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

}

Start::~Start()
{
  //Free the surface
  SDL_FreeSurface( ytpekare );
 

  //dessa rader under kanske inte ska vara här
  //Close the font that was used
  TTF_CloseFont( inputFont );
             
    
  //Quit SDL_ttf
  TTF_Quit();

  //Quit SDL
  SDL_Quit();
}


void Start::show() const
{
  apply_surface(0,0,ytpekare,screen, &clipsStartscr[0]); 
}


void Start::show_infopanel() const
{
  for (int i=0; i<=8; i++)
    { 
      apply_surface( (MAP_WIDTH+i*INFOPANEL_WIDTH), 0, ytpekare, screen, &clipsInfopanel[0] );
    }

  textpekare = TTF_RenderText_Solid( Font, header, headerColor );
  apply_surface(660, 30,textpekare, screen); 
}


void Start::handle_input(bool &proceed, bool &quit)
  
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

void Start::set_clips()
{
  clipsStartscr[ 0 ].x = 0;
  clipsStartscr[ 0 ].y = 0;
  clipsStartscr[ 0 ].w = MAP_WIDTH;
  clipsStartscr[ 0 ].h = SCREEN_HEIGHT;

  clipsInfopanel[ 0 ].x = MAP_WIDTH;
  clipsInfopanel[ 0 ].y = 0;
  clipsInfopanel[ 0 ].w = INFOPANEL_WIDTH;
  clipsInfopanel[ 0 ].h = INFOPANEL_HEIGHT;

}



//====================== BUTTON ==========================================================

Button::~Button()
{
  //Free the surface
  SDL_FreeSurface( ytpekare );
 

  //dessa rader under kanske inte ska vara här
  //Close the font that was used
  TTF_CloseFont( inputFont );
             
    
  //Quit SDL_ttf
  TTF_Quit();

  //Quit SDL
  SDL_Quit();

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
  //Load infoFont
  infoFont = TTF_OpenFont("img/KarmaFuture.ttf",22);

  if (infoFont ==NULL)
    {
      return false;
    }


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
  
void Button::show() const
{
 
}

void Button::show(int x, int y, const char* header) const
{
  textpekare = TTF_RenderText_Solid( infoFont, header , headerColor );
  apply_surface(x, y,textpekare, screen);  
}


//====================== HIGHSCORE_SCREEN ===================================================

Highscore_screen::~Highscore_screen()
{
  //Free the surface
  SDL_FreeSurface( ytpekare );
 

  //dessa rader under kanske inte ska vara här
  //Close the font that was used
  TTF_CloseFont( inputFont );
             
    
  //Quit SDL_ttf
  TTF_Quit();

  //Quit SDL
  SDL_Quit();

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

  if (Font ==NULL)
    {
      return false;
    }
} 

void Highscore_screen::show() const
{ 
  text = TTF_RenderText_Solid( infoFont, header , headerColor );
  apply_surface(x, y,text, screen);
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
  //Free the surface
  SDL_FreeSurface( ytpekare );
 

  //dessa rader under kanske inte ska vara här
  //Close the font that was used
  TTF_CloseFont( inputFont );
             
    
  //Quit SDL_ttf
  TTF_Quit();

  //Quit SDL
  SDL_Quit();

}

End_game::End_game()
{

  //Initialize
  button.x=400;
  button.y=10;
  message_="You win! Enter highscore!";

  //Set dimension
  button.w = BUTTON_WIDTH;
  button.h = BUTTON_HEIGHT;

  //Load  Font
  Font = TTF_OpenFont("img/xtrusion.ttf",55);

  if (Font ==NULL)
    {
      return false;
    }
}

void End_game::show() const
{
  text = TTF_RenderText_Solid( infoFont, header , headerColor );
  apply_surface(x, y,text, screen); 
}


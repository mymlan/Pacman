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

}

void Start::show() const
{
  Sprite animation;
  animation.show_start_background();
  /* apply_surface(0,0,startup,screen, &clipsStartscr[0]); 
  std::cout << "Hey Big Boy/Girl!!!" <<std::endl;
  //apply_surface(0,0,startup,screen);
  */
 //Show the startbuttons
  /*
  //  SDL_FillRect( screen, &button, SDL_MapRGB( screen->format, 0xEF, 0xEF, 0xEF) );
   for (int i=0; i<=8; i++)
    { 

    apply_surface( (MAP_WIDTH+i*INFOPANEL_WIDTH), 0, startup, screen, &clipsInfopanel[0] );
  
    }
   text = TTF_RenderText_Solid( headerFont, message_.c_str() , headerColor );
   apply_surface(660, 30,text, screen); 
  */
}


void Start::show_infopanel() const
{
  Sprite animation;
  animation.show_infopanel(message_.c_str());
  /*//Show the startbuttons
  
  //  SDL_FillRect( screen, &button, SDL_MapRGB( screen->format, 0xEF, 0xEF, 0xEF) );
   for (int i=0; i<=8; i++)
    { 

    apply_surface( (MAP_WIDTH+i*INFOPANEL_WIDTH), 0, startup, screen, &clipsInfopanel[0] );
  
    }

   text = TTF_RenderText_Solid( headerFont, message_.c_str() , headerColor );
   apply_surface(660, 30,text, screen); 
  */}


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

//====================== BUTTON ==========================================================


Button::Button(int x, int y, std::string text)
{
  //Initialize
  button.x = x; 
  button.y = y;
  message_ = text;

 //Set dimension
  button.w = BUTTON_WIDTH;
  button.h = BUTTON_HEIGHT;
  
}
  
void Button::show() const
{
  Sprite animation;
  animation.show_button(button.x, button.y, message_.c_str());
  /*text = TTF_RenderText_Solid( infoFont, message_.c_str() , headerColor );
  apply_surface(button.x, button.y,text, screen);  
  */
}




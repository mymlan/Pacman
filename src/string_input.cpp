//============================================================================
// Name        : string_input.cpp
// Author      : Benjamin, Ingrid, Jonatan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================


//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>
#include "string_input.h"
#include "sprite.h"



StringInput::StringInput()
{
    //Initialize the string
    str = "";

    //Initialize the surface
    text = NULL;

    //Enable Unicode
    SDL_EnableUNICODE( SDL_ENABLE );
}

StringInput::~StringInput()
{
    //Free text surface
    SDL_FreeSurface( text );

    //Disable Unicodeq
    SDL_EnableUNICODE( SDL_DISABLE );
}

void StringInput::handle_input()
{
  std::cout<< "handleinput"<< std::endl;
  SDL_EnableUNICODE( SDL_ENABLE );
  
  //while(SDL_PollEvent( &event)){
    //If a key was pressed
  if( event.type == SDL_KEYDOWN )
    {
       std::cout<< "jag kom in"<< std::endl;
        //Keep a copy of the current version of the string
        std::string temp = str;

        //If the string less than maximum size
        if( str.length() <= 16 )
        {
	   std::cout<< "fyfan"<< std::endl;
            //If the key is a space
            if( event.key.keysym.unicode == (Uint16)' ' )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
		std::cout<< "space"<< std::endl;
		std::cout<< str<< std::endl;
            }
            //If the key is a number
            else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
		std::cout<< str<< std::endl;
            }
            //If the key is a uppercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
		std::cout<< str<< std::endl;
            }
            //If the key is a lowercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
		std::cout<< str<< std::endl;
            }
        }

        //If backspace was pressed and the string isn't blank
        if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
        {
            //Remove a character from the end
            str.erase( str.length() - 1 );
	    std::cout<< str<< std::endl;
        }

        //If the string was changed
        if( str != temp )
        {
            //Free the old surface
            SDL_FreeSurface( text );

            //Render a new text surface
            text = TTF_RenderText_Solid( inputFont, str.c_str(), textColor );
        }
	}
}
//}
void StringInput::show_centered()
{
  Sprite draw;
  std::cout<<"show centered"<<std::endl;
    //If the surface isn't blank
    if( text != NULL )
    {
        //Show the name
        draw.apply_surface( ( SCREEN_WIDTH - text->w ) / 2, ( SCREEN_HEIGHT - text->h ) / 2, text, screen );
    }
}

std::string StringInput::get_str()
{
  return str;
}













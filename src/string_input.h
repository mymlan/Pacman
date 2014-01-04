//============================================================================
// Name        : string_input.h
// Author      : Benjamin, Ingrid, Jonatan, Lina, Mikaela & Minh
// Version     : 
// Copyright   : 
// Description : Pacman 
//============================================================================

#ifndef STRING_INPUT_H
#define STRING_INPUT_H


//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>

//The key press interpreter
class StringInput
{
    private:
    //The storage string
    std::string str;

    //The text surface
    SDL_Surface *text;

    public:
    //Initializes variables
    StringInput();

    //Does clean up
    ~StringInput();

    //Handles input
    void handle_input(SDL_Event);

    //Shows the message on screen
    void show_centered(SDL_Surface*);

    std::string get_str();

    TTF_Font *inputFont;

};






#endif

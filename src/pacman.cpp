//============================================================================
// Name        : pacman.cpp
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
#include "pacman.h"
#include "sprite.h"
#include "ghost.h"
#include "food.h"
#include "score.h"

//============================================================================
//  Class: Pacman (KOD)
//============================================================================

Pacman::Pacman() // string filename
{  
  //Initialize the offsets
  box.x = 320;
  box.y = 440;

  //Set the Pacman's dimensions
  box.w = PACMAN_WIDTH;
  box.h = PACMAN_HEIGHT;
  MAP_WIDTH=640;
  SCREEN_HEIGHT=480;
  SCREEN_WIDTH=1000;

  //Initialize the velocity
  xVel = 10;
  yVel = 0;
  x = 320;
  y = 440;

  //Initialize the user specified velocity
  goX = 0;
  goY = 0;
  
  //Initialize legit direction
  legitXVel = 0;
  legitYVel = 0;

  //Initialize lives of Pacman
  lives = 2;

  //Initialize animation variables
  frame = 0;
  status = PACMAN_LEFT;

  food_left = 114;
  pacman_has_eaten_special_food = false;

  //The image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized surface that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = IMG_Load("img/newsquare.bmp");

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

int Pacman::reveal_position_x() {
  int position_x{box.x};
  return position_x;
}

int Pacman::reveal_position_y() {
  int position_y{box.y};
  return position_y;
}

int Pacman::life() {
  int life{lives};
  return life;
}

void Pacman::handle_input(SDL_Event event) {
  //If a key was pressed
  if( event.type == SDL_KEYDOWN )
    {
      //Adjust the velocity
      switch( event.key.keysym.sym )
        {
	case SDLK_UP:    goY = -10; goX = 0; break;
	case SDLK_DOWN:  goY =  10; goX = 0; break;
	case SDLK_LEFT:  goX = -10; goY = 0; break;
	case SDLK_RIGHT: goX =  10; goY = 0; break;
        }
    }
}

void Pacman::move(std::vector<SDL_Rect> maze, SDL_Rect wall25) {
  // Try to go where the user last pointed pacman to go
  // This can be used to prepare pacman for turns
  xVel = goX;
  yVel = goY;
  
  //Pacman shouldn't stop moving if he tries to turn a bit too
  //early at a corner  
  if (!tryMoveX(maze, wall25)) {
    //Instead continue with previous direction
    xVel = legitXVel;
    yVel = legitYVel;
    tryMoveX(maze, wall25);
    tryMoveY(maze, wall25);
  }

  // if moving in x is okay, try y
  else if (!tryMoveY(maze, wall25)) {

    xVel = legitXVel;
    yVel = legitYVel;

    tryMoveX(maze, wall25);
    tryMoveY(maze, wall25);
  }

  else {
    // We could move in x and y, store the direction that worked
    legitXVel = xVel;
    legitYVel = yVel;
  }
}

bool Pacman::tryMoveX(std::vector<SDL_Rect> maze, SDL_Rect wall25) {
  //Move pacman left or right
  box.x += xVel;
  
  //Don't let him move out of the map
  if( (box.x < 0) || (box.x + PACMAN_WIDTH > MAP_WIDTH) ) {
      //Move back
      box.x -= xVel;
      return false; // Failed to move
    }
  
  else {
    //Don't let him hit the walls
    for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it) {      
      if( check_collision(box, *it) ) {
	//Move back
	box.x -= xVel;
	return false; // Failed to move
      }
    }
    return true; // Succeeded to move
  }
}

bool Pacman::tryMoveY(std::vector<SDL_Rect> maze, SDL_Rect wall25) {
  //Move pacman up or down
  box.y += yVel;

  //Don't let him move out of the map
  if( (box.y < 0) || (box.y + PACMAN_WIDTH > SCREEN_HEIGHT) ) {
      //Move back
      box.y -= yVel;
      return false;
    }
  
  else {

    //Don't let him hit the walls
    for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it) {
      if( check_collision(box, *it) ) {
	//Move back
	box.y -= yVel;
	return false;
      }
    }
    return true; // Succeeded to move
  }
}

void Pacman::show(SDL_Surface* screen)
{
  //Sprite animation;

  /*
  //If Pacman is moving left
  if( xVel < 0 )
  {
  //Set the animation to left
  status = PACMAN_LEFT;

  //Move to the next frame in the animation
  frame++;
  }
  //If Pacman is moving right
  else if( xVel > 0 )
  {
  //Set the animation to right
  status = PACMAN_RIGHT;

  //Move to the next frame in the animation
  frame++;
  }
  //If pacman is moving up
  else if ( yVel < 0)
  {
  status = PACMAN_UP;
  frame++;
  }
  //if pacman is moving down
  else if (yVel > 0)
  {
  status = PACMAN_DOWN;
  frame ++;
  }
  //If pacman standing
  else
  {
  //Restart the animation
  frame = 0;
  }

  //Loop the animation
  if( frame >= 2 )
  {
  frame = 0;
  }
    
  //Show the pacman
  if( status == PACMAN_RIGHT )
  {
  apply_surface(box.x,box.y, ytpekare , screen, &clipsRight[ frame]);
  }
  else if( status == PACMAN_LEFT )
  {
  apply_surface(box.x,box.y, ytpekare, screen, &clipsLeft[ frame ] );
  }
  else if( status == PACMAN_UP)
  {
  apply_surface (box.x,box.y, ytpekare, screen, &clipsUp[ frame ]);
  }

  else if( status == PACMAN_DOWN)
  {
  apply_surface (box.x,box.y, ytpekare, screen, &clipsDown[ frame ]);
  }
  
  */
  apply_surface(box.x,box.y,ytpekare,screen);
}





//Check if Pacman has no more lives
bool Pacman::game_over()
{
  return (life()==-1);
}


//Collision between
bool Pacman::eat_eaten(Ghost& ghost_object,Score& myScore)
{  
  if (check_collision(box, ghost_object.get_box()))
    {
      if (ghost_object.is_scared())
	{
	  myScore.add_points(1);
	}
      else	  
	{
	  lives=lives-1;
	  get_home();
	}
      ghost_object.get_home();
      return true;
    }
  return false;
}



//Pacman eats food
void Pacman::eat_food(std::vector<Food>& food_vector, Score& myScore) //Food& food_object
{  
  for (std::vector<Food>::iterator it = food_vector.begin() ; it != food_vector.end(); ++it)
    {
      
      if ((check_collision(box, (*it).get_box())) and !(*it).eaten())
	{
	  myScore.add_points(1);
	  (*it).was_eaten();
	  food_left = food_left - 1;
	 
	}
    }
}

//Pacman eats special_food
void Pacman::eat_special_food(std::vector<class Special_Food>& special_food_vector,Score& myScore)
{
  
  for (std::vector<Special_Food>::iterator it = special_food_vector.begin() ; it != special_food_vector.end(); ++it)
    {
      if ((check_collision(box, (*it).get_box())) and !(*it).eaten())
	{
	  myScore.add_points(10);
	  (*it).was_eaten();
	  food_left = food_left - 1;
	  pacman_has_eaten_special_food = true;
	} 
    }  
}


//Returns Pacman to starting position
void Pacman::get_home()
{
  box.x = 320;
  box.y = 440;
}


//Returns true if there is no food left
bool Pacman::no_food_left()
{
  if(food_left == 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}

void Pacman::pacman_change_mood()
{
  pacman_has_eaten_special_food = false;
}

bool Pacman::has_pacman_eaten_special_food()
{
  return pacman_has_eaten_special_food;
}
 
void Pacman::showlife(SDL_Surface* screen)
{
  if (lives==2)
    {
      apply_surface(910,440 ,ytpekare, screen);
      apply_surface(910+PACMAN_WIDTH,440 ,ytpekare, screen);
      apply_surface(910+2*PACMAN_WIDTH,440 ,ytpekare, screen);
    }   
  else if (lives==1)
    {

      apply_surface(910+PACMAN_WIDTH,440 ,ytpekare, screen );
      apply_surface(910+2*PACMAN_WIDTH,440 ,ytpekare, screen );
    }
    
  else if( lives==0)
    {
      apply_surface(910+2*PACMAN_WIDTH,440 ,ytpekare, screen );
    }
}


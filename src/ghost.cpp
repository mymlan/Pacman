//============================================================================
// Name        : ghost.cpp
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
#include "ghost.h"

//============================================================================
//  Class: Ghost
//============================================================================
bool Ghost::is_scared()
{
  return (scared_);
}

void Ghost::change_mood()
{
  if (is_scared())
    {
      scared_=false;
    }
  else
    {
      scared_=true;
    }
  reverse_direction();
}

void Ghost::reverse_direction()
{
  if (first_way_to_pacman_ != 0)
    {
      if (first_way_to_pacman_ == 1 || first_way_to_pacman_ == 3)
	{first_way_to_pacman_ += 1;}
      else
	{first_way_to_pacman_ -= 1;}
    }
  if (second_way_to_pacman_ != 0)
    {
      if (second_way_to_pacman_ == 1 ||second_way_to_pacman_ == 3)
	{second_way_to_pacman_ += 1;}
      else
	{second_way_to_pacman_ -= 1;}
    }

  crashed_ = 0;
}

void Ghost::show(SDL_Surface* screen)
{
  apply_surface(box.x,box.y,ytpekare,screen);
}

void Ghost::move(std::vector<SDL_Rect> maze) //checks collision with walls
{
  
  //Set velocity and direction
  switch(first_way_to_pacman_)
    {
    case 1: yVel = 0; xVel = -10; break; //left
    case 2: yVel = 0; xVel = 10; break;  //right
    case 3: yVel = -10; xVel = 0; break;  //up      y increases downwards
    case 4: yVel = 10; xVel = 0; break; //down
    }

 
  //Move the ghost left or right
  box.x += xVel;


  //If the ghost went too far to the left or right or has collided with the walls
  for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it) //try all the walls
    {
      if( ( box.x < 0 ) || ( box.x + GHOST_WIDTH > MAP_WIDTH ) || ( check_collision( box, *it ) ) )
	{

	  //Move back
	  box.x -= xVel;

	  //go to the second most favorable way to pacman
	  first_way_to_pacman_ = second_way_to_pacman_; 
	  second_way_to_pacman_ = 0;
	}
    }
  
  //Move the ghost up or down
  box.y += yVel;

  //If the square went too far up or down or has collided with the walls
  for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
    {
      if( ( box.y < 0 ) || ( box.y + GHOST_HEIGHT > SCREEN_HEIGHT ) || ( check_collision( box, *it ) ) )
	{
	  //Move back
	  box.y -= yVel;
	  

	  //If we are stuck, set crashed_
	  if(first_way_to_pacman_ == 0 && second_way_to_pacman_ == 0)
	    {
	      crashed_ = true;
	    }
	    
	  //else, go to the second most favorable way to pacman
	  first_way_to_pacman_ = second_way_to_pacman_; 
	  second_way_to_pacman_ = 0;
	}
    }
}

//behöver denna funktion verkligen ta in en pacmanklass???
bool Ghost::is_checkpoint(std::vector<SDL_Rect> checkmaze) //, Pacman paccy) //looks for a checkpoint
{
  //check if ghost is right on top of checkpoint, and not just at the checkpoints corner
  box.x -= xVel;
  box.y -= yVel;
  
  //check for checkpoint collission
  for(std::vector<SDL_Rect>::iterator it = checkmaze.begin() ; it != checkmaze.end(); ++it) //try all the checkpoints
    {
      if( check_collision( box, *it ) )
	{
	  //restore actual position
	  box.x += xVel;
	  box.y += yVel;

	  return true;
	}
    }
 
  //restore actual position
  box.x += xVel;
  box.y += yVel;
  return false;
}

//Returns SDL-object of ghost
SDL_Rect Ghost::get_box()
{
  return box;
}
//-------------- Ghost 1 ----------------------------------

Ghost1::Ghost1()
{
  //Initialize the offsets
  box.x = 0;
  box.y = 0;

  MAP_WIDTH=640;
  SCREEN_HEIGHT=480;
  SCREEN_WIDTH=1000;

  
  //Initialize the seek and destroy directions. first way to pacman is the most desirable way to go.
  first_way_to_pacman_ = 2;
  second_way_to_pacman_ = 4;
  //Initialize the angry or scared mode
  scared_ = false;

  //Initialize crashed
  crashed_ = 24;

  //Set the ghost's dimensions
  box.w = GHOST_WIDTH;   
  box.h = GHOST_HEIGHT;

  //Initialize the velocity
  xVel = 10;
  yVel = 0;

  //The image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized surface that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = IMG_Load("img/ghost-picture.bmp");

  //If the image loaded
  if( loadedImage != NULL )
    {
      //Create an optimized surface
      optimizedImage = SDL_DisplayFormat(ytpekare);

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

//Moves freely, and looks for checkpoints
void Ghost1::do_if_checkpoint( std::vector<SDL_Rect> checkmaze, Pacman paccy ) 
{
  
  if(is_checkpoint(checkmaze, paccy))
    {  
      //make a fresh seek if ghost reaches a checkpoint
      first_way_to_pacman_ = 0;
      second_way_to_pacman_ = 0;
      crashed_ = 0;
      seek(paccy); 
    }
}

//Sets the moving direction towards pacman
void Ghost1::seek(Pacman paccy)
{ 
  /*
  std::cout<<"scared_ : "<<scared_<<std::endl;
  std::cout<<"before seek"<<std::endl;
  std::cout<<"first: "<<first_way_to_pacman_<<std::endl;
  std::cout<<"second: "<<second_way_to_pacman_<<std::endl;

*/
  if (first_way_to_pacman_ == 0 && second_way_to_pacman_ == 0) //if we have tried both directions, get a new one
    {
      //pacman_x and pacman_y are the coordinates of pacman
      int pacman_x{paccy.reveal_position_x()};
      int pacman_y{paccy.reveal_position_y()};
      
      //tries to minimize the distance in the shortest direction first. If pacman is one step to the right and far away at the bottom, the ghost will first go down and then take one step left.
      if( abs(pacman_x - box.x) > abs(pacman_y - box.y) ) //if bigger difference in x than in y, then walk towards pacman i x direction
	{
	  if( pacman_x > box.x ) //if pacman is to the right, go right
	    {first_way_to_pacman_ = 2;}
	  else 
	    {first_way_to_pacman_ = 1;} //else, go left
      
	  if ( pacman_y > box.y ) //if pacman is below the ghost, go downwards
	    {second_way_to_pacman_ = 4;}
	  else
	    {second_way_to_pacman_ = 3;} //else, go up
	}
     
      else
	{
	  if (pacman_y > box.y) //biggest distance is in y direction, so walk in y direction first
	    {first_way_to_pacman_ = 4;}
	  else
	    {first_way_to_pacman_ = 3;}
      
	  if (pacman_x > box.x)
	    {second_way_to_pacman_ = 2;} //go right
	  else 
	    {second_way_to_pacman_ = 1;} //go left
	}

      /*
      std::cout<<"precis efter sokning : "<<std::endl;
      std::cout<<"first: "<<first_way_to_pacman_<<std::endl;
      std::cout<<"second: "<<second_way_to_pacman_<<std::endl;
      */

      if (10*first_way_to_pacman_ + second_way_to_pacman_ == crashed_) //same result for two seeks in a row means we are stuck
	{
	  //randomize a direcion
	  std::cout<<"slumpar"<<std::endl;
	  first_way_to_pacman_ = rand()% 4 + 1;
	}  
      
      
      if (scared_ == true) //if the ghost is scared, reverse the moving direction
	{
	  reverse_direction();
	}
      crashed_ = 10*first_way_to_pacman_ + second_way_to_pacman_;
    }
  /*
  std::cout<<"efter seek: "<<std::endl;
  std::cout<<"first: "<<first_way_to_pacman_<<std::endl;
  std::cout<<"second: "<<second_way_to_pacman_<<"\n"<<std::endl;
*/
}


//Returns ghost to start position
void Ghost1::get_home()
{
  box.x = 0;
  box.y = 0;
}
  
//-------------------------- Ghost 2 -------------------------
Ghost2::Ghost2()
{
  //Initialize the offsets
  box.x = 100;
  box.y = 0;

  MAP_WIDTH=640;
  SCREEN_HEIGHT=480;
  SCREEN_WIDTH=1000;

  
  //Initialize the seek and destroy directions. first way to pacman is the most desirable way to go.
  first_way_to_pacman_ = 1;

  //Initialize crashed
  crashed_ = false;

  //Set the ghost's dimensions
  box.w = GHOST_WIDTH;    
  box.h = GHOST_HEIGHT;

  //Initialize the velocity
  xVel = 10;
  yVel = 0;
//The image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized surface that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = IMG_Load("img/ghost-picture2.bmp");

  //If the image loaded
  if( loadedImage != NULL )
    {
      //Create an optimized surface
      optimizedImage = SDL_DisplayFormat(ytpekare);

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

//Moves freely, and looks for checkpoints
void Ghost2::do_if_checkpoint( std::vector<SDL_Rect> checkmaze ) 
{
  if(is_checkpoint(checkmaze))
    {
      //make a fresh seek if ghost reaches a checkpoint
      first_way_to_pacman_ = 0;
      second_way_to_pacman_ = 0;
      seek();
    }
}

//sets the moving direction towards pacman at random
void Ghost2::seek()
{
  if (first_way_to_pacman_ == 0)
    {
      first_way_to_pacman_ = rand()% 4 + 1;
      second_way_to_pacman_ = rand()% 4 + 1;
    } 
}

//Returns ghost2 to start position
void Ghost2::get_home()
{
  box.x = 20;
  box.y = 0;
}
//-------------------------- Ghost 3 -----------------
Ghost3::Ghost3()
{
  //Initialize the offsets
  box.x = 0;
  box.y = 100;

  MAP_WIDTH=640;
  SCREEN_HEIGHT=480;
  SCREEN_WIDTH=1000;

  
  //Initialize the seek and destroy directions. first way to pacman is the most desirable way to go.
  first_way_to_pacman_ = 4;
  second_way_to_pacman_ = 1;

  //Initialize the angry or scared mode
  scared_ = false;

  //Initialize crashed
  crashed_ = false;

  //Set the ghost's dimensions
  box.w = GHOST_WIDTH;   
  box.h = GHOST_HEIGHT;

  //Initialize the velocity
  xVel = 0;
  yVel = 10;
  //The image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized surface that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = IMG_Load("img/ghost-picture3.bmp");

  //If the image loaded
  if( loadedImage != NULL )
    {
      //Create an optimized surface
      optimizedImage = SDL_DisplayFormat(ytpekare);

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

//Moves freely, and looks for checkpoints
void Ghost3::do_if_checkpoint( std::vector<SDL_Rect> checkmaze, Pacman paccy ) 
{
  
  if (is_checkpoint(checkmaze, paccy))
    {
      
      //make a fresh seek if ghost reaches a checkpoint
      first_way_to_pacman_ = 0;
      second_way_to_pacman_ = 0;
      crashed_ = 0;


      seek(paccy);
    }
}

//sets the moving direction towards pacman, works as ghost1 but switches the first and second ways to pacman,
void Ghost3::seek(Pacman paccy) 
{

  if (first_way_to_pacman_ == 0 && second_way_to_pacman_ == 0) //if we have tried both directions, get a new one
    {
      //pacman_x and pacman_y are the coordinates of pacman
      int pacman_x{paccy.reveal_position_x()};
      int pacman_y{paccy.reveal_position_y()};
      
  
      //tries to minimize the distance in the shortest direction first. If pacman is one step to the right and far away at the bottom, the ghost will first go down and then take one step left.
      if( abs(pacman_x - box.x) > abs(pacman_y - box.y) ) //if bigger difference in x than in y, then walk towards pacman i x direction
	{
	  if( pacman_x > box.x ) //if pacman is to the right, go right
	    {second_way_to_pacman_ = 2;}
	  else 
	    {second_way_to_pacman_ = 1;} //else, go left
      
	  if ( pacman_y > box.y ) //if pacman is below the ghost, go downwards
	    {first_way_to_pacman_ = 4;}
	  else
	    {first_way_to_pacman_ = 3;} //else, go up
	}
     
      else
	{
	  if (pacman_y > box.y) //biggest distance is in y direction, so walk in y direction first
	    {second_way_to_pacman_ = 4;}
	  else
	    {second_way_to_pacman_ = 3;}
      
	  if (pacman_x > box.x)
	    {first_way_to_pacman_ = 2;} //go right
	  else 
	    {first_way_to_pacman_ = 1;} //go left
	}
      
      if (10*first_way_to_pacman_ + second_way_to_pacman_ == crashed_) //same result for two seeks in a row means we are stuck
	{
	  //randomize a direcion
	  first_way_to_pacman_ = rand()% 4 + 1;
	  

	}  
 
      if (scared_ == true) //if the ghost is scared, reverse the moving direction
	{
	  reverse_direction(); 
	}
 
      crashed_ = 10*first_way_to_pacman_ + second_way_to_pacman_;
    }
}

//Returns ghost3 to start position
void Ghost3::get_home()
{
  box.x = 40;
  box.y = 0;
}






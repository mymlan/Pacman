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

Ghost1::Ghost1()
{
  //Initialize the offsets
  box.x = 0;
  box.y = 0;
  
  //Initialize the seek and destroy directions. first way to pacman is the most desirable way to go.
  first_way_to_pacman_ = 2;
  second_way_to_pacman_ = 4;
  //Initialize the angry or scared mode
  scared_ = false;

  //Initialize crashed
  crashed_ = false;

  //Set the ghost's dimensions
  box.w = PACMAN_WIDTH;    //we should change the global constants names PACMAN_WIDTH to CHARACTER_WIDTH
  box.h = PACMAN_HEIGHT;

  //Initialize the velocity
  xVel = 10;
  yVel = 0;
}

Ghost2::Ghost2()
{
  //Initialize the offsets
  box.x = 100;
  box.y = 0;
  
  //Initialize the seek and destroy directions. first way to pacman is the most desirable way to go.
  first_way_to_pacman_ = 1;

  //Initialize crashed
  crashed_ = false;

  //Set the ghost's dimensions
  box.w = PACMAN_WIDTH;    //we should change the global constants names PACMAN_WIDTH to CHARACTER_WIDTH
  box.h = PACMAN_HEIGHT;

  //Initialize the velocity
  xVel = 10;
  yVel = 0;
}

Ghost3::Ghost3()
{
  //Initialize the offsets
  box.x = 0;
  box.y = 100;
  
  //Initialize the seek and destroy directions. first way to pacman is the most desirable way to go.
  first_way_to_pacman_ = 4;
  second_way_to_pacman_ = 1;

  //Initialize the angry or scared mode
  scared_ = false;

  //Initialize crashed
  crashed_ = false;

  //Set the ghost's dimensions
  box.w = PACMAN_WIDTH;    //we should change the global constants names PACMAN_WIDTH to CHARACTER_WIDTH
  box.h = PACMAN_HEIGHT;

  //Initialize the velocity
  xVel = 0;
  yVel = 10;
}

void Ghost::reverse_direction()
{
  if (first_way_to_pacman_ == 1 || 3)
    {first_way_to_pacman_ += 1;}
  else
    {first_way_to_pacman_ -= 1;}
  
  if (second_way_to_pacman_ == 1 || 3)
    {second_way_to_pacman_ += 1;}
  else
    {second_way_to_pacman_ -= 1;}
}

void Ghost::move(std::vector<SDL_Rect> maze) //checks collision with walls
{
  Sprite animation;
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
      if( ( box.x < 0 ) || ( box.x + PACMAN_WIDTH > MAP_WIDTH ) || ( animation.check_collision( box, *it ) ) )
	{
	  //Move back
	  box.x -= xVel;
	  first_way_to_pacman_ = second_way_to_pacman_; 
	  second_way_to_pacman_ = 0;
	}
    }
   
  //Move the ghost up or down
  box.y += yVel;

  //If the square went too far up or down or has collided with the walls
  for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
    {
      if( ( box.y < 0 ) || ( box.y + PACMAN_HEIGHT > SCREEN_HEIGHT ) || ( animation.check_collision( box, *it ) ) )
	{
	  //Move back
	  box.y -= yVel;
	  first_way_to_pacman_ = second_way_to_pacman_; 
	  second_way_to_pacman_ = 0;
	}
    }
}

bool Ghost1::is_checkpoint(std::vector<SDL_Rect> checkmaze, Pacman paccy) //looks for a checkpoint
{
  Sprite animation;

  //check for checkpoint collission
  for(std::vector<SDL_Rect>::iterator it = checkmaze.begin() ; it != checkmaze.end(); ++it) //try all the checkpoints
    {
      if( animation.check_collision( box, *it ) )
	{
	  return true;
	}
    }
 

  return false;
}

bool Ghost2::is_checkpoint(std::vector<SDL_Rect> checkmaze) //looks for a checkpoint
{
  Sprite animation;
  //check for checkpoint collission
  for(std::vector<SDL_Rect>::iterator it = checkmaze.begin() ; it != checkmaze.end(); ++it) //try all the checkpoints
    {
      if(animation.check_collision( box, *it ) )
	{
	  return true;
	}
    }
  
  return false;
}

bool Ghost3::is_checkpoint(std::vector<SDL_Rect> checkmaze, Pacman paccy) //looks for a checkpoint
{
  Sprite animation;
  //check for checkpoint collission
  for(std::vector<SDL_Rect>::iterator it = checkmaze.begin() ; it != checkmaze.end(); ++it) //try all the checkpoints
    {
      if( animation.check_collision( box, *it ))
	{
	  return true;
	}
      
    }
  

  return false;
	
}

//Moves freely, and looks for checkpoints
void Ghost1::do_if_checkpoint( std::vector<SDL_Rect> checkmaze, Pacman paccy ) 
{
  
  if(is_checkpoint(checkmaze, paccy))
    {
      seek(paccy);
    }
}


//Moves freely, and looks for checkpoints
void Ghost2::do_if_checkpoint( std::vector<SDL_Rect> checkmaze ) 
{
  if(is_checkpoint(checkmaze))
    {
      seek();
    }
}

 

//Moves freely, and looks for checkpoints
void Ghost3::do_if_checkpoint( std::vector<SDL_Rect> checkmaze, Pacman paccy ) 
{
  
  if (is_checkpoint(checkmaze, paccy))
    {
      seek(paccy);
    }
}
  

//Sets the moving direction towards pacman
void Ghost1::seek(Pacman paccy)
{
  if(first_way_to_pacman_ == 0 && second_way_to_pacman_ == 0) //om sp�ket fastnat, slumpa riktning
    {first_way_to_pacman_ = rand()% 4 + 1;}

  else if
    (first_way_to_pacman_ == 0)
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


      if (scared_ == true) //if the ghost is scared, reverse the moving direction
	{
	  reverse_direction();
	}
  
    }
 
}

//sets the moving direction towards pacman at random
void Ghost2::seek()
{
  if (first_way_to_pacman_ == 0)
    {
      first_way_to_pacman_ = rand()% 4 + 1;
      second_way_to_pacman_ = first_way_to_pacman_;
    }
 
}


//sets the moving direction towards pacman, works as ghost1 but switches the first and second ways to pacman,
void Ghost3::seek(Pacman paccy) 
{
  if(first_way_to_pacman_ == 0 && second_way_to_pacman_ == 0) //om sp�ket fastnat, slumpa riktning
    {first_way_to_pacman_ = rand()% 4 + 1;}
  {
    if(first_way_to_pacman_ == 0)
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
     

	if (scared_ == true) //if the ghost is scared, reverse the moving direction
	  {
	    reverse_direction(); 
	  }
      
      }
  }
 
}




void Ghost1::show()
{
  //Show the ghost
  //apply_surface( box.x, box.y, ghost, screen );
  Sprite animation;
  animation.show_ghost(box.x, box.y, ghost);
}

void Ghost2::show()
{
  //show the ghost2
  //apply_surface( box.x, box.y, ghost2, screen );
  Sprite animation;
  animation.show_ghost(box.x, box.y, ghost2);


}


void Ghost3::show()
{
  //show the ghost2
  //apply_surface( box.x, box.y, ghost3, screen );
  Sprite animation;
  animation.show_ghost(box.x, box.y, ghost3);
}

//Returns SDL-object of ghost
SDL_Rect Ghost::get_box()
{
  return box;
}


//Returns ghost to start position
void Ghost1::get_home()
{
  box.x = 0;
  box.y = 0;
}

//Returns ghost2 to start position
void Ghost2::get_home()
{
  box.x = 20;
  box.y = 0;
}

//Returns ghost3 to start position
void Ghost3::get_home()
{
  box.x = 40;
  box.y = 0;
}



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

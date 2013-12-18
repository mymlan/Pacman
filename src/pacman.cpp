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
#include "score.h"

//============================================================================
//  Class: Pacman (KOD)
//============================================================================



Pacman::Pacman()
{
    //Initialize the offsets
    box.x = 320;
    box.y = 440;

    //Set the Pacman's dimensions
    box.w = PACMAN_WIDTH;
    box.h = PACMAN_HEIGHT;

    //Initialize the velocity
    xVel = 10;
    yVel = 0;
    x= 320;
    y= 440;

    //Initialize lives of Pacman
    lives = 0;

 //Initialize animation variables
    frame = 0;
    status = PACMAN_LEFT;

    food_left = 1;//114;
    pacman_has_eaten_special_food = false;
}


int Pacman::reveal_position_x()
{
  int position_x{box.x};
  return position_x;
}

int Pacman::reveal_position_y()
{
  int position_y{box.y};
  return position_y;
}

int Pacman::life()
{
  int life{lives};
  return life;
}


void Pacman::showlife()
{
  Sprite animation;
  animation.showlife(lives); 
  /* if (lives==2)
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
  */
}


void Pacman::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
	case SDLK_UP: yVel = -10 /*-PACMAN_HEIGHT/2*/; xVel = 0; break;
	case SDLK_DOWN: yVel = 10 /* PACMAN_HEIGHT / 2*/; xVel = 0; break;
	case SDLK_LEFT: xVel = -10/*-PACMAN_WIDTH / 2 */; yVel = 0; break;
	case SDLK_RIGHT: xVel = 10 /*PACMAN_WIDTH / 2*/; yVel = 0;  break;
        }
    }
}

void Pacman::move(std::vector<SDL_Rect> maze, SDL_Rect wall25)
{
  //Sprite
  Sprite animation;

    //Move pacman left or right
    box.x += xVel;
    //If pacman went too far to the left or right or has collided with the walls
    for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
      {
	if( ( box.x < 0 ) || ( box.x + PACMAN_WIDTH > MAP_WIDTH ) || ( animation.check_collision( box, *it ) ) )
	  {
	    //Move back
	    box.x -= xVel;
	  }
      }   
	if( ( box.x < 0 ) || ( box.x + PACMAN_WIDTH > MAP_WIDTH ) || ( animation.check_collision( box, wall25 ) ) )
	  {
	    //Move back
	    box.x -= xVel;
	  } 

    //Move pacman up or down
    box.y += yVel;

    //If pacman went too far up or down or has collided with the walls
    for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
      {
	if( ( box.y < 0 ) || ( box.y + PACMAN_HEIGHT > SCREEN_HEIGHT ) || ( animation.check_collision( box, *it ) ) )
	  {
	    //Move back
	    box.y -= yVel;
	  }
      } 

}



void Pacman::show()
{
  Sprite animation;

  
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
    animation.show_pacman(box.x, box.y, status, frame);
/*
    if( status == PACMAN_RIGHT )
    {
        apply_surface(box.x, box.y, pacman, screen, &clipsRight[ frame] );
    }
    else if( status == PACMAN_LEFT )
    {
        apply_surface( box.x,box.y, pacman, screen, &clipsLeft[ frame ] );
    }
    else if( status == PACMAN_UP)
      {
	apply_surface (box.x, box.y, pacman, screen, &clipsUp[ frame ]);
      }

 else if( status == PACMAN_DOWN)
      {
	apply_surface (box.x,box.y, pacman , screen, &clipsDown[ frame ]);
	}*/
}





//Check if Pacman has no more lives
bool Pacman::game_over()
{
  return (life()==-1);
}


//Collision between
bool Pacman::eat_eaten(Ghost& ghost_object,Score& myScore)
{
  Sprite animation;
  
  if (animation.check_collision(box, ghost_object.get_box()))
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
  Sprite animation;
  for (std::vector<Food>::iterator it = food_vector.begin() ; it != food_vector.end(); ++it)
    {
    
      if ((animation.check_collision(box, (*it).get_box())) and !(*it).eaten())
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
  Sprite animation;
 for (std::vector<Special_Food>::iterator it = special_food_vector.begin() ; it != special_food_vector.end(); ++it)
    {
      if ((animation.check_collision(box, (*it).get_box())) and !(*it).eaten())
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

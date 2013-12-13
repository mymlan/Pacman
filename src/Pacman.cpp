//============================================================================
// Name        : Pacman.cpp
// Author      : Mymlan
// Version     : 
// Copyright   : 
// Description : Hello World in C++, Ansi-style
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



//void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

//Screen attributes
const int SCREEN_WIDTH = 1000; //640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int MAP_WIDTH = 640;


//The frame rate
int FRAMES_PER_SECOND = 20;

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
SDL_Surface *menu = NULL;
SDL_Surface *score = NULL;
SDL_Surface *startup=NULL;

SDL_Surface *food = NULL;
SDL_Surface *special_food = NULL;
SDL_Surface *text = NULL;
SDL_Surface *highscore = NULL;


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
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = {0,100,0};


//============================================================================
//  Classes
//============================================================================

//The Pacman
class Pacman
{
private:
  //The collision box of the square
  SDL_Rect box;
  int x, y;

  //The velocity of the square
  int xVel, yVel;

  //Pacmans lives
  int lives;
 
  //Its current frame
    int frame;

    //Its animation status
    int status;

public:
  //Initializes the variables
  Pacman();

  //Reveals pacmans position, ghosts will ask for this
  int reveal_position_x();
  int reveal_position_y();

  //Keeps tracks of pacmans lives and when he dies
  int life();
  void showlife();
  bool game_over();
  bool eat_eaten(class Ghost&, class Score&);

 //Pacman eats food for points
  bool eat_food(class Food&, class Score&);

  //Pacman eats special_food - ghosts flees
  bool eat_special_food(class Special_Food&, class Score&, class Ghost&);

  //Takes key presses and adjusts the square's velocity
  void handle_input();

  //Moves the Pacman
  void move(std::vector<SDL_Rect>, SDL_Rect);

  //Shows the Pacman on the screen
  void show();
  
  //Sets Pacmans position to startposition
  void get_home();
};

//The ghost 
class Ghost //need a way to set crashed_ to false. Do this by checking if there was no crash
{
private:
  //The collission box of the ghost
  SDL_Rect box;

  //The velocity of the ghost
  int xVel, yVel;

  //Angry or scare ghost. 0 angry, 1 scared
  bool scared_;

  //if ghost crashes into a wall it will change direction, otherwise will keep going.
  bool crashed_;

  //1 is left, 2 is right, 3 is up, and 4 is down. 0 will be the starting value, meaning the ghost hasn't found out where pacman is
  int first_way_to_pacman_;
  int second_way_to_pacman_;

public:
  //Initializes the variables
  Ghost();

  //Moves the ghost
  void move(std::vector<SDL_Rect>);

  //Finds out how to move to Pacman. Seek sets the "first and second way to pacman" member units.
  void seek(Pacman);


  SDL_Rect get_box();

  //Shows the ghost on the screen
  void show();

  //Sets Ghost position to startposition
  void get_home();

  //Returns if ghost is scared/angry
  bool is_scared();

  //Switches ghost between chase and flee states
  void change_mood();
};

//The second ghost
class Ghost2 //this is a whimsy  ghost, it moves in random directions. It is also never scared
{
private:
  //The collission box of the ghost
  SDL_Rect box;

  //The velocity of the ghost
  int xVel, yVel;

  //if ghost crashes into a wall it will change direction, otherwise will keep going.
  bool crashed_;

  //1 is left, 2 is right, 3 is up, and 4 is down. 0 will be the starting value, meaning the ghost hasn't found out where pacman is
  int first_way_to_pacman_;


public:
  //Initializes the variables
  Ghost2();

  //Moves the ghost
  void move(std::vector<SDL_Rect>);

  //Finds out how to move to Pacman. This ghost does it at random
  void seek();


  SDL_Rect get_box();

  //Shows the ghost on the screen
  void show();

  //Sets Ghost position to startposition
  void get_home();

  //Returns if ghost is scared/angry
  bool is_scared();

  //Switches ghost between chase and flee states
  void change_mood();
};


//The timer
class Timer
{
private:
  //The clock time when the timer started
  int startTicks;
  
  //The ticks stored when the timer was paused
  int pausedTicks;
  
  //The timer status
  bool paused;
  bool started;
  
public:
  //Initializes variables
  Timer();
  
  //The various clock actions
  void start();
  void stop();
  void pause();
  void unpause();
  
  //Gets the timer's time
  int get_ticks();
  
  //Checks the status of the timer
  bool is_started();
  bool is_paused();
};

class Menu
{
private:
  // The button
  SDL_Rect button;
  bool start;
  std::string message_;

public:
  //Initialize variable
  Menu(int x, int  y, std::string text = "");
  void showstart();
  void show();
  bool get_start();
  void change_start();
  void show_button();

};

//Score
class Score
{
private:
  int points;
public:
  Score();
  void reset_score();
  void add_points(int);
  std::string get_score(); // return score as string
  void show();
  int return_score(); // returns score as int
};


//Highscore
class Highscore
{
private:
  int highscore;
  std::string name;
public:
  Highscore(int, std::string);
  // void load();
  // void close();
  bool is_new_highscore(Score&);
  void save_new_highscore(Score&);
  std::string get_highscore();
  void show();
};


//Food
class Food
{
private:
  SDL_Rect box;
  bool eaten_;
public:
  Food(int,int);
  bool eaten();
  void was_eaten();
  void show();
  SDL_Rect get_box();
};

//Special_Food
class Special_Food
{
private:
  SDL_Rect box;
  bool eaten_;
public:
  Special_Food(int,int);
  bool eaten();
  void was_eaten();
  void show();
  SDL_Rect get_box();
};








//============================================================================
// Images 
//============================================================================




SDL_Surface *load_image( std::string filename )
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

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );

}

void set_clips()
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



bool check_collision( SDL_Rect A, SDL_Rect B )
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


bool init()
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

bool load_files()
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

    //If there was a problem in loading the ghost picture
    if( ghost == NULL)
      {
	return false;
      }


    //Load the foods image
    food = load_image( "img/food-picture1.bmp" );

    //If there was a problem in loading the food picture
    if( food == NULL)
      {
        return false;
      }
    



 //Load the menu image
    menu = load_image( "img/pingvin.png" );

    //If there was a problem in loading the ghost picture
    if( ghost == NULL)
      {
	return false;
      }

    //Load player score
    font = TTF_OpenFont("img/arial.ttf",28);

    if (font ==NULL)
      {
	return false;
      }

    //Load Special_Food
    special_food = load_image( "img/special_food-picture.bmp" );
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




//============================================================================
//  Memory release
//============================================================================


void clean_up()
{
    //Free the surface
    SDL_FreeSurface( pacman );
    SDL_FreeSurface( ghost );   
    SDL_FreeSurface( score );
    SDL_FreeSurface( startup);
               //prova ta bort vid problem med ghost
    //Quit SDL
    SDL_Quit();
}



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
    lives = 2;

 //Initialize animation variables
    frame = 0;
    status = PACMAN_LEFT;
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
    //Move pacman left or right
    box.x += xVel;
    //If pacman went too far to the left or right or has collided with the walls
    for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
      {
	if( ( box.x < 0 ) || ( box.x + PACMAN_WIDTH > MAP_WIDTH ) || ( check_collision( box, *it ) ) )
	  {
	    //Move back
	    box.x -= xVel;
	  }
      }   
	if( ( box.x < 0 ) || ( box.x + PACMAN_WIDTH > MAP_WIDTH ) || ( check_collision( box, wall25 ) ) )
	  {
	    //Move back
	    box.x -= xVel;
	  } 

    //Move pacman up or down
    box.y += yVel;

    //If pacman went too far up or down or has collided with the walls
    for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
      {
	if( ( box.y < 0 ) || ( box.y + PACMAN_HEIGHT > SCREEN_HEIGHT ) || ( check_collision( box, *it ) ) )
	  {
	    //Move back
	    box.y -= yVel;
	  }
      } 

}



void Pacman::show()
{
  
    //If Pacman is moving left
    if( xVel < 0 )
    {
        //Set the animation to left
        status = PACMAN_LEFT;

        //Move to the next frame in the animation
        frame++;
    }
    //If Foo is moving right
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
    //If Foo standing
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
      }
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
bool Pacman::eat_food(Food& food_object,Score& myScore)
{
  if (check_collision(box, food_object.get_box()) && !food_object.eaten())
      {
	myScore.add_points(1);
	food_object.was_eaten();
	return true;
      }
  return false;
}

//Pacman eats special_food
bool Pacman::eat_special_food(Special_Food& special_food_object,Score& myScore, Ghost& myGhost)
{
  if (check_collision(box, special_food_object.get_box()) && !special_food_object.eaten())
      {
	myGhost.change_mood();//funktion att spöken flyr
	special_food_object.was_eaten();
	return true;
      }
  return false;
}



//Returns Pacman to starting position
void Pacman::get_home()
{
  box.x = 320;
  box.y = 440;
}


//============================================================================
//  Class: Ghost
//============================================================================

Ghost::Ghost()
{
  //Initialize the offsets
  box.x = 0;
  box.y = 0;
  
  //Initialize the seek and destroy directions. first way to pacman is the most desirable way to go.
  first_way_to_pacman_ = 0;
  second_way_to_pacman_ = 0;
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
  first_way_to_pacman_ = 0;

  //Initialize crashed
  crashed_ = false;

  //Set the ghost's dimensions
  box.w = PACMAN_WIDTH;    //we should change the global constants names PACMAN_WIDTH to CHARACTER_WIDTH
  box.h = PACMAN_HEIGHT;

  //Initialize the velocity
  xVel = 10;
  yVel = 0;
}


void Ghost::move(std::vector<SDL_Rect> maze)
{
  //If the ghost recently crashed into a wall, go towards pacman in the second most desirable way
  if (crashed_ == true)
    {first_way_to_pacman_ = second_way_to_pacman_;}

  //Set velocity and direction
  switch(first_way_to_pacman_)
    {
    case 1: yVel = 0; xVel = -10; break; //left
    case 2: yVel = 0; xVel = 10; break;  //right
    case 3: yVel = -10; xVel = 0; break;  //up      y increases downwards
    case 4: yVel = 10; xVel = 0; break; //down
    }

  crashed_ = false;  
  //Move the ghost left or right
    box.x += xVel;


    //If the ghost went too far to the left or right or has collided with the walls
    for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
      {
	if( ( box.x < 0 ) || ( box.x + PACMAN_WIDTH > MAP_WIDTH ) || ( check_collision( box, *it ) ) )
	  {
	    //Move back
	    box.x -= xVel;
	    crashed_ = true;
	  }
      }    

    //Move the ghost up or down
    box.y += yVel;

    //If the square went too far up or down or has collided with the walls
    for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
      {
	if( ( box.y < 0 ) || ( box.y + PACMAN_HEIGHT > SCREEN_HEIGHT ) || ( check_collision( box, *it ) ) )
	  {
	    //Move back
	    box.y -= yVel;
	    crashed_ = true;
	  }
      }
}


void Ghost2::move(std::vector<SDL_Rect> maze)
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
    for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
      {
	if( ( box.x < 0 ) || ( box.x + PACMAN_WIDTH > MAP_WIDTH ) || ( check_collision( box, *it ) ) )
	  {
	    //Move back
	    box.x -= xVel;
	    crashed_ = true;
	  }
      }    

    //Move the ghost up or down
    box.y += yVel;

    //If the square went too far up or down or has collided with the walls
    for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
      {
	if( ( box.y < 0 ) || ( box.y + PACMAN_HEIGHT > SCREEN_HEIGHT ) || ( check_collision( box, *it ) ) )
	  {
	    //Move back
	    box.y -= yVel;
	    crashed_ = true;
	  }
      }
}


//Sets the moving direction towards pacman
void Ghost::seek(Pacman paccy)
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
      if (first_way_to_pacman_ == 1 || 3)
	{first_way_to_pacman_ += 1;}
      else
	{first_way_to_pacman_ -= 1;}
      
      if (second_way_to_pacman_ == 1 || 3)
	{second_way_to_pacman_ += 1;}
      else
	{second_way_to_pacman_ -= 1;}
    }
  
}


//sets the moving direction towards pacman at random
void Ghost2::seek()
{
  if (crashed_ == true)
    {
      first_way_to_pacman_ = rand()% 4 + 1;
    }
}

void Ghost::show()
{
  //Show the ghost
  apply_surface( box.x, box.y, ghost, screen );
}

void Ghost2::show()
{
  //Show the ghost
  apply_surface( box.x, box.y, ghost, screen );
}


//Returns SDL-object of ghost
SDL_Rect Ghost::get_box()
{
  return box;
}

//Returns SDL-object of ghost2
SDL_Rect Ghost2::get_box()
{
  return box;
}

//Returns ghost to start position
void Ghost::get_home()
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
}

//============================================================================
//  Class: Timer
//============================================================================

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

//============================================================================
//  Class: Score
//============================================================================
Score::Score()
{
  points=0;
}

void Score::reset_score()
{
  points=0;
}

void Score::add_points(int new_points)
{
  points += new_points;
}

std::string Score::get_score()
{
  std::stringstream stream;
  std::string text;
  stream << points;
  stream >> text; 
  return text;
}

int Score::return_score()
{
  return points;
}

void Score::show()
{
  score = TTF_RenderText_Solid( font, get_score().c_str(), textColor );
  apply_surface(0,0,score, screen);
}

//============================================================================
//  Class: Menu
//============================================================================

Menu::Menu(int x, int y, std::string text)
{
  //Initialize offset
  button.x = x;
  button.y = y;
  start=true;
  message_ = text;


  //Set dimension
  button.w = BUTTON_WIDTH;
  button.h = BUTTON_HEIGHT;

}
bool Menu::get_start()
{
  return start;
}

void Menu::change_start()
{ 
 start=false;
}

void Menu::show()
{
  //Show the startbuttons
  
  //  SDL_FillRect( screen, &button, SDL_MapRGB( screen->format, 0xEF, 0xEF, 0xEF) );
   for (int i=0; i<=8; i++)
    { 

    apply_surface( (MAP_WIDTH+i*INFOPANEL_WIDTH), 0, startup, screen, &clipsInfopanel[0] );
  
  
    }
  
}

void Menu::show_button()
{
  text = TTF_RenderText_Solid( font, message_.c_str() , textColor );
  apply_surface(button.x, button.y,text, screen);
}


void Menu::showstart()
{

  apply_surface(0,0,startup,screen, &clipsStartscr[0]); 
  std::cout << "Hey Big Boy/Girl!!!" <<std::endl;
  //apply_surface(0,0,startup,screen);
}
//============================================================================
//  Class: Highscore
//============================================================================
Highscore::Highscore(int myScore, std::string myName)
{
  highscore=myScore;
  name=myName;

}

bool Highscore::is_new_highscore(Score& myScore) // ev. ta in namn också
{
  /*std::ifstream InputFile ("highscore.txt");
  std::vector<Highscore> highscoretable;
  // int lowest_highscore{0};
  // std::string highscore;
  int new_score = myScore.return_score();
  if (InputFile.is_open())
    {
      for (int i{0}; i<1; i++) // 10
	{
	  InputFile >> highscore;
	}
      lowest_highscore=std::stoi(highscore);
      InputFile.close();
    }   
  if (new_score > lowest_highscore)
    {
      return true;
      }*/
  return false;
}

void Highscore::save_new_highscore(Score& new_highscore)
{
  /* std::ofstream OutputFile ("highscore.txt");
  int new_score = new_highscore.return_score();
  Highscore highscore_entry{new_score, "Ingrid"};
  std::vector<Highscore> highscoretable;
 highscoretable.push_back(highscore_entry);
 for (int i = 0 ; i < highscoretable.size() ; i++)
   { 
     OutputFile << highscoretable[i] << std::endl;   
   }
    // OutputFile << highscoretable;
   OutputFile.close();
  //ladda fil
  //lägg in på rätt palts
  //kolla listans längd
  //stäng fil*/
}

std::string Highscore::get_highscore()
{
  // std::stringstream stream;
  std::string text;
  // stream << points;
  // stream >> text; 
  return text;
}

void Highscore::show()
{
  //highscore = TTF_RenderText_Solid( font, get_highscore().c_str(), textColor );
  apply_surface(0,0,score,screen);
}

//============================================================================
//  FOOD
//============================================================================


Food::Food(int x_cord, int y_cord)
{
  bool eaten_=false;

  //Initialize the offsets
  box.x = x_cord;
  box.y = y_cord;

  //Set the foods dimensions
  box.w = PACMAN_WIDTH; //we should change the global constants names PACMAN_WIDTH to CHARACTER_WIDTH
  box.h = PACMAN_HEIGHT;
}

void Food::was_eaten()
{
  eaten_=true;
}

bool Food::eaten()
{
  return eaten_;
}

void Food::show()
{
  if (!eaten())
    {
      apply_surface(box.x,box.y,food, screen);
    }
}

//Returns SDL-object of ghost
SDL_Rect Food::get_box()
{
  return box;
}









//============================================================================
//  Class: Special_Food
//============================================================================
Special_Food::Special_Food(int x_cord, int y_cord)
{
  bool eaten_=false;

  //Initialize the offsets
  box.x = x_cord;
  box.y = y_cord;

  //Set the foods dimensions
  box.w = PACMAN_WIDTH;    //we should change the global constants names PACMAN_WIDTH to CHARACTER_WIDTH
  box.h = PACMAN_HEIGHT;
}

void Special_Food::was_eaten()
{
  eaten_=true;
}

bool Special_Food::eaten()
{
  return eaten_;
}

void Special_Food::show()
{
  if (!eaten())
    {
      apply_surface(box.x,box.y,special_food, screen);
    }
}

//Returns SDL-object of ghost
SDL_Rect Special_Food::get_box()
{
  return box;
}

//============================================================================
//  MAIN
//============================================================================



int main( int argc, char* args[] )
{

    //Quit flag
    bool quit = false;

    //Menu
    Menu Startup(0,0,"Press S to play");

    //The pacman
    Pacman myPacman;

    //The ghost
    Ghost myGhost;

    //The second ghost
    Ghost2 myGhost2;

    //Player score
    Score myScore;

    //Highscore
    Highscore myHighscore(0,"Ingrid");


    //Food
    Food myFood(370,100);

    //Special_food
    Special_Food mySpecial_Food(370,0);


    //The frame rate regulator
    Timer fps;


  //The buttons
    Menu theButton(700,100,"1. Chicken Tandoori 75kr ");
    Menu theButton2(700, 150,"2. Tikka Massaala 70kr ");
    Menu theButton3(700, 200,"3. Curry Chicken 70kr");

  //Initialize
  if( init() == false )
    {
      return 1;
    }
    
  //Load the files
  if( load_files() == false )
    {
      std::cout << "trubbel att ladda filerna" << std::endl;
      return 1;
    }
  //Initialize walls
    SDL_Rect wall1 = {40,40,40,200};
    SDL_Rect wall2 = {80,40,80,40};
    SDL_Rect wall3 = {80,120,40,40};
    SDL_Rect wall4 = {120,40,40,120};
    SDL_Rect wall5 = {200,40,160,40};
    SDL_Rect wall6 = {320,80,40,40};
    SDL_Rect wall7 = {200,120,160,40};
    SDL_Rect wall8 = {200,160,40,40};
    SDL_Rect wall9 = {200,200,160,40};
    SDL_Rect wall10 = {400,40,200,40};
    SDL_Rect wall11 = {400,120,200,40};
    SDL_Rect wall12 = {40,280,40,160};
    SDL_Rect wall13 = {120,200,40,240};
    SDL_Rect wall14 = {200,280,40,160};
    SDL_Rect wall15 = {280,280,120,40};
    SDL_Rect wall16 = {360,320,40,40};
    SDL_Rect wall17 = {280,360,120,80};
    SDL_Rect wall18 = {400,200,200,40};
    SDL_Rect wall19 = {440,240,40,200};
    SDL_Rect wall20 = {520,240,40,40};
    SDL_Rect wall21 = {600,280,40,40};
    SDL_Rect wall22 = {520,320,40,120};
    SDL_Rect wall23 = {560,360,40,40};
    SDL_Rect wall24 = {600,440,40,40};
    SDL_Rect wall25 = {350,160,10,40};

    //Create vector with all walls in, called maze
    std::vector<SDL_Rect> maze = {wall1,wall2,wall3,wall4,wall5,wall6,wall7,wall8,wall9,wall10,wall11,wall12,wall13,wall14,wall15,wall16,wall17,wall18,wall19,wall20,wall21,wall22,wall23,wall24};


    // Clip the sprite sheet
    set_clips();
 

    //While the user hasn't quit
    while( quit == false )
      {

	//=================== Startup =========================

	if(Startup.get_start()==true)
	  {	
	    bool proceed = false;
	    Startup.showstart();
	    //Show penguin
	    //  apply_surface( MAP_WIDTH, 0, startup, screen );
	    Startup.show();
	    Startup.show_button();

	 
	    //Update the screen
	     if( SDL_Flip( screen ) == -1 )
	       {
		 return 1;
	       }
	     
	     while(!proceed)
	       {

		 //========================== Xed out ======================
		 //If the user has Xed out the window
		 if( event.type == SDL_QUIT )
		   {
		     std::cout << "Game quit" << std::endl;
		     //Quit the program
		     quit = true; proceed = true;
		   }
		 //========================================================###

		 while(SDL_PollEvent( &event))
		   {
		     if(event.type == SDL_KEYDOWN)
		       {
			 switch(event.key.keysym.sym)
			   {
			   case SDLK_s: proceed=true; std::cout<<" Spela!!!" <<std::endl;  break;
			   case SDLK_q: quit=true; proceed=true; std::cout << "Game quit" << std::endl ; break;
			   }
			 Startup.change_start();
		       }
		   }
	       }
	  }
	
	//==================================================##

	//Start the frame timer
	fps.start();



	//While there's events to handle
	while( SDL_PollEvent( &event ) )
	  {

	    
	    //If a key was pressed
	    if( event.type == SDL_KEYDOWN )
	      {
		if( event.key.keysym.sym == SDLK_q)
		  {
		    std::cout << "Game quit" << std::endl;
		    quit = true;
		  }


		// ======================= PAUSE ==========================
   
		//If p was pressed
		if( event.key.keysym.sym == SDLK_p )
		  {
		    bool cont = false;
		    std::cout <<"Spel pausat" << std:: endl;
		    
		    //Pause the game
		    while(!cont)
		      {
			
			while(SDL_PollEvent( &event))
			  {
			    //========================== Xed out ======================
			    //If the user has Xed out the window
			    if( event.type == SDL_QUIT )
			      {
				//Quit the program
				quit = true; cont = true;
			      }
			    //=========================================================
			    
			    //Unpause the game 
			    if(event.type == SDL_KEYDOWN)
			      {
				switch(event.key.keysym.sym)
				  {
				  case SDLK_p: cont = true; std::cout << "Spela!!"<< std::endl; break;
				  case SDLK_q: cont = true ; quit = true; std::cout << "Game quit" << std::endl; break;
				  }
				
			      }
			  }
		      }
		  }
	      }
	  


	  
	    //Handle events for the pacman
	    myPacman.handle_input();


	  
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
	      {
		//Quit the program
                quit = true;
	      }
	  }
	
        //Move the pacman
        myPacman.move(maze, wall25);
	
	//Ghost finds out where pacman is
	myGhost.seek(myPacman);
	myGhost2.seek();

	//Move the ghost
	myGhost.move(maze);
	myGhost2.move(maze);

	//Is a ghost eating Pacman or are Pacman eating a ghost
	if (myPacman.eat_eaten(myGhost, myScore))
	  {
	    if (myPacman.game_over())
	      {

		if (myHighscore.is_new_highscore(myScore))
		  {
		    quit=true;
		    myHighscore.save_new_highscore(myScore);	
		  }
	      }
	  }


	//Is a Pacman eating food
	if (myPacman.eat_food(myFood, myScore)){
	  // if (alla food-pluttar uppätna - spel slut){
	  //  quit=true;
	  
	}
	
	//Is a Pacman eating special_food
	if (myPacman.eat_special_food(mySpecial_Food, myScore, myGhost)){
	  // timer räkna ner
	  //
	}


        //Fill the screen white
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

        //Show the walls
	for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
	  {
	    SDL_FillRect( screen, &(*it), SDL_MapRGB( screen->format, 0x00, 0x00, 0xEF) );
	  }
	//Show wall 25 the wall that separates the ghosts nest from playfield
	SDL_FillRect( screen, &wall25, SDL_MapRGB( screen->format, 0xAF, 0x00, 0x00) );

        //Show pacman on the screen
        myPacman.show();
	


	//Show ghost on the screen
	myGhost.show();
	myGhost2.show();


	//Show food on the screen
	myFood.show();

	//Show special_food on the screen
	mySpecial_Food.show();

	
	//Show penguin
	//apply_surface( MAP_WIDTH, 0, startup, screen, &clipsInfopanel[0] );


	//show the lives on the screen
	myPacman.showlife();

	//show the buttons

	theButton.show();
	theButton.show_button();
	theButton2.show_button();
theButton3.show_button();


	//Show score on the side of the screen
	myScore.show();

	
	
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
	  {
            return 1;
	  }
	
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
	  {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
	  }
	}
    
    //Clean up
    clean_up();

    return 0;
}


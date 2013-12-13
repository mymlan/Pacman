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
#include <algorithm>


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
SDL_Surface *ghost3 = NULL;
SDL_Surface *menu = NULL;
SDL_Surface *score = NULL;
SDL_Surface *startup=NULL;

SDL_Surface *food = NULL;
SDL_Surface *special_food = NULL;
SDL_Surface *text = NULL;
SDL_Surface *highscore = NULL;
SDL_Surface *checkpoint = NULL;

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
TTF_Font *scoreFont = NULL;
TTF_Font *headerFont= NULL;
TTF_Font *infoFont=NULL;

//The color of the font
SDL_Color textColor = {0,0,0,0};
SDL_Color headerColor = {255,255,0,0};
SDL_Color infoColor = {};



//============================================================================
//  Classes
//============================================================================

//===================== PACMAN ==============================================
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

  //food left
  int food_left;

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
  void eat_food(std::vector<class Food>&, class Score&); //bool eat_food(class Food&, class Score&);

  //Pacman eats special_food - ghosts flees
  bool eat_special_food(class Special_Food&, class Score&);

  //Takes key presses and adjusts the square's velocity
  void handle_input();

  //Moves the Pacman
  void move(std::vector<SDL_Rect>, SDL_Rect);

  //Shows the Pacman on the screen
  void show();
  
  //Sets Pacmans position to startposition
  void get_home();

  //returns true if there is no food left
  bool no_food_left();

  

};

//#######################################################################################################


//================================== GHOST ============================================================== 
class Ghost
{
protected:
  //if ghost crashes into a wall it will change direction, otherwise will keep going.
  bool crashed_;

//The collission box of the ghost
  SDL_Rect box;

  //The velocity of the ghost
  int xVel, yVel;

  //Angry or scare ghost. false is  angry, true is scared
  bool scared_;


  //1 is left, 2 is right, 3 is up, and 4 is down. 0 will be the starting value, meaning the ghost hasn't found out where pacman is
  int first_way_to_pacman_;
  int second_way_to_pacman_;
public:
  Ghost() = default;
  
  //Moves the ghost
  void move(std::vector<SDL_Rect>);
  
  
  SDL_Rect get_box();
  
  //use reverse_direction when ghost toggles scared_
  void reverse_direction();
 
  //Sets Ghost position to startposition
  virtual void get_home() = 0;
  
  //Returns if ghost is scared/angry
  bool is_scared();
  
  //Switches ghost between chase and flee states
  void change_mood();

 
};



class Ghost1 : public Ghost
{
public:
 //Finds out how to move to Pacman. Seek sets the "first and second way to pacman" member units.
  void seek(Pacman);

  //Initializes the variables
  Ghost1();

  void get_home();  

  //Shows the ghost on the screen
  void show();

 //Looks for checkpoints, 
  bool is_checkpoint(std::vector<SDL_Rect>, Pacman);

  //If the ghost finds a checkpoint, it reorients. uses is_checkpoint?
  void do_if_checkpoint(std::vector<SDL_Rect>, Pacman);


};


//The second ghost
class Ghost2 : public Ghost  //this is a whimsy  ghost, it moves in random directions.
{
public:
  void seek();

  Ghost2();

  void get_home();

  //Shows the ghost on the screen
  void show();


//Looks for checkpoints
  bool is_checkpoint(std::vector<SDL_Rect>);

//If the ghost finds a checkpoint, it reorients. uses is_checkpoint?
  void do_if_checkpoint(std::vector<SDL_Rect>);

};

//The third ghost
class Ghost3 : public Ghost //this ghost mixes up the first and second most desirable directions towards pacman
{
public:
  void seek(Pacman paccy);

  Ghost3();

  void get_home();

  //Shows the ghost on the screen
  void show();
  
  //Looks for checkpoints
  bool is_checkpoint(std::vector<SDL_Rect>, Pacman);

 //If the ghost finds a checkpoint, it reorients. uses is_checkpoint
  void do_if_checkpoint(std::vector<SDL_Rect>, Pacman);

 
};



//###############################################################################################


//========================================= TIMER ===============================================
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

//###############################################################################################

//========================================== MENU ==============================================
/*
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
*/

class Menu
{
protected:
  SDL_Rect button;
  std::string message_;

public:
  virtual void show() const = 0;
  virtual ~Menu() = default;
};



class Start : public Menu
{
public:
  void show() const;
  void show_infopanel() const;
  bool is_start();
  void change_start();

  Start(int x, int y, std::string text);
  ~Start() = default;

private:
  bool start;
};


class Button : public Menu
{
public:
  ~Button()=default;
  Button(int x, int y, std::string text);

  void show() const;
};




//###############################################################################################

//========================================== SCORE ==============================================
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

//###############################################################################################

//========================================== HIGHSCORE============================================

//Highscore
class Highscore
{
private:
  int highscore;
  std::string name;
public:
  std::vector<int> highscoretable;
  Highscore(int, std::string);
  // void load();
  // void close();
  bool is_new_highscore(Score&);
  void save_new_highscore(Score&);
  std::string get_highscore_name();
  int get_highscore();
  void show();
  void load_list();
};

//###############################################################################################

//========================================== FOOD ==============================================

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


//###############################################################################################

//========================================== SPECIAL FOOD =======================================


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


/*
//Ghosts checkpoints, to make their ways in the maze
class Checkpoint
{
private:
  SDL_Rect box;

<<<<<<< HEAD
public:
  Checkpoint(int, int);
  SDL_Rect get_box();
  void show(); //används för att testa, ska egentligen vara osynlig
 
};
*/





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
    ghost2 = load_image( "img/ghost-picture2.bmp" );

    ghost3 = load_image( "img/ghost-picture3.bmp" );
    //If there was a problem in loading the ghost picture
    if( ghost == NULL || ghost2 == NULL || ghost3 == NULL)

      {
	return false;
      }
    

    //Load the foods image
    food = load_image( "img/food2.bmp" );

    //If there was a problem in loading the food picture
    if( food == NULL)
      {
        return false;
      }
    
    //load the checkpoint image, only for testing. The checkpoints shall be invisible
    checkpoint = load_image( "img/checkpoint.bmp" );
    
    //If there was a problem in loading the checkpoint picture
    if( checkpoint == NULL)
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

    //Load  headerFont
    headerFont = TTF_OpenFont("img/xtrusion.ttf",55);

    if (headerFont ==NULL)
      {
	return false;
      }

 //Load infoFont
    infoFont = TTF_OpenFont("img/KarmaFuture.ttf",22);

    if (infoFont ==NULL)
      {
	return false;
      }


  //Load player scoreFont
   scoreFont = TTF_OpenFont("img/arial.ttf",28);

    if (scoreFont ==NULL)
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
    SDL_FreeSurface( ghost2 );   //prova ta bort vid problem med ghost
    SDL_FreeSurface( score );
    SDL_FreeSurface( startup);
              
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
    lives = 0;

 //Initialize animation variables
    frame = 0;
    status = PACMAN_LEFT;

    food_left = 40;
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
void Pacman::eat_food(std::vector<Food>& food_vector, Score& myScore) //Food& food_object
{
  for (std::vector<Food>::iterator it = food_vector.begin() ; it != food_vector.end(); ++it)
    {
    
      if ((check_collision(box, (*it).get_box())) and ((*it).eaten() == false))
	{
	  myScore.add_points(1);
	  (*it).was_eaten();
	  food_left = food_left - 1;
	 
	}
      
    }
    
}



//Pacman eats special_food
bool Pacman::eat_special_food(Special_Food& special_food_object,Score& myScore)
{

  if (check_collision(box, special_food_object.get_box()) && !special_food_object.eaten())
      {	
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
      if( ( box.x < 0 ) || ( box.x + PACMAN_WIDTH > MAP_WIDTH ) || ( check_collision( box, *it ) ) )
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
      if( ( box.y < 0 ) || ( box.y + PACMAN_HEIGHT > SCREEN_HEIGHT ) || ( check_collision( box, *it ) ) )
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
  //check for checkpoint collission
  for(std::vector<SDL_Rect>::iterator it = checkmaze.begin() ; it != checkmaze.end(); ++it) //try all the checkpoints
    {
      if( check_collision( box, *it ) )
	{
	  return true;
	}
    }
 

  return false;
}

bool Ghost2::is_checkpoint(std::vector<SDL_Rect> checkmaze) //looks for a checkpoint
{
  //check for checkpoint collission
  for(std::vector<SDL_Rect>::iterator it = checkmaze.begin() ; it != checkmaze.end(); ++it) //try all the checkpoints
    {
      if(check_collision( box, *it ) )
	{
	  return true;
	}
    }
  
  return false;
}

bool Ghost3::is_checkpoint(std::vector<SDL_Rect> checkmaze, Pacman paccy) //looks for a checkpoint
{
  //check for checkpoint collission
  for(std::vector<SDL_Rect>::iterator it = checkmaze.begin() ; it != checkmaze.end(); ++it) //try all the checkpoints
    {
      if( check_collision( box, *it ))
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
  if(first_way_to_pacman_ == 0 && second_way_to_pacman_ == 0) //om spöket fastnat, slumpa riktning
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
  if(first_way_to_pacman_ == 0 && second_way_to_pacman_ == 0) //om spöket fastnat, slumpa riktning
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
  apply_surface( box.x, box.y, ghost, screen );
  
}

void Ghost2::show()
{
  //show the ghost2
  apply_surface( box.x, box.y, ghost2, screen );
}

void Ghost3::show()
{
  //show the ghost2
  apply_surface( box.x, box.y, ghost3, screen );
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
  score = TTF_RenderText_Solid( scoreFont, get_score().c_str(), textColor );
  apply_surface(0,0,score, screen);
}

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
  apply_surface(0,0,startup,screen, &clipsStartscr[0]); 
  std::cout << "Hey Big Boy/Girl!!!" <<std::endl;
  //apply_surface(0,0,startup,screen);

 //Show the startbuttons
  
  //  SDL_FillRect( screen, &button, SDL_MapRGB( screen->format, 0xEF, 0xEF, 0xEF) );
   for (int i=0; i<=8; i++)
    { 

    apply_surface( (MAP_WIDTH+i*INFOPANEL_WIDTH), 0, startup, screen, &clipsInfopanel[0] );
  
    }
   text = TTF_RenderText_Solid( headerFont, message_.c_str() , headerColor );
   apply_surface(660, 30,text, screen); 

}


void Start::show_infopanel() const
{
 //Show the startbuttons
  
  //  SDL_FillRect( screen, &button, SDL_MapRGB( screen->format, 0xEF, 0xEF, 0xEF) );
   for (int i=0; i<=8; i++)
    { 

    apply_surface( (MAP_WIDTH+i*INFOPANEL_WIDTH), 0, startup, screen, &clipsInfopanel[0] );
  
    }

   text = TTF_RenderText_Solid( headerFont, message_.c_str() , headerColor );
   apply_surface(660, 30,text, screen); 
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
  text = TTF_RenderText_Solid( infoFont, message_.c_str() , headerColor );
  apply_surface(button.x, button.y,text, screen);  
}




/*Menu::Menu(int x, int y, std::string text)
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
  



   text = TTF_RenderText_Solid( headerFont, "PACMAN" , headerColor );
   apply_surface(button.x, button.y,text, screen);
}
	void Menu::show_button()
{
  text = TTF_RenderText_Solid( infoFont, message_.c_str() , headerColor );
  apply_surface(button.x, button.y,text, screen);

}


void Menu::showstart()
{

  apply_surface(0,0,startup,screen, &clipsStartscr[0]); 
  std::cout << "Hey Big Boy/Girl!!!" <<std::endl;
  //apply_surface(0,0,startup,screen);
}
*/




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
  load_list();
  int size=highscoretable.size();
  if ((size<10) || (myScore.return_score() > highscoretable[size-1])){
    return true;}
  return false;
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
    // return false;
}

void Highscore::save_new_highscore(Score& new_highscore)
{
  //Load highscore list to vector
  load_list();

  //Save highscore list to file
  std::ofstream outputFile ("src/highscore.txt", std::ios::binary);
  //Highscore highscore_entry{new_score, "Ingrid"};
  highscoretable.push_back(new_highscore.return_score());
  std::stable_sort (highscoretable.begin(), highscoretable.end());
  std::reverse(highscoretable.begin(),highscoretable.end());
  if (highscoretable.size() > 10)
    {
      highscoretable.pop_back();
    }
  for ( int i = 0 ; i < highscoretable.size() ; i++)
    { 
      outputFile << highscoretable[i] << std::endl;
      //  outputFile << highscoretable[i].get_highscore_name << std::endl;
    }
  outputFile.close();
}

void Highscore::load_list()
{
  std::ifstream inputfile ("src/highscore.txt");
  int entry;
  highscoretable.erase(highscoretable.begin(),highscoretable.end());
  while (inputfile >> entry)
    { 
      highscoretable.push_back(entry);
    }
  inputfile.close();
}

std::string Highscore::get_highscore_name()
{
  return name;
}

int Highscore::get_highscore()
{
  return highscore;
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


/*
//============================================================================
// Class: Checkpoint
//============================================================================
Checkpoint::Checkpoint(int x_cord, int y_cord)
{
  //initialize the offsets
  box.x = x_cord;
  box.y = y_cord;

//set the checkpoints dimensions
  box.w = 1;
  box.h = 1;
}

void Checkpoint::show()
{
  apply_surface(box.x, box.y, checkpoint, screen);
}
*/

//============================================================================
//  MAIN
//============================================================================



int main( int argc, char* args[] )
{

    //Quit flag
    bool quit = false;

    //Menu
    Start Startup(0,0,"PACMAN");
    //    Menu Startup(660,30);


    //The pacman
    Pacman myPacman;

    //The ghost
    Ghost1 myGhost1;

    //The second ghost
    Ghost2 myGhost2;

    //The third ghost
    Ghost3 myGhost3;

    //Player score
    Score myScore;

    //Highscore
    Highscore myHighscore(0,"Ingrid");


    //Initialize Food
    Food myFood1(10,50);
    Food myFood2(10,90);
    Food myFood3(10,130);
    Food myFood4(10,170);
    Food myFood5(10,210);
    Food myFood6(10,250);
    Food myFood7(10,290);
    Food myFood8(10,330);
    Food myFood9(10,370);
    Food myFood10(10,410);

    Food myFood11(50,10);
    Food myFood12(50,250);
    Food myFood13(50,450);

    Food myFood14(90,10);
    Food myFood15(90,170);
    Food myFood16(90,210);
    Food myFood17(90,250);
    Food myFood18(90,290);
    Food myFood19(90,330);
    Food myFood20(90,370);
    Food myFood21(90,410);
    Food myFood22(90,450);

    Food myFood23(130,10);
    Food myFood24(130,170);
    Food myFood25(130,450);

    Food myFood26(170,10);
    Food myFood27(170,50);
    Food myFood28(170,90);
    Food myFood29(170,130);
    Food myFood30(170,170);
    Food myFood31(170,210);
    Food myFood32(170,250);
    Food myFood33(170,290);
    Food myFood34(170,330);
    Food myFood35(170,370);
    Food myFood36(170,410);
    Food myFood37(170,450);

    Food myFood38(210,10);
    Food myFood39(210,90);
    Food myFood40(210,250);
    Food myFood41(210,450);

    //create vectorwith all food in, called food_vector
    std::vector<Food> food_vector = {myFood1,myFood2,myFood3,myFood4,myFood5,myFood6,myFood7,myFood8,myFood9,myFood10,myFood11,myFood12,myFood13,myFood14,myFood15,myFood16,myFood17,myFood18,myFood19,myFood20,myFood21,myFood22,myFood23,myFood24,myFood25,myFood26,myFood27,myFood28,myFood29,myFood30,myFood31,myFood32,myFood33,myFood34,myFood35,myFood36,myFood37,myFood38,myFood39,myFood40};

   

    //Special_food
    Special_Food mySpecial_Food(370,0);


    //The frame rate regulator
    Timer fps;


  //The buttons

    /* Button theButton(700,100,"1. Chicken Tandoori 75kr ");
    Button theButton2(700, 150,"2. Tikka Massaala 70kr ");
    Button theButton3(700, 200,"3. Curry Chicken 70kr");
    */

      //Menu theButton(660,30);

      Button theButton1(660,100,"Press \"S\" to start ");
      Button theButton2(660, 150,"Press \"P\" to pause ");
      Button theButton3(660, 200,"Press \"Q\" to quit");
      Button theButton4(660,250,"Press \"H\" to show highscore");
    

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
  SDL_Rect wall1 = {40,40,40,200}; //dessa två har samma parametrar som checkpoint1 och checkpoint2
  SDL_Rect wall2 = {80,40,80,40}; //
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

  //Initialize checkpoints
  SDL_Rect checkpoint1 = {15,260,5,5};
  

  /* more chekpoints
     SDL_Rect checkpoint = {};
     SDL_Rect checkpoint = {};
     SDL_Rect checkpoint = {};
     SDL_Rect checkpoint = {};
  */
 
  
  //Create a vector with all the checkpoints

  std::vector<SDL_Rect> checkmaze = {checkpoint1};

  

    // Clip the sprite sheet
    set_clips();
 

    //While the user hasn't quit
    while( quit == false )
      {

	//=================== Startup =========================

	if(Startup.is_start())
	  {	
	    bool proceed = false;
	    Startup.show();
	    //Show penguin
	    //  apply_surface( MAP_WIDTH, 0, startup, screen );

	    theButton1.show();
	    theButton2.show();
	    theButton3.show();
	    theButton4.show();
	 

	    //   Startup.show();
	    //Startup.show_button();
	    //theButton1.show_button();
	    //theButton2.show_button();
	    //theButton3.show_button();
	    //theButton4.show_button();

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
	
	//Ghosts finds out where pacman is
	myGhost1.seek(myPacman);
	myGhost2.seek(); 
	myGhost3.seek(myPacman);

	//Move the ghosts
	myGhost1.move(maze);
	myGhost2.move(maze);
	myGhost3.move(maze);

	myGhost1.do_if_checkpoint(checkmaze, myPacman);
	myGhost2.do_if_checkpoint(checkmaze);
	myGhost3.do_if_checkpoint(checkmaze, myPacman);


	//Is a ghost eating Pacman or are Pacman eating a ghost


	/*
	if (myPacman.eat_eaten(myGhost, myScore))
	  {
	    if (myPacman.game_over())
	      {
	    	if (myHighscore.is_new_highscore(myScore))
		  {
		    std::cout << "Nytt rekord" << std::endl;
		    myHighscore.save_new_highscore(myScore);
		    quit=true;	
		  }
	      }
	  }

	*/
	if (myPacman.eat_eaten(myGhost1, myScore))
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

	if (myPacman.eat_eaten(myGhost2, myScore))
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

	if (myPacman.eat_eaten(myGhost3, myScore))
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

	//Om alla Food objekt är uppätna avslutas spelet. Ska troligtvis ske något annat
	if(myPacman.no_food_left())
	  {
	    quit=true;
	  }



	//Is a Pacman eating food
	myPacman.eat_food(food_vector, myScore);

	//myPacman.eat_food(food_vector, myScore);
      /* {
	  // if (alla food-pluttar uppätna - spel slut){
	  //  quit=true;
	  

	  }*/


	//Is a Pacman eating special_food
	if (myPacman.eat_special_food(mySpecial_Food, myScore))
	  {
	    myGhost1.change_mood();
	    myGhost2.change_mood();
	    myGhost3.change_mood();
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
	
	//Show food on the screen
	for (std::vector<Food>::iterator it = food_vector.begin() ; it != food_vector.end(); ++it)
	  {
	    (*it).show();
	  }

	//Show the checkpoints - just for testing
	for (std::vector<SDL_Rect>::iterator it = checkmaze.begin() ; it != checkmaze.end(); ++it)
	  {
	    SDL_FillRect( screen, &(*it), SDL_MapRGB( screen->format, 0x00, 0xEF, 0xEF) );
	  }

	//Show ghost on the screen
	myGhost1.show();
	myGhost2.show();
	myGhost3.show();




	//Show special_food on the screen
	mySpecial_Food.show();

	




	//show infopanel
	Startup.show_infopanel();

	//show the buttons

	//theButton.show();
       

	theButton1.show();
	theButton2.show();
	theButton3.show();
	theButton4.show();

	  //theButton1.show_button();
	  //	theButton2.show_button();
	  //theButton3.show_button();

	  //theButton4.show_button();
	
	//show the lives on the screen
	myPacman.showlife();




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


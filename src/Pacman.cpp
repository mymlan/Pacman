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

//Screen attributes
const int SCREEN_WIDTH = 1000; //640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int MAP_WIDTH = 640;


//The frame rate
const int FRAMES_PER_SECOND = 20;

//The attributes of the square
const int SQUARE_WIDTH = 20;
const int SQUARE_HEIGHT = 20;

//The surfaces
SDL_Surface *square = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *ghost = NULL;
SDL_Surface *menu = NULL;

//The event structure
SDL_Event event;




//============================================================================
//  Classes
//============================================================================



//The wall
SDL_Rect wall;


//The square
class Square
{
private:
  //The collision box of the square
  SDL_Rect box;

  //The velocity of the square
  int xVel, yVel;

public:
  //Initializes the variables
  Square();

  //Reveals pacmans position, ghosts will ask for this
  int reveal_position_x();
  int reveal_position_y();

  //Takes key presses and adjusts the square's velocity
  void handle_input();

  //Moves the square
  void move();

  //Shows the square on the screen
  void show();
  
};

//The ghost 
class Ghost
{
private:
  //The collission box of the ghost
  SDL_Rect box;

  //The velocity of the ghost
  int xVel, yVel;

  //1 is left, 2 is right, 3 is up, and 4 is down. 0 is starting value, meaning the ghost hasn't found out where pacman is
  int direction_to_pacman_;

public:
  //Initializes the variables
  Ghost();

  //Moves the ghost
  void move();

  //Finds out how to move to Pacman. Seek sets the "direction_to_pacman datamedlem".
  void seek(Square);

  //Finds out how to move away from Pacman. Uses seek, but instead of going towards pacman by right, flee goes left.
  //std::string flee();

  

  //Shows the ghost on the screen
  void show();
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

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the square image
  square = load_image( "img/square.bmp" ); //pacman-test bilden har fel dimensioner

    //If there was a problem in loading the square
    if( square == NULL )
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


 //Load the menu image
    menu = load_image( "img/pingvin.png" );

    //If there was a problem in loading the ghost picture
    if( ghost == NULL)
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
    SDL_FreeSurface( square );
    SDL_FreeSurface( ghost );                  //prova ta bort vid problem med ghost
    //Quit SDL
    SDL_Quit();
}



//============================================================================
//  Class: Square
//============================================================================



Square::Square()
{
    //Initialize the offsets
    box.x = 360;
    box.y = 280;

    //Set the square's dimensions
    box.w = SQUARE_WIDTH;
    box.h = SQUARE_HEIGHT;

    //Initialize the velocity
    xVel = 10;
    yVel = 0;
}

int Square::reveal_position_x()
{
  int position_x{box.x};
  return position_x;
}

int Square::reveal_position_y()
{
  int position_y{box.y};
  return position_y;
}



void Square::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
	case SDLK_UP: yVel = -10 /*-SQUARE_HEIGHT/2*/; xVel = 0; break;
	case SDLK_DOWN: yVel = 10 /* SQUARE_HEIGHT / 2*/; xVel = 0; break;
	case SDLK_LEFT: xVel = -10/*-SQUARE_WIDTH / 2 */; yVel = 0; break;
	case SDLK_RIGHT: xVel = 10 /*SQUARE_WIDTH / 2*/; yVel = 0;  break;
        }
    }

    
}

void Square::move()
{
    //Move the square left or right
    box.x += xVel;

    //If the square went too far to the left or right or has collided with the wall
    if( ( box.x < 0 ) || ( box.x + SQUARE_WIDTH > MAP_WIDTH ) || ( check_collision( box, wall ) ))
    {
        //Move back
        box.x -= xVel;
    }

    //Move the square up or down
    box.y += yVel;

    //If the square went too far up or down or has collided with the wall
    if( ( box.y < 0 ) || ( box.y + SQUARE_HEIGHT > SCREEN_HEIGHT ) || ( check_collision( box, wall ) ) )
    {
        //Move back
        box.y -= yVel;
    }
}


void Square::show()
{
    //Show the square
    apply_surface( box.x, box.y, square, screen );
}



//============================================================================
//  Class: Ghost
//============================================================================



Ghost::Ghost()
{
  //Initialize the offsets
  box.x = 100;
  box.y = 100;
  
  //Initialize the seek and destroy direction, that is, where the ghost believe pacman is
  direction_to_pacman_ = 0;


  //Set the ghost's dimensions
  box.w = SQUARE_WIDTH;    //we should change the global constants names SQUARE_WIDTH to CHARACTER_WIDTH
  box.h = SQUARE_HEIGHT;

  //Initialize the velocity
  xVel = 0;
  yVel = 0;
}



void Ghost::move()
{
  //Set velocity and direction in order to move to where the ghost believe pacman is located
  switch(direction_to_pacman_)
    {
    case 1: yVel = 0; xVel = -10; break; //left
    case 2: yVel = 0; xVel = 10; break;  //right
    case 3: yVel = -10; xVel = 0; break;  //up      y increases downwards
    case 4: yVel = 10; xVel = 0; break; //down
    }
  

  //Move the ghost left or right 
  box.x += xVel;

  //If the ghost went too far to the left or right or has collided with the wall
  if( ( box.x < 0 ) || ( box.x + SQUARE_WIDTH > MAP_WIDTH ) || ( check_collision( box, wall ) ))
    {
      //Move back
      box.x -= xVel;
    }

  //Move the ghost up or down
  box.y += yVel;

  //If the ghost went too far up or down or has collided with the wall
  if( ( box.y < 0 ) || ( box.y + SQUARE_HEIGHT > SCREEN_HEIGHT ) || ( check_collision( box, wall ) ) )
    {
      //Move back
      box.y -= yVel;
    }
}


//Sets the moving direction towards pacman
void Ghost::seek(Square paccy)
{

  //pacman_x and pacman_y are the coordinates of pacman
  int pacman_x{paccy.reveal_position_x()};
  int pacman_y{paccy.reveal_position_y()};
  
  
  //tries to minimize the distance in the shortest direction first. If pacman is one step to the right and far away at the bottom, the ghost will first take one step left and the go down.
  if( abs(pacman_x - box.x) > abs(pacman_y - box.y) ) //if bigger difference in x than in y, then walk towards pacman i x direction
    {
      if (pacman_x < box.x)
	{direction_to_pacman_ = 1;}
      else
	{direction_to_pacman_ = 2;}
      return;
    }

  //else walk towards pacman in y direction
  if (pacman_y < box.y) 
    {direction_to_pacman_ = 3;}
  else
    {direction_to_pacman_ = 4;}
  return;    
}



void Ghost::show()
{
      //Show the ghost
    apply_surface( box.x, box.y, ghost, screen );
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
//  Class: Timer
//============================================================================



int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //The square
    Square mySquare;

    //The ghost
    Ghost myGhost;

    //The frame rate regulator
    Timer fps;

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

    //Set the wall
    wall.x = 300;
    wall.y = 40;
    wall.w = 40;
    wall.h = 400;

  

    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the square
            mySquare.handle_input();

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //Move the square
        mySquare.move();
	
	//Ghost finds out where pacman is
	myGhost.seek(mySquare);
	
	//Move the ghost
	myGhost.move();

	

        //Fill the screen white
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

        //Show the wall
        SDL_FillRect( screen, &wall, SDL_MapRGB( screen->format, 0x77, 0x77, 0x77 ) );
	
        //Show the square on the screen
        mySquare.show();

	//Show the ghost on the screen
	myGhost.show();

  apply_surface( MAP_WIDTH, 0, menu, screen );


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


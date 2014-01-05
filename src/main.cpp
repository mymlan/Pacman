
//============================================================================
// Name        : main.cpp
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
#include "sprite.h"
#include "pacman.h"
#include "ghost.h"
#include "food.h"
#include "score.h"
#include "highscore.h"
#include "timer.h"
#include "menu.h"
#include "string_input.h"
#include "map_data.h"

SDL_Surface *screen {NULL};

void exit_program(std::string message)
{
	std::cerr << message << std::endl;
	SDL_Quit();
	exit(1);
}

void init()
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
		exit_program("Error in SDL init");
	}

	SDL_EnableUNICODE( SDL_ENABLE );

	screen = SDL_SetVideoMode( 1000, 480, 32, SDL_SWSURFACE );
	if( screen == NULL )  {
		exit_program("Error in screen init");
	}

	if(TTF_Init() == -1)
	{
		exit_program("Error in TTF init");
	}
}

void update_screen()
{
	if( SDL_Flip( screen ) == -1 )
	{
		exit_program("Could not flip screen");
	}
}

void show_start_menu(bool &quit, Start &Startup, Button &b1, Button &b2, Button &b3, Button &b4)
{
	if(Startup.is_start())
	{
		SDL_Event event;
		bool proceed = false;


		//Start screen
		Startup.show(screen);

		Startup.show_infopanel(screen);
		b1.show(screen);

		b2.show(screen);
		b3.show(screen);
		b4.show(screen);

		update_screen();

		while(!proceed)
		{
			if( event.type == SDL_QUIT )
			{
				quit = true; proceed = true;
			}

			while(SDL_PollEvent(&event))
				Startup.handle_input(proceed,quit,event);

		}
	}
}

void run_pause_loop(bool &quit, Highscore &myHighscore)
{
	SDL_Event event;
	bool cont = false;
	while(!cont)
	{
		while(SDL_PollEvent( &event))
		{
			if( event.type == SDL_QUIT )
			{
				quit = true;
				cont = true;
			}

			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
				case SDLK_p:
					cont = true;
					break;
				case SDLK_q:
					cont = true;
					quit = true;
					exit(0);
					break;
				case SDLK_h:
					SDL_WM_SetCaption("Highscore", NULL );
					Highscore_screen Highscore(400,10, "HIGHSCORE");
					Highscore.show(screen);
					myHighscore.show(screen);
					if( SDL_Flip( screen ) == -1 )
					{
						exit_program("Error flipping highscore screen");
					}
					break;
				}

			}
		}
	}
}


void handle_key_press(bool& quit, SDL_Event &event, Highscore &myHighscore)
{
	if( event.type == SDL_QUIT )
	{
		quit = true;
	}

	if( event.type == SDL_KEYDOWN )
	{
		if( event.key.keysym.sym == SDLK_q)
		{
			quit = true;
		}

		if( event.key.keysym.sym == SDLK_p )
		{
			run_pause_loop(quit, myHighscore);
		}
	}
}

void move_stuff(Pacman &myPacman, Ghost1 &myGhost1, Ghost2 &myGhost2, Ghost3 &myGhost3, std::vector<SDL_Rect>& maze, SDL_Rect &wall25)
{
	myPacman.move(maze, wall25);

	myGhost1.seek(myPacman);
	myGhost2.seek();
	myGhost3.seek(myPacman);

	myGhost1.move(maze);
	myGhost2.move(maze);
	myGhost3.move(maze);
}

void do_creepy_ghost_stuff(Timer &checktimer1, Timer &checktimer2, Timer &checktimer3,
		Ghost1 &myGhost1, Ghost2 &myGhost2, Ghost3 &myGhost3,
		Pacman &myPacman, std::vector<SDL_Rect>& checkpoint_vector) {
	if(!checktimer1.is_started()) //If the timer is off, turn it on
	{checktimer1.start();}

	if(checktimer1.get_ticks() > 300) //was it long enough since we found a checkpoint?
	{
		myGhost1.do_if_checkpoint(checkpoint_vector, myPacman);
		if(myGhost1.is_checkpoint(checkpoint_vector))
		{
			checktimer1.start();
		} //restart the timer so that ghost only will look at a checkpoint once
	}

	if(!checktimer2.is_started()) //If the timer is off, turn it on
	{checktimer2.start();}

	if(checktimer2.get_ticks() > 300) //was it long enough since we found a checkpoint?
	{
		myGhost2.do_if_checkpoint(checkpoint_vector);
		if(myGhost2.is_checkpoint(checkpoint_vector))
		{checktimer2.start();} //restart the timer so that ghost only will look at a checkpoint once
	}

	if(!checktimer3.is_started()) //If the timer is off, turn it on
	{checktimer3.start();}

	if(checktimer3.get_ticks() > 1000) //was it long enough since we found a checkpoint?
	{
		myGhost3.do_if_checkpoint(checkpoint_vector, myPacman);
		if(myGhost3.is_checkpoint(checkpoint_vector))
		{checktimer3.start();} //restart the timer so that ghost only will look at a checkpoint once
	}
}

void handle_ghost_eats_pacman(bool &quit, Pacman &myPacman, Ghost1 &myGhost1, Ghost2 &myGhost2, Ghost3 &myGhost3,
		Highscore &myHighscore, Score &myScore)
{
	if (myPacman.eat_eaten(myGhost1, myScore) || myPacman.eat_eaten(myGhost2, myScore) || myPacman.eat_eaten(myGhost3, myScore))
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
}

void handle_no_food_left(Pacman &myPacman)
{
	if(myPacman.no_food_left())
	{
		End_game game_over;
		StringInput PlayerName;
		SDL_WM_SetCaption("Enter name", NULL );
		game_over.show(screen);
		update_screen();

		bool nameEntered = false;
		while(!nameEntered)
		{
			SDL_Event event;
			while(SDL_PollEvent( &event))
			{
				if( nameEntered == false )
				{
					PlayerName.handle_input(event);

					if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
					{
						nameEntered = true;
					}
					PlayerName.show_centered(screen);
					update_screen();

				}
			}
		}

		PlayerName.show_centered(screen);
		update_screen();
	}
}

void handle_ghost_mood(Pacman &myPacman, Timer &special_food_timer,
		Ghost1 &myGhost1, Ghost2 &myGhost2, Ghost3 &myGhost3)
{
	if (myPacman.has_pacman_eaten_special_food())
	{
		if(!special_food_timer.is_started())
		{
			myGhost1.change_mood();
			myGhost2.change_mood();
			myGhost3.change_mood();
		}
		special_food_timer.start();
		myPacman.pacman_change_mood();
	}

	if(special_food_timer.get_ticks() > 5000)
	{
		myGhost1.change_mood();
		myGhost2.change_mood();
		myGhost3.change_mood();
		special_food_timer.stop();
	}
}

void draw_background(Ghost1 myGhost1)
{
	if(myGhost1.is_scared())
	{
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	}
	else
	{

		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x3, 0x5, 0x80 ) );
	}
}

int main( int argc, char* args[] )
{
	init();
	SDL_WM_SetCaption("Pacman", NULL );

	SDL_Event event;

	//Screen attributes
	extern const int SCREEN_WIDTH;
	extern const int SCREEN_HEIGHT;
	extern const int SCREEN_BPP;

	//Map attributes
	extern const int MAP_WIDTH ;

	Start Startup{0,0,"PACMAN"}; // Start menu
	Button theButton1(660,100,"Press \"S\" to start ");
	Button theButton2(660, 150,"Press \"P\" to pause ");
	Button theButton3(660, 200,"Press \"Q\" to quit");
	Button theButton4(660,250,"Press \"H\" to show highscore");

	Pacman myPacman;
	Ghost1 myGhost1;
	Ghost2 myGhost2;
	Ghost3 myGhost3;
	Score myScore;
	Highscore myHighscore;
	Timer fps;
	Timer checktimer1;
	Timer checktimer2;
	Timer checktimer3;
	Timer special_food_timer;

	std::vector<Food> food_vector = map_data_get_food_vector();
	std::vector<Special_Food> special_food_vector = map_data_get_special_food_vector();
	std::vector<SDL_Rect> maze = map_data_get_maze_vector();
	SDL_Rect wall25 = {350,160,10,40};
	std::vector<SDL_Rect> checkpoint_vector = map_data_get_checkpoint_vector();

	bool quit = false;
	while(!quit)
	{
		show_start_menu(quit, Startup, theButton1, theButton2, theButton3, theButton4);
		fps.start();

		while(SDL_PollEvent( &event ))
		{
			handle_key_press(quit, event, myHighscore);
			myPacman.handle_input(event);
		}

		move_stuff(myPacman, myGhost1, myGhost2, myGhost3, maze, wall25);

		do_creepy_ghost_stuff(checktimer1, checktimer2, checktimer3,
				myGhost1, myGhost2, myGhost3, myPacman, checkpoint_vector);

		handle_ghost_eats_pacman(quit, myPacman, myGhost1, myGhost2, myGhost3,
				myHighscore, myScore);

		handle_no_food_left(myPacman);

		myPacman.eat_food(food_vector, myScore);
		myPacman.eat_special_food(special_food_vector, myScore);

		handle_ghost_mood(myPacman, special_food_timer,
				myGhost1, myGhost2, myGhost3);

		draw_background(myGhost1);

		for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
		{
			SDL_FillRect( screen, &(*it), SDL_MapRGB( screen->format, 0x00, 0x00, 0xEF) );
		}


		//show the wonderwall
		SDL_FillRect( screen, &wall25, SDL_MapRGB( screen->format, 0xAF, 0x00, 0x00) );

		//Show pacman on the screen
		myPacman.show(screen);

		for (std::vector<Food>::iterator it = food_vector.begin() ; it != food_vector.end(); ++it)
		{
			(*it).show(screen);
		}

		for (std::vector<Special_Food>::iterator it = special_food_vector.begin() ; it != special_food_vector.end(); ++it)
		{
			(*it).show(screen);
		}

		//Show the checkpoints - just for testing
		for (std::vector<SDL_Rect>::iterator it = checkpoint_vector.begin() ; it != checkpoint_vector.end(); ++it)
		{
			SDL_FillRect( screen, &(*it), SDL_MapRGB( screen->format, 0x00, 0xEF, 0xEF) );
		}

		//Show ghost on the screen
		myGhost1.show(screen);
		myGhost2.show(screen);
		myGhost3.show(screen);

		//show infopanel
		Startup.show_infopanel(screen);

		//show the buttons
		theButton1.show(screen);
		theButton2.show(screen);
		theButton3.show(screen);
		theButton4.show(screen);

		update_screen();

		fps.delay_game();
	}

	TTF_Quit();
	SDL_Quit();

	return 0;
}

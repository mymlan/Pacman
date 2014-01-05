#include "board.h"

Board::Board(SDL_Surface *screen)
: screen(screen)
, Startup(0,0,"PACMAN")
, theButton1(660,100,"Press \"S\" to start ")
, theButton2(660, 150,"Press \"P\" to pause ")
, theButton3(660, 200,"Press \"Q\" to quit")
, theButton4(660,250,"Press \"H\" to show highscore")
, myPacman()
, myGhost1()
, myGhost2()
, myGhost3()
, myScore()
, myHighscore()
, fps()
, checktimer1()
, checktimer2()
, checktimer3()
, special_food_timer()
{
	SDL_WM_SetCaption("Pacman", NULL );
	food_vector = map_data_get_food_vector();
	special_food_vector = map_data_get_special_food_vector();
	maze = map_data_get_maze_vector();
	wall25 = {350,160,10,40};
	checkpoint_vector = map_data_get_checkpoint_vector();
}

void Board::run()
{
	bool quit = false;
	while(!quit)
	{
		show_start_menu(quit);
		fps.start();

		SDL_Event event;
		while(SDL_PollEvent( &event ))
		{
			handle_key_press(quit, event);
			myPacman.handle_input(event);
		}

		move_stuff();

		do_creepy_ghost_stuff();

		handle_ghost_eats_pacman(quit);

		handle_no_food_left();

		myPacman.eat_food(food_vector, myScore);
		myPacman.eat_special_food(special_food_vector, myScore);

		handle_ghost_mood();

		draw_everything();

		fps.delay_game();
	}


}

void Board::exit_program(std::string message)
{
	std::cerr << message << std::endl;
	SDL_Quit();
	exit(1);
}

void Board::update_screen()
{
	if( SDL_Flip( screen ) == -1 )
	{
		exit_program("Could not flip screen");
	}
}

void Board::show_start_menu(bool &quit)
{
	if(Startup.is_start())
	{
		SDL_Event event;
		bool proceed = false;


		//Start screen
		Startup.show(screen);

		Startup.show_infopanel(screen);
		theButton1.show(screen);

		theButton2.show(screen);
		theButton3.show(screen);
		theButton4.show(screen);

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

void Board::run_pause_loop(bool &quit)
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


void Board::handle_key_press(bool& quit, SDL_Event &event)
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
			run_pause_loop(quit);
		}
	}
}

void Board::move_stuff()
{
	myPacman.move(maze, wall25);

	myGhost1.seek(myPacman);
	myGhost2.seek();
	myGhost3.seek(myPacman);

	myGhost1.move(maze);
	myGhost2.move(maze);
	myGhost3.move(maze);
}

void Board::do_creepy_ghost_stuff() {
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

void Board::handle_ghost_eats_pacman(bool &quit)
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

void Board::handle_no_food_left()
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

void Board::handle_ghost_mood()
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

void Board::draw_background()
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

void Board::draw_everything()
{
	draw_background();

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
}

#include "board.h"

void exit_program(std::string message)
{
	std::cerr << message << std::endl;
	SDL_Quit();
	exit(1);
}

int main( int argc, char* args[] )
{
	SDL_Surface *screen = NULL;
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

	Board board(screen);
	board.run();

	TTF_Quit();
	SDL_Quit();

	return 0;
}

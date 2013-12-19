//============================================================================
// Name        : main.cpp
// Author      : Chicken Tandoori och Jonca
// Version     : 1
// Copyright   : 
// Description : Main
//============================================================================
//============================================================================
//  MAIN
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


//Screen attributes
extern const int SCREEN_WIDTH ; //640;
extern const int SCREEN_HEIGHT ;
extern const int SCREEN_BPP ;

//Map attributes
extern const int MAP_WIDTH ;



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

      //Om alla Food objekt �r upp�tna avslutas spelet. Ska troligtvis ske n�got annat
      if(myPacman.no_food_left())
	{
	  quit=true;
	}



      //Is a Pacman eating food
      myPacman.eat_food(food_vector, myScore);

      //myPacman.eat_food(food_vector, myScore);
      /* {
      // if (alla food-pluttar upp�tna - spel slut){
      //  quit=true;
	  

      }*/


      //Is a Pacman eating special_food
      if (myPacman.eat_special_food(mySpecial_Food, myScore))
	{
	  myGhost1.change_mood();
	  myGhost2.change_mood();
	  myGhost3.change_mood();
	  // timer r�kna ner
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


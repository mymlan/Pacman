
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

//Set up the screen
SDL_Surface *screen {NULL};
   
bool init()
{//Initialize all SDL subsystems
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
      return false;
    }

  screen = SDL_SetVideoMode( 1000, 480, 32, SDL_SWSURFACE );

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

bool init(SDL_Surface* screen, std::string caption)
{
  //Initialize all SDL subsystems
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
      return false;
    }
 
  //Set up the screen
  screen = SDL_SetVideoMode(1000, 480, 32, SDL_SWSURFACE );
  
 
  //If there was an error in setting up the screen
  if( screen == NULL )
    {
      return false;
    }
 
  //Set the window caption
  SDL_WM_SetCaption( caption.c_str(), NULL );
     
  //Initialize SDL_ttf
  if(TTF_Init() == -1)
    {
      return false;
    }
 
  //If everything initialized fine
  return true;
}


//============================================================================
//  MAIN
//============================================================================

int main( int argc, char* args[] )
{
  SDL_EnableUNICODE( SDL_ENABLE );


  //initialize settings
  // Settings settings;
  //initialize the variable event, which we use to check events
SDL_Event event;
  
//Screen attributes
extern const int SCREEN_WIDTH ; //640;
extern const int SCREEN_HEIGHT ;
extern const int SCREEN_BPP ;

//Map attributes
 extern const int MAP_WIDTH ;
  

 //Quit flag
 bool quit = false;


 //Initialize Menu
 Start Startup{0,0,"PACMAN"};


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
 Highscore myHighscore;


 //StringInput
 StringInput PlayerName;



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

    Food myFood42(250,10);
    Food myFood43(250,90);
    Food myFood44(250,250);
    Food myFood45(250,290);
    Food myFood46(250,330);
    Food myFood47(250,370);
    Food myFood48(250,410);
    Food myFood49(250,450);

    Food myFood50(290,10);
    Food myFood51(290,90);
    Food myFood52(290,250);
    Food myFood53(290,330);
    Food myFood54(290,450);

    Food myFood55(330,10);
    Food myFood56(330,250);
    Food myFood57(330,330);
    Food myFood58(330,450);

    Food myFood59(370,10);
    Food myFood60(370,50);
    Food myFood61(370,90);
    Food myFood62(370,130);
    Food myFood63(370,170);
    Food myFood64(370,210);
    Food myFood65(370,250);
    Food myFood66(370,450);

    Food myFood67(410,10);
    Food myFood68(410,90);
    Food myFood69(410,170);
    Food myFood70(410,250);
    Food myFood71(410,290);
    Food myFood72(410,330);
    Food myFood73(410,370);
    Food myFood74(410,410);
    Food myFood75(410,450);

    Food myFood76(450,10);
    Food myFood77(450,90);
    Food myFood78(450,170);
    Food myFood79(450,450);

    Food myFood80(490,10);
    Food myFood81(490,90);
    Food myFood82(490,170);
    Food myFood83(490,250);
    Food myFood84(490,290);
    Food myFood85(490,330);
    Food myFood86(490,370);
    Food myFood87(490,410);
    Food myFood88(490,450);

    Food myFood89(530,10);
    Food myFood90(530,90);
    Food myFood91(530,170);
    Food myFood92(530,290);
    Food myFood93(530,450);

    Food myFood94(570,10);
    Food myFood95(570,90);
    Food myFood96(570,170);
    Food myFood97(570,250);
    Food myFood98(570,290);
    Food myFood99(570,330);
    Food myFood100(570,450);

    Food myFood101(610,10);
    Food myFood102(610,50);
    Food myFood103(610,90);
    Food myFood104(610,130);
    Food myFood105(610,170);
    Food myFood106(610,210);
    Food myFood107(610,250);
    Food myFood108(610,330);
    Food myFood109(610,370);
    Food myFood110(610,410);
    
    
    //create vectorwith all food in, called food_vector
    std::vector<Food> food_vector = 
      {myFood1,myFood2,myFood3,myFood4,myFood5,myFood6,myFood7,myFood8,myFood9,myFood10,
       myFood11,myFood12,myFood13,myFood14,myFood15,myFood16,myFood17,myFood18,myFood19,myFood20,
       myFood21,myFood22,myFood23,myFood24,myFood25,myFood26,myFood27,myFood28,myFood29,myFood30,
       myFood31,myFood32,myFood33,myFood34,myFood35,myFood36,myFood37,myFood38,myFood39,myFood40,
       myFood41,myFood42,myFood43,myFood44,myFood45,myFood46,myFood47,myFood48,myFood49,myFood50,
       myFood51,myFood52,myFood53,myFood54,myFood55,myFood56,myFood57,myFood58,myFood59,myFood60,
       myFood61,myFood62,myFood63,myFood64,myFood65,myFood66,myFood67,myFood68,myFood69,myFood70,
       myFood71,myFood72,myFood73,myFood74,myFood75,myFood76,myFood77,myFood78,myFood79,myFood80,
       myFood81,myFood82,myFood83,myFood84,myFood85,myFood86,myFood87,myFood88,myFood89,myFood90,
       myFood91,myFood92,myFood93,myFood94,myFood95,myFood96,myFood97,myFood98,myFood99,myFood100,
       myFood101,myFood102,myFood103,myFood104,myFood105,myFood106,myFood107,myFood108,myFood109,myFood110};
    
    //std::vector<Food> food_vector = {myFood50};
    
   

    //Special_food
    Special_Food mySpecial_Food1(10,10);
    Special_Food mySpecial_Food2(10,450);
    Special_Food mySpecial_Food3(610 ,10);
    Special_Food mySpecial_Food4(570,410);

    Special_Food mySpecial_Food(370,0);
    std::vector<Special_Food> special_food_vector = {mySpecial_Food1,mySpecial_Food2,mySpecial_Food3,mySpecial_Food4};

    //The frame rate regulator
    Timer fps;


    //The checkpoint timers, helps the ghosts so they dont get distracted by the checkpoints
    Timer checktimer1;
    Timer checktimer2;
    Timer checktimer3;



    // Timer for controlling when pacman eats ghosts
    Timer special_food_timer;
    

    Button theButton1(660,100,"Press \"S\" to start ");
    Button theButton2(660, 150,"Press \"P\" to pause ");
    Button theButton3(660, 200,"Press \"Q\" to quit");
    Button theButton4(660,250,"Press \"H\" to show highscore");
    

  //Initialize
  if( init() == false )
    {
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
  SDL_Rect checkpoint2 = {175,15,5,5};
  SDL_Rect checkpoint3 = {375,15,5,5};
  SDL_Rect checkpoint4 = {375,100,5,5};
  SDL_Rect checkpoint5 = {260,260,5,5};
  SDL_Rect checkpoint6 = {260,500,5,5};
  SDL_Rect checkpoint7 ={175,100,5,5};
  SDL_Rect checkpoint8={175,260,5,5};
  SDL_Rect checkpoint9={375,260,5,5};
  SDL_Rect checkpoint10={375,175,5,5};
  SDL_Rect checkpoint11={175,460,5,5};
  SDL_Rect checkpoint12={260,460,5,5};
  SDL_Rect checkpoint13={415,460,5,5};
  SDL_Rect checkpoint14={500,460,5,5};
  SDL_Rect checkpoint15={500,300,5,5};
  SDL_Rect checkpoint16={570,300,5,5};
  SDL_Rect checkpoint17={620,175,5,5};
  SDL_Rect checkpoint18={620,100,5,5};
  SDL_Rect checkpoint19={620,15,5,5};
  SDL_Rect checkpoint20={175,175,5,5};
  SDL_Rect checkpoint21={100,260,5,5};
  SDL_Rect checkpoint22={100,460,5,5};

//SDL_Rect checkpoint7 = {
  //   SDL_Rect checkpoint8 = {
  // SDL_Rect checkpoint9 = {
  //SDL_Rect checkpoint10 = {
  

  //Create a vector with all the checkpoints

  std::vector<SDL_Rect> checkmaze = {checkpoint1,checkpoint2,checkpoint3,checkpoint4,checkpoint5,checkpoint6,checkpoint7,checkpoint8,checkpoint9,checkpoint10,checkpoint11,checkpoint12,checkpoint13,checkpoint14,checkpoint15,checkpoint16,checkpoint17,checkpoint18,checkpoint19,checkpoint20,checkpoint21,checkpoint22};

 
    // Clip the sprite sheet
  //   myPacman.set_clips();
 

    //While the user hasn't quit
    while( quit == false )
      {

	//=================== Startup =========================

	if(Startup.is_start())
	  {	
	    //Set proceed-flag to false
	    bool proceed = false;

	    //Start screen
	    Startup.show();
	    
	    Startup.show_infopanel();
	    theButton1.show();
	    theButton2.show();
	    theButton3.show();
	    theButton4.show();
	 
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
		
		//If a key is pressed
		while(SDL_PollEvent( &event))
		  Startup.handle_input(proceed,quit);
		
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
				quit = true; cont = true; std::cout<<"Game quit!"<<std::endl; 
			      }
			    //=========================================================
			    SDL_Surface *new_screen = NULL; // Experiment

			    //Unpause the game 
			    if(event.type == SDL_KEYDOWN)
			      {
				switch(event.key.keysym.sym)
				  {
				  case SDLK_p: cont = true; std::cout << "Play!"<< std::endl; break;
				  case SDLK_q: cont = true ; quit = true; std::cout << "Game quit" << std::endl; return 0; break;
				  case SDLK_h: init(new_screen, "Highscore");
				    Highscore_screen Highscore(400,10, "HIGHSCORE");
				    
				    Highscore.show();
				    myHighscore.show();
				    
				    //update screen
				    if( SDL_Flip( screen ) == -1 )
				      {
					return 1;
				      }
				    
				    std::cout<< "Highscore. Game paused."<<std::endl;
				    break; //test
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

	
	if(!checktimer1.is_started()) //If the timer is off, turn it on
	  {checktimer1.start();}
	


	if(checktimer1.get_ticks() > 300) //was it long enough since we found a checkpoint?
	  {
	    myGhost1.do_if_checkpoint(checkmaze, myPacman);
	    if(myGhost1.is_checkpoint(checkmaze))
	      {checktimer1.start();} //restart the timer so that ghost only will look at a checkpoint once
	  }
	


	if(!checktimer2.is_started()) //If the timer is off, turn it on
	  {checktimer2.start();}

	if(checktimer2.get_ticks() > 300) //was it long enough since we found a checkpoint?
	  {
	    myGhost2.do_if_checkpoint(checkmaze);
	    if(myGhost2.is_checkpoint(checkmaze))
	      {checktimer2.start();} //restart the timer so that ghost only will look at a checkpoint once
	  }


	if(!checktimer3.is_started()) //If the timer is off, turn it on
	  {checktimer3.start();}
	
	
	if(checktimer3.get_ticks() > 1000) //was it long enough since we found a checkpoint?
	  {
	    myGhost3.do_if_checkpoint(checkmaze, myPacman);
	    if(myGhost3.is_checkpoint(checkmaze))
	      {checktimer3.start();} //restart the timer so that ghost only will look at a checkpoint once
	  }




	//Is a ghost eating Pacman or are Pacman eating a ghost
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

	//Om alla Food objekt är uppätna avslutas spelet. Ska troligtvis ske något annat
	if(myPacman.no_food_left())
	  {
	    bool cont=false;
	    End_game game_over;
	    SDL_Surface *new_screen = NULL; // Experiment

	    init(new_screen,"Enter Name");

	    game_over.show();

	    //update screen
	    if( SDL_Flip( screen ) == -1 )
	      {
		return 1;
	      }
	    
	    
	    //Keep track if whether or not the user has entered their name
	   
	      
		
	    bool nameEntered = false;
	    	while(!nameEntered)
		  {
		    while(SDL_PollEvent( &event))
		      {
	
		    //If the user hasn't entered their name yet
		    if( nameEntered == false )
		      {
			
			  //Get user input
			  PlayerName.handle_input();
			
			  
			  //If the enter key was pressed
			  if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
			    {
			      //Change the flag
			      nameEntered = true;
			      //cont =true;///////
			      std::cout<< PlayerName.get_str()<< std::endl;
			      std::cout<< "Enter"<< std::endl;
				   
			    }
			


			PlayerName.show_centered();

			//uppdate screen
			if( SDL_Flip( screen ) == -1 )
			  {
			    return 1;
			  }
			
		      }
		  }
		
		
	
	      }

	      PlayerName.show_centered();

	      //uppdate screen
	      if( SDL_Flip( screen ) == -1 )
		{
		  return 1;
		}
    
	  

	       
	      }
	  



	//Is a Pacman eating food
	myPacman.eat_food(food_vector, myScore);


	//Is Pacman eating special_food
	myPacman.eat_special_food(special_food_vector, myScore);

	// Makes ghosts run
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


		
	// Sets ghosts back to chasing Pacman
	if(special_food_timer.get_ticks() > 5000)
	  {
	    myGhost1.change_mood();
	    myGhost2.change_mood();
	    myGhost3.change_mood();
	    special_food_timer.stop();
	  }
	


        //Fill the screen white or blue, depending on whether the ghost is scared
       
	if(myGhost1.is_scared())
	  {
	    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	  }
	else
	  {
	    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x3, 0x5, 0x80 ) );
	  } 


        //Show the walls
	for (std::vector<SDL_Rect>::iterator it = maze.begin() ; it != maze.end(); ++it)
	  {
	    SDL_FillRect( screen, &(*it), SDL_MapRGB( screen->format, 0x00, 0x00, 0xEF) );
	  }


	//show the wonderwall
	SDL_FillRect( screen, &wall25, SDL_MapRGB( screen->format, 0xAF, 0x00, 0x00) );

        //Show pacman on the screen
        myPacman.show();
	
	//Show food on the screen
	myFood1.show_all_food(food_vector);

	//Show special_food on the screen
	mySpecial_Food1.show_all_special_food(special_food_vector);


	//Show the checkpoints - just for testing
	for (std::vector<SDL_Rect>::iterator it = checkmaze.begin() ; it != checkmaze.end(); ++it)
	  {
	    SDL_FillRect( screen, &(*it), SDL_MapRGB( screen->format, 0x00, 0xEF, 0xEF) );
	  }

	//Show ghost on the screen
	myGhost1.show();
	myGhost2.show();
	myGhost3.show();

	//show infopanel
	Startup.show_infopanel();

	//show the buttons
	theButton1.show();
	theButton2.show();
	theButton3.show();
	theButton4.show();


	//show the lives on the screen
	myPacman.showlife();

	//Show score on the side of the screen
	myScore.show();
	
      
	
        if( SDL_Flip( screen ) == -1 )
	  {
            return 1;
	  }
	

        //Cap the frame rate
	fps.delay_game();
	/* if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
	  {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
	    }*/
      }
    
  

    return 0;
}

//============================================================================
// Name        : highscore.cpp
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
#include "highscore.h"



//============================================================================
//  Class: Highscore
//============================================================================
//Highscore::Highscore(){}

bool Highscore::is_new_highscore(Score& myScore) // ev. ta in namn också
{
  load_list();
  int size=highscoretable.size();
  if ((size<10) || (myScore.return_score() > highscoretable[size-1].return_score()))
    {
      return true;
      }
  return false;
}

void Highscore::save_new_highscore(Score& new_highscore)
{
  //Load highscore list to vector
  load_list();

  //Save highscore list to file
  std::ofstream outputFile ("src/highscore.txt", std::ios::binary);
  //Highscore highscore_entry{new_score, "Ingrid"};
  new_highscore.set_name("ingrid");
   highscoretable.push_back(new_highscore);
   // std::stable_sort (highscoretable.begin(), highscoretable.end());
   std::reverse(highscoretable.begin(),highscoretable.end());
   if (highscoretable.size() == 11)
    {
      highscoretable.pop_back();
    }
  for ( int i = 0 ; i < highscoretable.size() ; i++)
    { 
      outputFile << highscoretable[i].return_score() << std::endl;
      outputFile << highscoretable[i].return_name() << std::endl;
    }
    outputFile.close();
}

void Highscore::load_list()
{
  std::ifstream inputfile ("src/highscore.txt");
  Score entry;
  highscoretable.clear();
  int points{0};
  std::string name;
  while (inputfile >> points)
      { 
	entry.set_score(points);
	inputfile >> name;
	entry.set_name(name);
	highscoretable.push_back(entry);
      }
  inputfile.close();
}


void Highscore::show()
{
  //highscore = TTF_RenderText_Solid( font, get_highscore().c_str(), textColor );
  //apply_surface(0,0,score,screen);
  Sprite animation;
  animation.show_highscore(0,0);
}

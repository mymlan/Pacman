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
  //apply_surface(0,0,score,screen);
  Sprite animation;
  animation.show_highscore(0,0);
}



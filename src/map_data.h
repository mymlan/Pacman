#ifndef _MAP_DATA_H
#define _MAP_DATA_H

#include "food.h"
#include <vector>

std::vector<Food> map_data_get_food_vector();

std::vector<Special_Food> map_data_get_special_food_vector();

std::vector<SDL_Rect> map_data_get_maze_vector();

std::vector<SDL_Rect> map_data_get_checkpoint_vector();

#endif // _MAP_DATA_H

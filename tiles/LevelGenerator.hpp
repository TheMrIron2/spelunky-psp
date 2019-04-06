//
// Created by xdbeef on 15.09.18.
//

#ifndef SPELUNKYDS_LEVEL_LAYOUT_H
#define SPELUNKYDS_LEVEL_LAYOUT_H

#include "Level.hpp"

void generate_new_level_layout();

void obtain_new_direction(int curr_x, Direction &direction);

void place_an_altar();

void place_a_shop();

#endif //SPELUNKYDS_LEVEL_LAYOUT_H

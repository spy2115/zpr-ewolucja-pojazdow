/*
Eryk Jakubowski
Function that sets up data used in the project.
*/

#pragma once
#include "./Render.h"

void init( std::vector<Box> &boxes, std::vector<float> &boxes_x, std::vector<float> &boxes_y, std::vector<Car> &cars, std::vector<CarData> &cars_data, std::vector<std::vector<std::pair<float, float>>> &cars_positions, float &track_start, float &track_end );
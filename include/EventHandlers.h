/*
Jakub Ciarcinski, Eryk Jakubowski
Functions which handle user's interactions with UI.
*/

#pragma once
#include "./GA.h"
#include "./FileOperations.h"
#include "./TextField.h"
#include "./Init.h"

void handleClickSavePopulation( std::vector<Car> &cars, GeneticAlgorithm &saga, ScrollableList &file_list );

void handleClickLoadPopulation( std::vector<Car> &cars, GeneticAlgorithm &saga, ScrollableList &file_list, std::vector<Box> &boxes, std::vector<std::vector<std::pair<float, float>>> &cars_positions );

void handleClickSet( std::vector<Car> &cars, GeneticAlgorithm &saga, std::vector<Box> &boxes, std::vector<std::vector<std::pair<float, float>>> &cars_positions, std::vector<float> &boxes_x,
                    std::vector<float> &boxes_y, TextField fields[], std::vector<sf::Text> &labels, std::vector<CarData> &cars_data, float &track_start, float &track_end );
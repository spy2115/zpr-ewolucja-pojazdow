/*
Eryk Jakubowski
Various helper functions used in project.
*/

#pragma once
#include <cmath>
#include <random>
#include <sstream>
#include "./ScrollableList.h"

bool isInteger( const std::string& str );

bool isFloat( const std::string& str );

float randomFloatGenerator( float min, float max );

float randomNormalFloatGenerator( float mean, float stddev );
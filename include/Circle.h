/*
Jakub Ciarcinski
A struct that represents a circle-type object and holds a pointer to its body for physics.
*/

#pragma once
#include "./Globals.h"

struct Circle{
	float radius;
	sf::Color color;
	b2Body *body;
};

Circle createCircle( float x, float y, float radius, float density, float friction, sf::Color color );
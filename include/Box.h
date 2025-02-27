/*
Jakub Ciarcinski, Eryk Jakubowski
A struct that represents a box-type object and holds a pointer to its body for physics.
*/

#pragma once
#include "./Globals.h"
#include "./Utils.h"

struct Box{
	float width;
	float height;
	sf::Color color;
	b2Body *body;
};

Box createBox( float x, float y, float width, float height, float density, float friction, sf::Color color );

void createGround( std::vector<Box> &boxes, float x, float y, float width, float height, int count, sf::Color color );
